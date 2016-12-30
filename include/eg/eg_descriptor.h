#pragma once

#include <utility>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include "eg_foundation.h"

//TODO: Make one of these that works using enums cast to ints or something, so that it's easier to debug (AKA use enums in the templates and cast to ints in the class)
//TODO: Project when feeling brainy. Make one of these that can take infinate keys O_O (eg [key0][key1][key2])

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
			//Maybe this should have been a += (makes more sense I guess...)
			Set &operator=(Set const &p0);
			//Called on 'descriptor[x] = value_t'
			//"add value_t to descriptor vector [x] if not already there"
			Set &operator=(value_t const p0);

			//Called on 'descriptor[x][y]'
			//"descriptor vector[x] value[y]"
			auto operator[](value_t const p0)->util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>;
			auto operator[](value_t const p0) const->util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::const_iterator const> const;

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

		auto operator[](key_t const p0)->Set;
		auto operator[](key_t const p0) const->Set const;

		//Called on 'descriptor0 == descriptor1'
		//"descriptor0 is equal to descriptor1"
		bool operator==(Descriptor<key_t, value_t> const &p0) const;
		
		//Called on 'descriptor0 & descriptor1'
		//"create a descriptor that contains both the values and keys that were in both descriptor0 and descriptor1"
		Descriptor<key_t, value_t> operator&(Descriptor<key_t, value_t> const &p0) const;

		//Called on '*_cast<bool>(descriptor)'
		//"descriptor contains at least one key and one value"
		operator bool() const;

		Descriptor();
		Descriptor(std::map<key_t, std::vector<value_t>> const ndescription);
	private:
		std::vector<key_t> get_keys() const;
		std::vector<key_t> get_sorted_keys() const;
		void sort_values();

		//Called on 'descriptor[x][y] = value_t'
		void Container_set(typename std::vector<value_t>::iterator const iteration, value_t const element);
		//Called on '*_cast<value_t>(descriptor[x][y])'
		value_t &Container_get(typename std::vector<value_t>::iterator const iteration);
		value_t const &Container_get(typename std::vector<value_t>::const_iterator const iteration) const;

		//Returns a std::vector::iterator relative to the key and value. Adds -value- to vector -key- if not already there.
		typename std::vector<value_t>::iterator const Set_getIterator(key_t const key, value_t const value);
		typename std::vector<value_t>::const_iterator const Set_getIterator(key_t const key, value_t const value) const;
		//Add -value- to vector -key- if not already there
		void Set_addValue(key_t const key, value_t const value);

		friend Set;
		friend Set const;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> const;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> const;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::const_iterator const>;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::const_iterator const> const;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::const_iterator const>;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::const_iterator const> const;
	};
}

template <typename key_t, typename value_t> typename eg::Descriptor<key_t, value_t>::Set &eg::Descriptor<key_t, value_t>::Set::operator=(Set const &p0) {
	if (_iteratation == p0._iteration) {
		for (auto&& element : p0.master->description[_iteration]) {
			master->Set_addValue(_iteration, element);
		}
	}
	return(*this);
}

template <typename key_t, typename value_t> typename eg::Descriptor<key_t, value_t>::Set &eg::Descriptor<key_t, value_t>::Set::operator=(value_t const p0) {
	master->Set_addValue(_iteration, p0);
	return(*this);
}

template <typename key_t, typename value_t> auto eg::Descriptor<key_t, value_t>::Set::operator[](value_t const p0)->util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> {
	return(util::Container::Element<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator>::Element(master, master->Set_getIterator(_iteration, p0)));
}

template <typename key_t, typename value_t> auto eg::Descriptor<key_t, value_t>::Set::operator[](value_t const p0) const->util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::const_iterator const> const {
	return(util::Container::Element<Descriptor<key_t, value_t>, value_t, std::vector<value_t>::iterator>::Element(master, master->Set_getIterator(_iteration, p0)));
}

template <typename key_t, typename value_t> bool eg::Descriptor<key_t, value_t>::Set::operator==(Set const &p0) const {
	if (_iteration == p0._iteration) {	//If statement is probably the smartest thing (due to how map works)
		sort_values();
		p0.master->sort_values();
		return(master->description[_iteration] == p0.master->description[_iteration]);
	}
	return(false);
}

