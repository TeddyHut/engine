#pragma once

#include <cstdint>
#include <cstdarg>
#include <cstring>
#include <vector>
#include <functional>
#include <tuple>

namespace eg {
	//TODO: Wasn't operator= supposed to return something? Like a reference to 'this'? Find out.
	namespace util {
		namespace Container {
			template<typename Master_t,typename Element_t = Master_t> class Element {
			public:
				size_t const get_iteration();

				void operator=(Element_t const& p0);
				void operator=(Element<Master_t,Element_t> const& p0);
				operator Element_t& ();
				operator Element_t const&() const;	//TODO: Check whether we need const and non-const versions when brain starts working

				//TODO: Scratch that ^, check what the consts of this whole thing do! (crazyness)
				//TODO: Switch to _iteration over iteration
				//TODO: Maybe overload this contructor with a Master_t* const version? If things don't work out...
				Element(Master_t const * const nmaster, size_t const niteration);
			private:
				size_t iteration;
				Master_t* master;
			};

			template<typename Master_t,typename Element_t = Master_t> class Iterator {
			public:
				size_t const get_iteration();

				void operator=(Element_t const& p0);
				void operator=(Iterator<Master_t,Element_t> const& p0);
				void operator++();
				bool const operator==(Iterator<Master_t,Element_t> const& p0) const;
				bool const operator!=(Iterator<Master_t,Element_t> const& p0) const;
				Element<Master_t,Element_t> operator*();
				Element<Master_t,Element_t> const operator*() const;

				Iterator(Master_t const * const nmaster, size_t const niteration);
			private:
				size_t iteration;
				Master_t* master;
			};
		}
	}

	//TODO V2: Add const set of members (eg for creating an iterator from a const-param) | Done?
	//Idea for V2: Explicit constuctors/operators or whatever
	//Idea for V2: operator[](Element/Iterator p0) <- allows for(auto&& element : param) { param[element] }
	//TODO: Make this use the stuff above ^^^
	class Param {
	public:
		struct ExternReference {
			size_t iteration;
			bool element;		//Checked instance of param that can be passed out as a variable
			bool element_prev;	//Used to check which one was updated
		};

		bool get_param(size_t const param) const;				//Get value of param -param-
		void set_param(size_t const param, bool const nbit);	//Set value of param -param-

		void add_param(size_t const amount);					//Add -amount- param to stack
		void remove_param(size_t const amount);					//Remove -amount- param from stack

		size_t param_amount;
		uint8_t param_free;
		std::vector<uint8_t> param_data;

		auto begin()							->eg::util::Container::Iterator<eg::Param, bool>;		//Return a iterator to stack begin
		auto begin() const						->eg::util::Container::Iterator<eg::Param, bool> const;	//Return a const iterator to stack begin
		auto end()								->eg::util::Container::Iterator<eg::Param, bool>;		//Return a iterator to stack end
		auto end() const						->eg::util::Container::Iterator<eg::Param, bool> const;	//Return a const iterator to stack end
		auto operator[](size_t const p0)		->eg::util::Container::Element<eg::Param, bool>;
		auto operator[](size_t const p0) const	->eg::util::Container::Element<eg::Param, bool> const;

		Param(size_t const amount);
		Param(size_t const amount, size_t param, bool nbit, ...);
		Param();
		~Param();
	private:
		bool get_param_p(size_t const param) const;
		void set_param_p(size_t const param, bool const nbit);
		
		void refreshExtern();
		void refreshExtern() const;

		void Container_set(size_t const iteration, bool const element);
		bool& Container_get(size_t const iteration);
		bool const& Containter_get(size_t const iteration) const;

		std::vector<ExternReference> externReference;

		friend eg::util::Container::Element<eg::Param, bool>;
		friend eg::util::Container::Iterator<eg::Param, bool>;
	};

	namespace util {
		//TODO: Use vector::find (or whatever) instead of searching through
		namespace remove_p0_from_p1 {
			extern size_t const PARAM_ALL; //Set this to remove all of the instance that is in the vector specified
			extern eg::Param const Param_DEFAULT;
		}
		namespace remove_p0_from_p1 {
			template<typename T0> void remove_p0_from_p1_idn(std::vector<T0> const& p0, std::vector<T0>& p1); //Removes exacly what is told to
			template<typename T0> void remove_p0_from_p1_all(std::vector<T0> const& p0, std::vector<T0>& p1); //Removes all matches of type if found
			template<typename T0> void remove_p0_from_p1(std::vector<T0> const& p0, std::vector<T0>& p1, eg::Param const param0 = Param_DEFAULT);
		}
		void edianSwap(void* buffer, size_t buffer_len, size_t type_len = 0);	//Swaps the edian of the buffer. -buffer_len- is measured in bytes
	} //end namespace util

} //end namespace eg

//Legit... Like.. WHAT? Templates are so sillly.

