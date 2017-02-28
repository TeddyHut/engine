#pragma once

#include <utility>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include "eg_foundation.h"
#include "eg_set.h"

//TODO: Make one of these that works using enums cast to ints or something, so that it's easier to debug (AKA use enums in the templates and cast to ints in the class)
//TODO: Project when feeling brainy. Make one of these that can take infinate keys O_O (eg [key0][key1][key2])
//TODO: Add const. I got rid if it, it was being a pain.
//TODO: Work out a way to get the definition outside the declaration. It doesn't like it because Descriptor isn't specialized
//TODO: Could actually make template overloads for some of the functions that only overload between Set and value... They all call master->add/remove p0. Or not. Would need a bit of framwork or something. Just an idea.

namespace eg {
	template <typename key_t = unsigned int, typename value_t = unsigned int>
	class Descriptor {
		//TODO: Put some 'typedef' or 'using =' in here, because it looks rather messey
		//TODO: Do some cool constexpr stuff so that the compiler can do stuff (like a static initialised descriptor for comparison or something?)
	public:
		typedef key_t key_type;
		typedef value_t value_type;

		std::map<key_t, std::vector<value_t>> description;


		//Called on 'descriptor[x]'
		//"access descriptor key set [x] (see class "Set" for further operations)"
		Set<key_t, value_t, Descriptor<key_t, value_t>> operator[](key_t const p0) {
			return(op_at(p0));
		}

		Set<key_t, value_t, Descriptor<key_t, value_t> const> operator[](key_t const p0) const {
			return(op_at(p0));
		}

		//Called on 'descriptor0 == descriptor1'
		//"descriptor0 is equal to descriptor1"
		bool operator==(Descriptor<key_t, value_t> const &p0) const {
			return(op_compareEqual(p0));
		}

		//Called on 'descriptor0 < descriptor1'
		//"descriptor0 is by strict-weak-ordering less than descriptor1"
		bool operator<(Descriptor<key_t, value_t> const &p0) const {
			return(op_lessThan(p0));
		}

		//Called on 'descriptor0 > descriptor1'
		//"descriptor0 is by strict-weak-ordering greater than descriptor1"
		bool operator>(Descriptor<key_t, value_t> const &p0) const {
			return(op_greaterThan(p0));
		}

		//Called on 'descriptor0 & descriptor1'
		//"create a descriptor that contains both the values and keys that were in both descriptor0 and descriptor1"
		Descriptor<key_t, value_t> operator&(Descriptor<key_t, value_t> const &p0) const {
			return(op_and(p0));
		}

		//Called on '*_cast<bool>(descriptor)'
		//"descriptor contains at least one key and one value"
		operator bool() const {
			return(op_bool());
		}

		//Could use just move assignment (delete copy assignment) and std::foward if simply fowarding into op_assign

		//Copy assignment
		//Called on 'descriptor0 = descriptor1'
		//"make descriptor0 a copy of descriptor1'
		Descriptor<key_t, value_t> &operator=(Descriptor<key_t, value_t> const &p0) {
			return(op_assign(p0));
		}

		//Move assignment
		//Called on descriptor0 = std::move(descriptor1)
		//"move the contents of descriptor1 into descriptor0"
		Descriptor<key_t, value_t> &operator=(Descriptor<key_t, value_t> &&p0) {
			return(op_assign(std::move(p0)));
		}

		//Checker members

		//Returns true if value is present in key
		bool valuePresent(key_t const key, value_t const value) const {
			if (description.count(key)) {
				if (std::find(description.at(key).begin(), description.at(key).end(), value) != description.at(key).end()) {
					return(true);
				}
			}
			return(false);
		}
		//Returns true if the key is present
		bool keyPresent(key_t const key) const {
			return(std::find_if(description.begin(), description.end(), [key](std::pair<key_t, std::vector<value_t>> const &p0) {
				return(p0.first == key);
			}) != description.end());
		}
		//Returns true if there are no keys present
		bool empty() const {
			return(description.empty());
		}

		//Modification members

		//Clears all keys and values
		void clear() {
			description.clear();
		}

