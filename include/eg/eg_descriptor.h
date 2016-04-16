#pragma once

#include <utility>
#include <vector>
#include <map>

#include "eg_foundation.h"

namespace eg {
	template <typename key_t = int, typename value_t = int>
	class Descriptor {
		//TODO: Put some 'typedef' or 'using =' in here, because it looks rather messey
		//TODO: Do some cool constexpr stuff so that the compiler can do stuff (like a static initialised descriptor for comparison or something?)
	public:
		//Describes a set key and a vector of values, relative to master
		class Set {
		public:
			//Called on 'descriptor0[x] = descriptor1[y]'
			//"add values from descriptor1[y] to descriptor0[x] that are not already present"
			Set &operator=(Set const &p0);
			//Called on 'descriptor[x] = value_t'
			//"add value_t to descriptor vector [x] if not already there"
			Set &operator=(value_t const p0);

			//Called on 'descriptor[x][y]'
			//"descriptor vector[x] value[y]"
			auto operator[](value_t const p0)->util::Container::Iterator<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator> const;
			auto operator[](value_t const p0) const->util::Container::Iterator<Descriptor<key_t, value_t>, value_t, const std::vector<value_t>::iterator> const;

			//Called on 'descriptor0[x] == descriptor1[y]'
			//"descriptor0 vector[x] is equal to descriptor1 vector[y]"
			bool operator==(Set const &p0) const;
			//Called on 'descriptor[x] == value_t'
			//"descriptor vector[x] contains value_t"
			bool operator==(value_t const p0) const;

			//Called on 'descriptor[x] & value_t'
			//"create a descriptor that contains vector[x] with only value_t if value_t was already present"
			Descriptor<key_t, value_t> operator&(value_t const p0) const;
			//Called on 'descriptor0[x] & descriptor1[y]'
			//"create a descriptor that contains vector[x] if(x equals y) with the values that were equal in both vectors"
			Descriptor<key_t, value_t> operator&(Set const &p0) const;

			Set(Descriptor<key_t, value_t> *const nmaster, key_t niteration);
		private:
			Descriptor<key_t, value_t> *master;
			key_t _iteration;
		};
		std::map<key_t, std::vector<value_t>> description;

		bool valuePresent(key_t const key, value_t const value) const;

		//Called on '*_cast<bool>(descriptor)'
		//"descriptor contains at least one key"
		operator bool() const;

		//TODO: A contructor that allows for initialisation of everything (need to learn some initialiser lists)
		Descriptor();
		Descriptor(std::map<key_t const, std::vector<value_t> const> const ndescription);
	private:
		//Called on 'descriptor[x][y] = value_t'
		void Container_set(std::vector<value_t>::iterator const iteration, value_t const element);
		//Called on '*_cast<value_t>(descriptor[x][y])'
		value_t &Container_get(std::vector<value_t>::iterator const iteration);
		value_t const &Container_get(const std::vector<value_t>::iterator const iteration) const;

		//Returns a std::vector::iterator relative to the key and value. Adds -value- to vector -key- if not already there.
		std::vector<value_t>::iterator const Set_getIterator(key_t const key, value_t const value);
		const std::vector<value_t>::iterator const Set_getIterator(key_t const key, value_t const value) const;
		//Add -value- to vector -key- if not already there
		void Set_addValue(key_t const key, value_t const value);

