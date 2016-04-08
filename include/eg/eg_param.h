#pragma once

#include <cstdint>
#include <cstdarg>
#include <vector>
#include "eg_foundation.h"

namespace eg {
	template<typename param_t = size_t> class Param {
	public:
		struct ExternReference {
			size_t iteration;
			bool element;		//Checked instance of param that can be passed out as a variable
			bool element_prev;	//Used to check which one was updated
		};

		eg::Param<param_t>& operator=(eg::Param<param_t> const& p0);

		bool get_param(param_t const param, bool const temp_param_enum = true) const;				//Get value of param -param-
		void set_param(param_t const param, bool const nbit, bool const temp_param_enum = true);	//Set value of param -param-

		void add_param(size_t const amount);					//Add -amount- param to stack
		void remove_param(size_t const amount);					//Remove -amount- param from stack

		bool param_enum;
		size_t param_amount;
		uint8_t param_free;
		std::vector<uint8_t> param_data;
		std::vector<size_t> param_order;

		auto begin()->eg::util::Container::Iterator<eg::Param<param_t>, bool>;		//Return a iterator to stack begin
		auto begin() const->eg::util::Container::Iterator<eg::Param<param_t>, bool> const;	//Return a const iterator to stack begin
		auto end()->eg::util::Container::Iterator<eg::Param<param_t>, bool>;		//Return a iterator to stack end
		auto end() const->eg::util::Container::Iterator<eg::Param<param_t>, bool> const;	//Return a const iterator to stack end
		auto operator[](param_t const p0)->eg::util::Container::Element<eg::Param<param_t>, bool>;
		auto operator[](param_t const p0) const->eg::util::Container::Element<eg::Param<param_t>, bool> const;

		Param(size_t const amount, bool const nenum = true);
		Param(size_t const amount, bool const nenum, param_t param, bool nbit, ...);
		Param();
		~Param();
	private:
		bool get_param_p(size_t const param, bool const temp_param_enum = true) const;
		void set_param_p(size_t const param, bool const nbit, bool const temp_param_enum = true);

		size_t get_param_index(size_t const param, bool*const result = nullptr, bool const regular = true);
		size_t get_param_index(size_t const param, bool*const result = nullptr, bool const regular = true) const;

		void refreshExtern();
		void refreshExtern() const;

		void Container_set(size_t const iteration, bool const element);
		bool& Container_get(size_t const iteration);
		bool const& Containter_get(size_t const iteration) const;

		std::vector<ExternReference> externReference;

		friend eg::util::Container::Element<eg::Param<param_t>, bool>;
		friend eg::util::Container::Iterator<eg::Param<param_t>, bool>;
	};
}

template<typename param_t> eg::Param<param_t>& eg::Param<param_t>::operator=(eg::Param<param_t> const& p0) {
	//TODO: Double check that it isn't smarter to just use set_param instead
	std::vector<size_t> done;									//Things that are done
	for (size_t i = 0; i < param_amount; i++) {
		if (i >= p0.param_order.size()) {
			for (size_t j = 0; j < param_order.size(); j++) {
				bool set_it = true;
				for (auto&& element : done) {
					if (element == param_order[j]) {
						set_it = false;
						break;
					}
				}
				if (set_it) {
					set_param_p(param_order[j], false);
				}
			}
			break;
		}
		set_param_p(p0.param_order[i], p0.get_param_p(p0.param_order[i]));	//Sets own param_t value to otherones param_t value without actually doing it
		done.push_back(p0.param_order[i]);
	}
	refreshExtern();
	return(*this);
}

template<typename param_t> bool eg::Param<param_t>::get_param(param_t const param, bool const temp_param_enum) const {
	refreshExtern();
	return(get_param_p(static_cast<size_t>(param),temp_param_enum));
}

template<typename param_t> void eg::Param<param_t>::set_param(param_t const param, bool const nbit, bool const temp_param_enum) {
	set_param_p(static_cast<size_t>(param), nbit, temp_param_enum);
	refreshExtern();
}