		Set<key_t, value_t, Descriptor<key_t, value_t>> op_at(key_t const p0) {
			if (!keyPresent(p0))
				Set_addKey(p0);
			return(Set<key_t, value_t, Descriptor<key_t, value_t>>(this, p0));
		}
		Set<key_t, value_t, Descriptor<key_t, value_t> const> op_at(key_t const p0) const {
			return(Set<key_t, value_t, Descriptor<key_t, value_t> const>(this, p0));
		}

		bool op_compareEqual(Descriptor<key_t, value_t> const &p0) const {
			//Find a more std::way to implement this
			auto keys = get_sorted_keys();
			if (keys == p0.get_sorted_keys()) {
				for (auto &&element : keys) {
					if ((!key_sorted(element)) || (!p0.key_sorted(element)))
						return(false);
					if (description.at(element) != p0.description.at(element)) {
						return(false);
					}
				}
				return(true);
			}
			return(false);
		}

		bool op_lessThan(Descriptor<key_t, value_t> const &p0) const {
			auto keys = get_sorted_keys();
			auto okeys = p0.get_sorted_keys();
			if (keys == okeys) {
				for (auto &&element : keys) {
					if ((!key_sorted(element)) || (!p0.key_sorted(element)))
						return(false);
					if (description.at(element) != p0.description.at(element)) {
						return(description.at(element) < p0.description.at(element));
					}
				}
				return(false);
			}
			return(keys < okeys);
		}

		bool op_greaterThan(Descriptor<key_t, value_t> const &p0) const {
			auto keys = get_sorted_keys();
			auto okeys = p0.get_sorted_keys();
			if (keys == okeys) {
				for (auto &&element : keys) {
					if ((!key_sorted(element)) || (!p0.key_sorted(element)))
						return(false);
					if (description.at(element) != p0.description.at(element)) {
						return(description.at(element) > p0.description.at(element));
					}
				}
				return(false);
			}
			return(keys > okeys);
		}

		Descriptor<key_t, value_t> op_and(Descriptor<key_t, value_t> const &p0) const {
			eg::Descriptor<key_t, value_t> rtrn;
			auto keys = get_sorted_keys();
			auto p0_keys = p0.get_keys();
			std::vector<key_t> common_keys;
			std::set_intersection(keys.begin(), keys.end(), p0_keys.begin(), p0_keys.end(), std::back_inserter(common_keys));
			if (common_keys.size() == 0)
				return(rtrn);
			for (auto &&key : common_keys) {
				if ((!key_sorted(key)) || (!p0.key_sorted(key)))
					continue;
				std::vector<value_t> vec;
				std::set_intersection(
					description.at(key).begin(), description.at(key).end(),
					p0.description.at(key).begin(), p0.description.at(key).end(),
					std::back_inserter((*(rtrn.description.insert(std::make_pair(key, vec)).first)).second));
			}
			return(rtrn);
		}

		bool op_bool() const {
			if (description.empty())
				return(false);
			for (auto &&element : description) {
				if (!element.second.empty())
					return(true);
			}
			return(false);
		}

		Descriptor<key_t, value_t> &op_assign(Descriptor<key_t, value_t> const &p0) {
			description = p0.description;
			return(*this);
		}
		Descriptor<key_t, value_t> &op_assign(Descriptor<key_t, value_t> &&p0) {
			description = std::move(p0.description);
			return(*this);
		}

		Descriptor() {}
		Descriptor(std::map<key_t, std::vector<value_t>> const description) : description(description) {}
		//Copy constructor
		Descriptor(Descriptor<key_t, value_t> const &p0) {
			op_assign(p0);
		}
		//Move constructor
		Descriptor(Descriptor<key_t, value_t> &&p0) {
			op_assign(std::move(p0));
		}
	private:
		std::vector<key_t> get_keys() const {
			std::vector<key_t> rtrn;
			rtrn.reserve(description.size());
			std::for_each(description.begin(), description.end(), [&](std::pair<key_t, std::vector<value_t>> const &p0) { rtrn.push_back(p0.first); });
			return(rtrn);
		}