template<typename Master_t, typename Element_t> size_t const eg::util::Container::Element<Master_t, Element_t>::get_iteration() {
	return(iteration);
}

template<typename Master_t, typename Element_t> void eg::util::Container::Element<Master_t, Element_t>::operator=(Element_t const& p0) {
	master->Container_set(iteration, p0);
}

template<typename Master_t, typename Element_t> void eg::util::Container::Element<Master_t, Element_t>::operator=(Element<Master_t, Element_t> const& p0) {
	master->Container_set(p0.iteration, p0);	//Should automatically convert to needed type becuase of operator T0();
}

template<typename Master_t, typename Element_t> eg::util::Container::Element<Master_t, Element_t>::operator Element_t& () {
	return(master->Container_get(iteration));
}

template<typename Master_t, typename Element_t> eg::util::Container::Element<Master_t, Element_t>::operator Element_t const&() const {
	return(master->Container_get(iteration));
}

//Why const * const and const_cast are needed: Needed because cannot convert 'const this' to 'this' when passing master param from const function
template<typename Master_t, typename Element_t> eg::util::Container::Element<Master_t, Element_t>::Element(Master_t const * const nmaster, size_t const niteration) : master(const_cast<Master_t*>(nmaster)), iteration(niteration) {
}

template<typename Master_t, typename Element_t> size_t const eg::util::Container::Iterator<Master_t, Element_t>::get_iteration() {
	return(iteration);
}

template<typename Master_t, typename Element_t> void eg::util::Container::Iterator<Master_t, Element_t>::operator=(Element_t const& p0) {
	master->Container_set(iteration, p0);
}

template<typename Master_t, typename Element_t> void eg::util::Container::Iterator<Master_t, Element_t>::operator=(Iterator<Master_t, Element_t> const& p0) {
	master->Container_set(p0.iteration, p0);
}

template<typename Master_t, typename Element_t> void eg::util::Container::Iterator<Master_t, Element_t>::operator++() {
	iteration++;
	//TODO: Some error checking here would be a good idea.
}

template<typename Master_t, typename Element_t> bool const eg::util::Container::Iterator<Master_t, Element_t>::operator==(Iterator<Master_t, Element_t> const& p0) const {
	return((iteration == p0.iteration) && (master == p0.master));
}

template<typename Master_t, typename Element_t> bool const eg::util::Container::Iterator<Master_t, Element_t>::operator!=(Iterator<Master_t, Element_t> const& p0) const {
	return((iteration != p0.iteration) || (master != p0.master));
}

template<typename Master_t, typename Element_t> eg::util::Container::Element<Master_t, Element_t> eg::util::Container::Iterator<Master_t, Element_t>::operator*() {
	return(eg::util::Container::Element<Master_t, Element_t>::Element(master, iteration));
}

template<typename Master_t, typename Element_t> eg::util::Container::Element<Master_t, Element_t> const eg::util::Container::Iterator<Master_t, Element_t>::operator*() const {
	return(const_cast<eg::util::Container::Element<Master_t, Element_t> const>(eg::util::Container::Element<Master_t, Element_t>::Element(master, iteration)));//Maybe get rid of that const_cast... Not really needed
}

//Maybe cast to <T0* const>?
template<typename Master_t, typename Element_t> eg::util::Container::Iterator<Master_t, Element_t>::Iterator(Master_t const * const nmaster, size_t const niteration) : master(const_cast<Master_t*>(nmaster)), iteration(niteration) {
}

template<typename T0> void eg::util::remove_p0_from_p1::remove_p0_from_p1_idn(std::vector<T0> const& p0, std::vector<T0>& p1) {
	for (uint32_t i = 0; i < p0.size(); i++) {
		for (uint32_t j = 0; j < p1.size(); j++) {
			if (p1[j] == p0[i]) {
				p1.erase(p1.begin() + j);
				break;
			}
		}
	}
}

//Hmm... Check this works (erase at pos 7 yet still +1 = pos 9)
template<typename T0> void eg::util::remove_p0_from_p1::remove_p0_from_p1_all(std::vector<T0> const& p0, std::vector<T0>& p1) {
	for (uint32_t i = 0; i < p0.size(); i++) {
		for (uint32_t j = 0; j < p1.size(); j++) {
			if (p1[j] == p0[i]) {
				p1.erase(p1.begin() + j);
				j--;	//Added this in to fix above problem... May also cause problems.
			}
		}
	}
}

template<typename T0> void eg::util::remove_p0_from_p1::remove_p0_from_p1(std::vector<T0> const& p0, std::vector<T0>& p1, eg::Param const param0) {
	if (param0.get_param(eg::util::remove_p0_from_p1::PARAM_ALL)) {
		eg::util::remove_p0_from_p1::remove_p0_from_p1_all<T0>(p0, p1);
	}
	else {
		eg::util::remove_p0_from_p1::remove_p0_from_p1_idn<T0>(p0, p1);
	}
}