template<typename param_t> void eg::Param<param_t>::add_param(size_t const amount) {
	size_t amountc = amount;
	while (true) {
		if (static_cast<size_t>(param_free) < amountc) {
			amountc -= static_cast<size_t>(param_free);
			param_amount += static_cast<size_t>(param_free);

			param_data.push_back(0);
			param_free = 8;
		}
		else {
			param_free -= static_cast<uint8_t>(amountc);
			param_amount += amountc;
			break;
		}
	}
}

template<typename param_t> void eg::Param<param_t>::remove_param(size_t const amount) {
	size_t amountc = amount;
	while (true) {
		size_t f = static_cast<size_t>(8 - param_free);
		if (f < amountc) {
			amountc -= f;
			param_amount -= f;

			param_data.erase(param_data.end() - 1);
			param_free = 0;
		}
		else {
			param_free += static_cast<uint8_t>(amountc);
			param_amount -= amountc;
			break;
		}
	}
}

template<typename param_t> auto eg::Param<param_t>::begin()->eg::util::Container::Iterator<eg::Param<param_t>, bool> {
	return(typename eg::util::Container::Iterator<eg::Param<param_t>, bool>::Iterator(this, 0));
}

template<typename param_t> auto eg::Param<param_t>::begin() const->eg::util::Container::Iterator<eg::Param<param_t>, bool> const {
	return(typename eg::util::Container::Iterator<eg::Param<param_t>, bool>::Iterator(this, 0));
}

template<typename param_t> auto eg::Param<param_t>::end()->eg::util::Container::Iterator<eg::Param<param_t>, bool> {
	return(typename eg::util::Container::Iterator<eg::Param<param_t>, bool>::Iterator(this, param_amount));
}

template<typename param_t> auto eg::Param<param_t>::end() const->eg::util::Container::Iterator<eg::Param<param_t>, bool> const {
	return(typename eg::util::Container::Iterator<eg::Param<param_t>, bool>::Iterator(this, param_amount));
}

template<typename param_t> auto eg::Param<param_t>::operator[](param_t const p0)->eg::util::Container::Element<eg::Param<param_t>, bool> {
	return(typename eg::util::Container::Element<eg::Param<param_t>, bool>::Element(this, get_param_index(static_cast<size_t const>(p0))));
}

template<typename param_t> auto eg::Param<param_t>::operator[](param_t const p0) const->eg::util::Container::Element<eg::Param<param_t>, bool> const {
	return(typename eg::util::Container::Element<eg::Param<param_t>, bool>::Element(this, get_param_index(static_cast<size_t const>(p0))));
}

template<typename param_t> eg::Param<param_t>::Param(size_t const amount, bool const nenum) : param_amount(0), param_free(0) {
	param_enum = nenum;
	add_param(amount);
}

template<typename param_t> eg::Param<param_t>::Param(size_t const amount, bool const nenum, param_t param, bool nbit, ...) : param_amount(0), param_free(0) {
	param_enum = nenum;
	add_param(amount);
	set_param(param, nbit);
	size_t amountc = amount - 1;

	va_list ellipse;
	va_start(ellipse, nbit);

	for (size_t i = 0; i < amountc; i++) {
		param_t const tparam = va_arg(ellipse, param_t);
		bool const tbit = (va_arg(ellipse, int)) != 0;
		set_param(tparam, tbit);
	}
	va_end(ellipse);
}

template<typename param_t> eg::Param<param_t>::Param() : param_enum(true), param_amount(0), param_free(0) {
}

template<typename param_t> eg::Param<param_t>::~Param() {
}

template<typename param_t> bool eg::Param<param_t>::get_param_p(size_t const param, bool const temp_param_enum) const {
	size_t paramc = get_param_index(param,nullptr,temp_param_enum);
	return(((param_data[paramc / 8]) >> paramc % 8) & 0x01);
}