template <typename key_t, typename value_t> bool eg::Descriptor<key_t, value_t>::Set::operator==(value_t const p0) const {
	return(master->valuePresent(_iteration, p0));
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t> eg::Descriptor<key_t, value_t>::Set::operator&(value_t const p0) const {
	//TODO: Make this just a return statement (use contructors or whatever)
	Descriptor<key_t, value_t> r0;
	if (master->valuePresent(_iteration, p0))
		r0.Set_addValue(_iteration, p0);
	return(r0);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t> eg::Descriptor<key_t, value_t>::Set::operator&(Set const &p0) const {
	Descriptor<key_t, value_t> r0;
	if (_iteration == p0._iteration) {
		for (auto&& element : p0.master->description[_iteration]) {
			if (master->valuePresent(_iteration, element))
				r0.Set_addValue(_iteration, element);
		}
	}
	return(r0);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Set::Set(Descriptor<key_t, value_t> *const nmaster, key_t niteration) : master(nmaster), _iteration(niteration) {
}

template <typename key_t, typename value_t> bool eg::Descriptor<key_t, value_t>::valuePresent(key_t const key, value_t const value) const {
	if (description.count(key)) {
		for (auto&& element : description.at(key)) {
			if (element == value)
				return(true);
		}
	}
	return(false);
}

template <typename key_t, typename value_t> auto eg::Descriptor<key_t, value_t>::operator[](key_t const p0)->Set {
	return(Set::Set(this, p0));
}

template <typename key_t, typename value_t> auto eg::Descriptor<key_t, value_t>::operator[](key_t const p0) const->Set const {
	return(Set::Set(this, p0));
}

template <typename key_t, typename value_t> bool eg::Descriptor<key_t, value_t>::operator==(eg::Descriptor<key_t, value_t> const &p0) const {
	auto keys = get_sorted_keys();
	if (keys == p0.get_sorted_keys()) {
		//I'm going to be evil.
		const_cast<Descriptor<key_t, value_t> *>(this)->sort_values();
		//Wasn't sure whether not doing a pointer on here would only modify a copy.
		const_cast<Descriptor<key_t, value_t> *>(&p0)->sort_values();
		for (auto &&element : keys) {
			if (description.at(element) != p0.description.at(element)) {
				return(false);
			}
		}
		return(true);
	}
	return(false);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t> eg::Descriptor<key_t, value_t>::operator&(eg::Descriptor<key_t, value_t> const &p0) const {
	eg::Descriptor<key_t, value_t> rtrn;
	auto keys = get_keys();
	auto p0_keys = p0.get_keys();
	std::vector<key_t> common_keys;
	for (auto &&element : keys) {
		for (auto &&p0_element : p0_keys) {
			if (element == p0_element) {
				common_keys.push_back(element);
				break;
			}
		}
	}
	if (common_keys.size() == 0)
		return(rtrn);
	for (auto &&key : common_keys) {
		for (auto &&value : description.at(key)) {
			if (p0.valuePresent(key, value))
				rtrn[key] = value;
		}
	}
	return(rtrn);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::operator bool() const {
	if (description.empty())
		return(false);
	for (auto &&element : description) {
		if (!element.second.empty())
			return(true);
	}
	return(false);
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Descriptor() {
}

template <typename key_t, typename value_t> eg::Descriptor<key_t, value_t>::Descriptor(std::map<key_t, std::vector<value_t>> const ndescription) : description(ndescription) {
}

template <typename key_t, typename value_t> std::vector<key_t> eg::Descriptor<key_t, value_t>::get_keys() const {
	std::vector<key_t> rtrn;
	//Add all keys to the vector
	for (auto &&element : description) {
		rtrn.push_back(element.first);
	}
	return(rtrn);
}

template <typename key_t, typename value_t> std::vector<key_t> eg::Descriptor<key_t, value_t>::get_sorted_keys() const {
	auto rtrn = get_keys();
	std::sort(rtrn.begin(), rtrn.end());
	return(rtrn);
}

template <typename key_t, typename value_t> void eg::Descriptor<key_t, value_t>::sort_values() {
	for (auto &&element : description) {
		std::sort(element.second.begin(), element.second.end());
	}
}

template <typename key_t, typename value_t> void eg::Descriptor<key_t, value_t>::Container_set(typename std::vector<value_t>::iterator const iteration, value_t const element) {
	*iteration = element;
}

template <typename key_t, typename value_t> value_t &eg::Descriptor<key_t, value_t>::Container_get(typename std::vector<value_t>::iterator const iteration) {
	return(*iteration);
}

template <typename key_t, typename value_t> value_t const &eg::Descriptor<key_t, value_t>::Container_get(typename std::vector<value_t>::const_iterator const iteration) const {
	return(*iteration);
}

template <typename key_t, typename value_t> typename std::vector<value_t>::iterator const eg::Descriptor<key_t, value_t>::Set_getIterator(key_t const key, value_t const value) {
	for (auto itr = description[key].begin(); itr != description[key].end(); itr++) {
		if (*itr == value)
			return(itr);
	}
	description[key].push_back(value);
	return(description[key].end() - 1);
}

template <typename key_t, typename value_t> typename std::vector<value_t>::const_iterator const eg::Descriptor<key_t, value_t>::Set_getIterator(key_t const key, value_t const value) const {
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