		friend Set;
		friend Set const;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator>;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator> const;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator>;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator> const;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, const std::vector<value_t>::iterator>;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, const std::vector<value_t>::iterator> const;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, const std::vector<value_t>::iterator>;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, const std::vector<value_t>::iterator> const;
	};
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Set &eg::Descriptor<key_t, value_t>::Set::operator=(Set const &p0) {
	if (_iteratation == p0._iteration) {
		for (auto&& element : p0.master->description[_iteration]) {
			master->Set_addValue(_iteration, element);
		}
	}
	return(*this);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Set &eg::Descriptor<key_t, value_t>::Set::operator=(value_t const p0) {
	master->Set_addValue(_iteration, p0);
	return(*this);
}

template <typename key_t, typename value_t> auto eg::Descriptor<key_t, value_t>::Set::operator[](value_t const p0)->util::Container::Iterator<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator> const {
	return(util::Container::Iterator<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator>::Iterator(master, master->Set_getIterator(_iteration, p0)));
}

template <typename key_t, typename value_t> auto eg::Descriptor<key_t, value_t>::Set::operator[](value_t const p0) const->util::Container::Iterator<Descriptor<key_t, value_t>, value_t, const std::vector<value_t>::iterator> const {
	return(util::Container::Iterator<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator>::Iterator(master, master->Set_getIterator(_iteration, p0)));
}

template <typename key_t, typename value_t> bool eg::Descriptor<key_t, value_t>::Set::operator==(Set const &p0) const {
	if (_iteration == p0._iteration)	//If statement is probably the smartest thing (due to how map works)
		return(master->description[_iteration] == p0.master->description[_iteration]);
	return(false);
}

template <typename key_t, typename value_t> bool eg::Descriptor<key_t, value_t>::Set::operator==(value_t const p0) const {
	return(master->valuePresent(_iteration, p0));
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t> eg::Descriptor<key_t, value_t>::Set::operator&(value_t const p0) const {
	//TODO: Make this just a return statement (use contructors or whatever)
	Descriptor<key_t, value_t> r0;
	if (master->valuePresent(_iteration, r0))
		r0.Set_addValue(_iteration, p0);
	return(r0);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t> eg::Descriptor<key_t, value_t>::Set::operator&(Set const &p0) const {
	Descriptor<key_t, value_t> r0;
	if (_iteration == p0._iteration) {
		for (auto&& element : p0.master->description[_iteraion]) {
			if (master->valuePresent(_iteration, element))
				r0.Set_addValue(_iteration, element);
		}
	}
	return(r0);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Set::Set(Descriptor<key_t, value_t> *const nmaster, key_t niteration) : master(nmaster), _iteration(niteration) {
}

template <typename key_t, typename value_t> bool eg::Descriptor<key_t, value_t>::valuePresent(key_t const key, value_t const value) const {
	for (auto&& element : description[key]) {
		if (element == value)
			return(true);
	}
	return(false);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::operator bool() const {
	return(!description.empty());
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Descriptor() {
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Descriptor(std::map<key_t const, std::vector<value_t> const> const ndescription) : description(ndiscription) {
}

template <typename key_t, typename value_t> void eg::Descriptor<key_t, value_t>::Container_set(std::vector<value_t>::iterator const iteration, value_t const element) {
	*iteration = element;
}

template <typename key_t, typename value_t> value_t &eg::Descriptor<key_t, value_t>::Container_get(std::vector<value_t>::iterator const iteration) {
	return(*iteration);
}

template <typename key_t, typename value_t> value_t const &eg::Descriptor<key_t, value_t>::Container_get(const std::vector<value_t>::iterator const iteration) const {
	return(*iteration);
}

template <typename key_t, typename value_t> std::vector<value_t>::iterator const eg::Descriptor<key_t, value_t>::Set_getIterator(key_t const key, value_t const value) {
	for (auto itr = description[key].begin(); itr != description[key].end(); itr++) {
		if (*itr == value)
			return(itr);
	}
	description[key].push_back(value);
	return(description[key].end() - 1);
}

template <typename key_t, typename value_t> const std::vector<value_t>::iterator const eg::Descriptor<key_t, value_t>::Set_getIterator(key_t const key, value_t const value) const {
	for (auto itr = description[key].begin(); itr != description[key].end(); itr++) {
		if (*itr == value)
			return(itr);
	}
	return(description[key].end());
}

template <typename key_t, typename value_t> void eg::Descriptor<key_t, value_t>::Set_addValue(key_t const key, value_t const value) {
	if (!valuePresent(key, value))
		description[key].push_back(value);
}