template<typename param_t> void eg::Param<param_t>::set_param_p(size_t const param, bool const nbit, bool const temp_param_enum) {
	bool result;
	size_t paramc = get_param_index(param, &result, temp_param_enum);
	if (result) {
		bool nbitc = nbit;
		param_data[paramc / 8] &= ~(1 << (paramc % 8));
		param_data[paramc / 8] |= (nbitc << (paramc % 8));
	}
}

template<typename param_t> size_t eg::Param<param_t>::get_param_index(size_t const param, bool*const result, bool const regular) {
	bool wants_result = true;								//bool used to determine if the caller wants a result
	if (result == nullptr) wants_result = false;			//if they don't, set the variable to false
	if (param_enum && regular) {							//if this is an enum param and it is a regular call
		for (size_t i = 0; i < param_order.size(); i++) {	//iterate through param_order
			if (param_order[i] == param) {					//if param_order[i] matches param
				if (wants_result) *result = true;			//result = success
				return(i);									//return the iteration (location of ordered param)
			}
		}
		if (param_order.size() < param_amount) {			//if there is still room for new params
			if (wants_result) *result = true;				//result = success
			param_order.push_back(param);					//Add the new enum value to param_order
			return(param_order.size()-1);					//return location of ordered param
		}
	}
	else {													//if -param- points to an ordered param location
		if (param < param_amount) {							//if the param is within range
			if (wants_result) *result = true;				//result = success
			return(param);									//return param
		}
	}
	if (wants_result) *result = false;						//result = failure
	return(0);												//return lowest possible value
}

template<typename param_t> size_t eg::Param<param_t>::get_param_index(size_t const param, bool*const result, bool const regular) const {
	bool wants_result = true;
	if (result == nullptr) wants_result = false;
	if (param_enum && regular) {
		for (size_t i = 0; i < param_order.size(); i++) {
			if (param_order[i] == param) {
				if(wants_result) *result = true;
				return(i);
			}
		}
	}
	else {
		if (param < param_amount) {
			if (wants_result) *result = true;
			return(param);
		}
	}
	if (wants_result) *result = false;
	return(0);
}

template<typename param_t> void eg::Param<param_t>::refreshExtern() {
	for (auto&& element : externReference) {						//Iterate through externReferences
		bool intern = get_param_p(element.iteration, false);
		if (intern != element.element) {							//If the extern and the intern are no longer in sync
			if (element.element != element.element_prev) {			//If it was the extern that changed
				set_param_p(element.iteration, element.element);	//Update the internal param with that information
			}
			else {													//If it was the intern that changed
				element.element = intern;							//Update the extern with that information
			}
		}
		element.element_prev = element.element;						//Has been checked
	}
}

template<typename param_t> void eg::Param<param_t>::refreshExtern() const {
	//const_cast<std::remove_const<decltype(this)>::type>(this)->refreshExtern();
	const_cast<eg::Param<param_t>*>(this)->refreshExtern();	//<- THAT IS THE PIVOT OF C++ DISRESPECT RIGHT THERE
}

template<typename param_t> void eg::Param<param_t>::Container_set(size_t const iteration, bool const element) {
	set_param_p(iteration, element, false);
	refreshExtern();
}

template<typename param_t> bool& eg::Param<param_t>::Container_get(size_t const iteration) {
	refreshExtern();
	for (auto&& element : externReference) {
		if (element.iteration == iteration) {
			return(element.element);
		}
	}
	ExternReference exref;
	exref.iteration = iteration;
	exref.element = get_param_p(exref.iteration, false);
	exref.element_prev = exref.element;
	externReference.push_back(exref);
	return(externReference[externReference.size() - 1].element);
}

template<typename param_t> bool const& eg::Param<param_t>::Containter_get(size_t const iteration) const {
	return(const_cast<eg::Param<param_t>*>(this)->Container_get(iteration));		//AND I DID IT AGAIN! *clap clap clap*
}