		std::vector<key_t> get_sorted_keys() const {
			auto rtrn = get_keys();
			std::sort(rtrn.begin(), rtrn.end());
			return(rtrn);
		}

		void sort_values() {
			//std::for_each didn't work
			for (auto &&element : description) {
				std::sort(element.second.begin(), element.second.end());
			}
		}

		void sort_key(key_t const key) {
			if (!std::is_sorted(description.at(key).begin(), description.at(key).end()))
				std::sort(description.at(key).begin(), description.at(key).end());
		}

		bool key_sorted(key_t const key) const {
			return(std::is_sorted(description.at(key).begin(), description.at(key).end()));
		}

		//Called on 'descriptor[x][y] = value_t'
		void Container_set(typename std::vector<value_t>::iterator const iteration, value_t const element) {
			*iteration = element;
		}

		//Called on '*_cast<value_t>(descriptor[x][y])'
		value_t &Container_get(typename std::vector<value_t>::iterator const iteration) {
			return(*iteration);
		}
		value_t const &Container_get(typename std::vector<value_t>::const_iterator const iteration) const {
			return(*iteration);
		}

		//Returns a std::vector::iterator relative to the key and value. Adds -value- to vector -key- if not already there.
		typename std::vector<value_t>::iterator Set_getIterator(key_t const key, value_t const value) {
			auto itr = std::find(description.at(key).begin(), description.at(key).end(), value);
			if (itr == description.at(key).end()) {
				Set_addValue(key, value);
				return(std::find(description.at(key).begin(), description.at(key).end(), value));
			}
			return(itr);
		}
		typename std::vector<value_t>::const_iterator Set_getIterator(key_t const key, value_t const value) const {
			return(std::find(description.at(key).begin(), description.at(key).end(), value));
		}

		//Add -value- to vector -key- if not already there
		void Set_addValue(key_t const key, value_t const value) {
			if (!valuePresent(key, value)) {
				description[key].push_back(value);
				sort_key(key);
			}
		}

		void Set_addValue(key_t const key, std::vector<value_t> &&p0) {
			if (!keyPresent(key))
				Set_addKey(key);
			sort_key(key);
			if (!std::is_sorted(p0.begin(), p0.end()))
				std::sort(p0.begin(), p0.end());
			std::set_difference(p0.begin(), p0.end(), description.at(key).begin(), description.at(key).end(), std::back_inserter(description.at(key)));
			sort_key(key);
		}

		void Set_addValue(key_t const key, std::vector<value_t> const &p0) {
			if (!keyPresent(key))
				Set_addKey(key);
			sort_key(key);
			if (!std::is_sorted(p0.begin(), p0.end())) {
				auto mutable_p0 = p0;
				std::sort(mutable_p0.begin(), mutable_p0.end());
				std::set_difference(mutable_p0.begin(), mutable_p0.end(), description.at(key).begin(), description.at(key).end(), std::back_inserter(description.at(key)));
			}
			else
				std::set_difference(p0.begin(), p0.end(), description.at(key).begin(), description.at(key).end(), std::back_inserter(description.at(key)));
			sort_key(key);
		}

		void Set_removeValue(key_t const key, value_t const value) {
			description.at(key).erase(std::remove(description.at(key).begin(), description.at(key).end(), value), description.at(key).end());
			sort_key(key);
		}

		void Set_removeValue(key_t const key, std::vector<value_t> const &p0) {
			description.at(key).erase(
				std::remove_if(description.at(key).begin(), description.at(key).end(),
					[&](value_t const &p1) {
				return(std::find(p0.begin(), p0.end(), p1) != p0.end()); }),
				description.at(key).end());
			sort_key(key);
		}

		void Set_addKey(key_t const key) {
			//Todo: Find the correct way to insert default initialized objects into an expression.
			std::vector<value_t> vec;
			description.insert(std::make_pair(key, vec));
		}

		friend Set<key_t, value_t, Descriptor<key_t, value_t>>;
		friend Set<key_t, value_t, Descriptor<key_t, value_t> const>;
		friend Const_Set<key_t, value_t, Descriptor<key_t, value_t>>;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>;
		//friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> const;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>;
		//friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> const;
	};
}
