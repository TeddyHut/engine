#pragma once

#include <utility>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

#include "eg_foundation.h"

//TODO: Make one of these that works using enums cast to ints or something, so that it's easier to debug (AKA use enums in the templates and cast to ints in the class)
//TODO: Project when feeling brainy. Make one of these that can take infinate keys O_O (eg [key0][key1][key2])
//TODO: Add const. I got rid if it, it was being a pain.

namespace eg {
	template <typename key_t = int, typename value_t = int>
	class Descriptor {
		//TODO: Put some 'typedef' or 'using =' in here, because it looks rather messey
		//TODO: Do some cool constexpr stuff so that the compiler can do stuff (like a static initialised descriptor for comparison or something?)
	public:
		//Describes a set key and a vector of values, relative to master
		class Set {
		public:
			//Called on 'descriptor[x][y]'
			//"descriptor vector[x] value[y]"
			util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> operator[](value_t const p0);

			//Called on 'descriptor0[x] + descriptor[y]'
			//"return a descriptor that contains the net values of the two sets"
			Descriptor<key_t, value_t> operator+(Set const &p0);
			
			//Called on 'descriptor[x] + value_t'
			//"return a descriptor that contains set[x] + value_t"
			Descriptor<key_t, value_t> operator+(value_t const p0);

			//Called on 'descriptor0[x] += descriptor1[y]'
			//"add values from descriptor1[y] to descriptor0[x] that are not already present"
			Descriptor<key_t, value_t> &operator+=(Set const &p0);

			//Called on 'descriptor[x] += value_t'
			//"add value_t to descriptor vector [x] if not already present"
			Descriptor<key_t, value_t> &operator+=(value_t const p0);

			//Called on 'descriptor0[x] - descriptor1[y]'
			//"return a descriptor that contains the values that are in vector[x], except for the values that are in vector[y]"
			Descriptor<key_t, value_t> operator-(Set const &p0);

			//Called on 'descriptor0[x] - descriptor1[y]'
			//"return a descriptor that contains the values that are in vector[x], except for value_t"
			Descriptor<key_t, value_t> operator-(value_t const p0);

			//Called on 'descriptor0[x] -= descriptor1[y]'
			//"remove the values that are in descriptor vector[y] from descriptor vector[x]"
			Descriptor<key_t, value_t> &operator-=(Set const &p0);

			//Called on 'descriptor0[x] -= value_t'
			//"remove value_t from descriptor vector[x]"
			Descriptor<key_t, value_t> &operator-=(value_t const p0);

			//Called on 'descriptor0[x] == descriptor1[y]'
			//"descriptor0 vector[x] is equal to descriptor1 vector[y]"
			bool operator==(Set const &p0);

			//Called on 'descriptor[x] == value_t'
			//"descriptor vector[x] contains only value_t"
			bool operator==(value_t const p0);

			//Called on 'descriptor[x] & descriptor[y]'
			//"create a descriptor that contains vector[x] if(x equals y) with the values that were equal in both vectors"
			Descriptor<key_t, value_t> operator&(Set const &p0);

			//Called on 'descriptor[x] & value_t'
			//"create a descriptor that contains vector[x] with only value_t if value_t was already present"
			Descriptor<key_t, value_t> operator&(value_t const p0);

			//Called on '*_cast<Descriptor<key_t, value_t>(descriptor[x])'
			//"create a descriptor that contains only key set[x], with all values that were in key set[x]"
			operator Descriptor<key_t, value_t>();

			//Called on 'descriptor[x] = {value0, value1...}
			//"make the only values in vector [x] those inside the initializer_list"
			Descriptor<key_t, value_t> &operator=(std::vector<value_t> const &p0);

			//Called on 'descriptor[x] = std::move(some vector)'
			//"make the only values in vector [x] those inside some vector"
			Descriptor<key_t, value_t> &operator=(std::vector<value_t> &&p0);

			//Called on 'descriptor[x] = descriptor[y]'
			//"make the values in descriptor vector [x] equal the values in descriptor vector[y]'
			Descriptor<key_t, value_t> &operator=(Set const &p0);

			//Called on 'descriptor[x] = value_t'
			//"make the only value in vector[x] value_t"
			Descriptor<key_t, value_t> &operator=(value_t const p0);

			//Don't think that we need a move version of this (might cause some havoc)

			util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> op_at(value_t const p0);
			Descriptor<key_t, value_t> op_add(Set &p0);
			Descriptor<key_t, value_t> op_add(value_t const p0);
			Descriptor<key_t, value_t> &op_addAssign(Set &p0);
			Descriptor<key_t, value_t> &op_addAssign(value_t const p0);
			Descriptor<key_t, value_t> op_subtract(Set &p0);
			Descriptor<key_t, value_t> op_subtract(value_t const p0);
			Descriptor<key_t, value_t> &op_subtractAssign(Set &p0);
			Descriptor<key_t, value_t> &op_subtractAssign(value_t const p0);
			bool op_compareEqual(Set &p0);
			bool op_compareEqual(value_t const p0);
			Descriptor<key_t, value_t> op_and(Set const &p0);
			Descriptor<key_t, value_t> op_and(value_t const p0);
			Descriptor<key_t, value_t> op_descriptor();
			Descriptor<key_t, value_t> &op_assign(std::vector<value_t> const &p0);
			Descriptor<key_t, value_t> &op_assign(std::vector<value_t> &&p0);
			Descriptor<key_t, value_t> &op_assign(Set const &p0);
			Descriptor<key_t, value_t> &op_assign(value_t const p0);

			Set(Descriptor<key_t, value_t> *const master, key_t const iteration);
		private:
			Descriptor<key_t, value_t> *master;
			key_t _iteration;
		};
		std::map<key_t, std::vector<value_t>> description;


		//Called on 'descriptor[x]'
		//"access descriptor key set [x] (see class "Set" for further operations)"
		Set operator[](key_t const p0);

		//Called on 'descriptor0 == descriptor1'
		//"descriptor0 is equal to descriptor1"
		bool operator==(Descriptor<key_t, value_t> &p0);
		
		//Called on 'descriptor0 < descriptor1'
		//"descriptor0 is by strict-weak-ordering less than descriptor1"
		bool operator<(Descriptor<key_t, value_t> &p0);

		//Called on 'descriptor0 > descriptor1'
		//"descriptor0 is by strict-weak-ordering greater than descriptor1"
		bool operator>(Descriptor<key_t, value_t> &p0);
		
		//Called on 'descriptor0 & descriptor1'
		//"create a descriptor that contains both the values and keys that were in both descriptor0 and descriptor1"
		Descriptor<key_t, value_t> operator&(Descriptor<key_t, value_t> &p0);

		//Called on '*_cast<bool>(descriptor)'
		//"descriptor contains at least one key and one value"
		operator bool();

		//Could use just move assignment (delete copy assignment) and std::foward if simply fowarding into op_assign

		//Copy assignment
		//Called on 'descriptor0 = descriptor1'
		//"make descriptor0 a copy of descriptor1'
		Descriptor<key_t, value_t> &operator=(Descriptor<key_t, value_t> const &p0);

		//Move assignment
		//Called on descriptor0 = std::move(descriptor1)
		//"move the contents of descriptor1 into descriptor0"
		Descriptor<key_t, value_t> &operator=(Descriptor<key_t, value_t> &&p0);

		//Checker members

		//Returns true if value is present in key
		bool valuePresent(key_t const key, value_t const value);
		//Returns true if the key is present
		bool keyPresent(key_t const key);
		//Returns true if there are no keys present
		bool empty();

		//Modification members

		//Clears all keys and values
		void clear();

		typename Set op_at(key_t const p0);
		bool op_compareEqual(Descriptor<key_t, value_t> &p0);
		bool op_lessThan(Descriptor<key_t, value_t> &p0);
		bool op_greaterThan(Descriptor<key_t, value_t> &p0);
		Descriptor<key_t, value_t> op_and(Descriptor<key_t, value_t> &p0);
		bool op_bool();
		Descriptor<key_t, value_t> &op_assign(Descriptor<key_t, value_t> const &p0);
		Descriptor<key_t, value_t> &op_assign(Descriptor<key_t, value_t> &&p0);

		Descriptor();
		Descriptor(std::map<key_t, std::vector<value_t>> const description);
		//Copy constructor
		Descriptor(Descriptor<key_t, value_t> const &p0);
		//Move constructor
		Descriptor(Descriptor<key_t, value_t> &&p0);
	private:
		std::vector<key_t> get_keys();
		std::vector<key_t> get_sorted_keys();
		void sort_values();
		void sort_key(key_t const key);

		//Called on 'descriptor[x][y] = value_t'
		void Container_set(typename std::vector<value_t>::iterator const iteration, value_t const element);
		//Called on '*_cast<value_t>(descriptor[x][y])'
		value_t &Container_get(typename std::vector<value_t>::iterator const iteration);

		//Returns a std::vector::iterator relative to the key and value. Adds -value- to vector -key- if not already there.
		typename std::vector<value_t>::iterator const Set_getIterator(key_t const key, value_t const value);
		//Add -value- to vector -key- if not already there
		void Set_addValue(key_t const key, value_t const value);
		void Set_addValue(key_t const key, std::vector<value_t> &p0);
		void Set_removeValue(key_t const key, value_t const value);
		void Set_removeValue(key_t const key, std::vector<value_t> &p0);
		void Set_addKey(key_t const key);

		friend Set;
		friend Set const;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>;
		friend util::Container::Iterator<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> const;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>;
		friend util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> const;
	};

	template<typename key_t, typename value_t>
	inline util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> eg::Descriptor<key_t, value_t>::Set::operator[](value_t const p0)
	{
		return(op_at(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::operator+(Set const & p0)
	{
		return(op_add(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::operator+(value_t const p0)
	{
		return(op_add(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator+=(Set const & p0)
	{
		return(op_addAssign(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator+=(value_t const p0)
	{
		return(op_addAssign(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::operator-(Set const & p0)
	{
		return(op_subtract(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::operator-(value_t const p0)
	{
		return(op_subtract(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator-=(Set const & p0)
	{
		return(op_subtractAssign(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator-=(value_t const p0)
	{
		return(op_subtractAssign(p0));
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::Set::operator==(Set const & p0)
	{
		return(op_compareEqual(p0))
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::Set::operator==(value_t const p0)
	{
		return(op_compareEqual(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::operator&(Set const & p0)
	{
		return(op_and(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::operator&(value_t const p0)
	{
		return(op_and(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>::Set::operator Descriptor<key_t, value_t>()
	{
		return(op_descriptor());
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator=(std::vector<value_t> const & p0)
	{
		return(op_assign(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator=(std::vector<value_t>&& p0)
	{
		return(op_assign(std::move(p0)));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator=(Set const & p0)
	{
		return(op_assign(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::operator=(value_t const p0)
	{
		return(op_assign(p0));
	}

	template<typename key_t, typename value_t>
	inline util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> Descriptor<key_t, value_t>::Set::op_at(value_t const p0)
	{
		return(util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>::Element(master, master->Set_getIterator(_iteration, p0)));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::op_add(Set & p0)
	{
		eg::Descriptor<key_t, value_t> rtrn = *master;
		if (_iteration == p0._iteration)
			rtrn.Set_addValue(_iteration, p0.master->description.at(_iteration));
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::op_add(value_t const p0)
	{
		eg::Descriptor<key_t, value_t> rtrn = *master;
		rtrn.Set_addValue(_iteration, p0);
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_addAssign(Set & p0)
	{
		if (_iteration == p0._iteration)
			master->Set_addValue(_iteration, p0.master->description.at(_iteration));
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_addAssign(value_t const p0)
	{
		master->Set_addValue(_iteration, p0);
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::op_subtract(Set & p0)
	{
		eg::Descriptor<key_t, value_t> rtrn = *master;
		if (_iteration == p0._iteration)
			rtrn.Set_removeValue(_iteration, p0.master->description.at(_iteration));
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::op_subtract(value_t const p0)
	{
		Descriptor<key_t, value_t> rtrn = *master;
		rtrn.Set_removeValue(_iteration, p0);
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_subtractAssign(Set & p0)
	{
		if (_iteration == p0._iteration)
			master->Set_removeValue(_iteration, p0.master->description.at(_iteration));
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_subtractAssign(value_t const p0)
	{
		if (_iteration == p0._iteration)
			master->Set_removeValue(_iteration, p0);
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::Set::op_compareEqual(Set & p0)
	{
		if (_iteration == p0._iteration) {
			master->sort_key(_iteration);
			p0.master->sort_key(_iteration);
			return(master->description.at(_iteration) == p0.master->description.at(_iteration));
		}
		return(false);
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::Set::op_compareEqual(value_t const p0)
	{
		return((master->description.at(_iteration).size() == 1) && (master->description.at(_iteration).at(0) == p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::op_and(Set const & p0)
	{
		Descriptor<key_t, value_t> rtrn;
		if (_iteration == p0._iteration) {
			master->sort_key(_iteration);
			p0.master->sort_key(_iteration);
			std::set_intersection(
				master->description.at(_iteration).begin(), master->description.at(_iteration).end(),
				p0.master->description.at(_iteration).begin(), p0.master->description.at(_iteration).end(),
				std::back_inserter((*(rtrn.description.insert(std::make_pair(_iteration, std::vector<value_t>::vector())).first)).second));
			if (!rtrn.op_bool())
				rtrn.clear();
		}
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::op_and(value_t const p0)
	{
		Descriptor<key_t, value_t> rtrn;
		if (master->valuePresent(_iteration, p0))
			rtrn.Set_addValue(_iteration, p0);
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::Set::op_descriptor()
	{
		Descriptor<key_t, value_t> rtrn;
		rtrn.Set_addValue(_iteration, master->description.at(key));
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_assign(std::vector<value_t> const & p0)
	{
		master->description.at(_iteration) = p0;
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_assign(std::vector<value_t>&& p0)
	{
		master->description.at(_iteration) = std::move(p0);
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_assign(Set const & p0)
	{
		if (_iteration == p0._iteration)
			master->description.at(_iteration) = p0.master->description.at(_iteration);
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::Set::op_assign(value_t const p0)
	{
		master->description.at(_iteration).clear();
		master->description.at(_iteration).push_back(p0);
		return(*master);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>::Set::Set(Descriptor<key_t, value_t>* const master, key_t const iteration) : master(master), _iteration(iteration)
	{
	}

	template<typename key_t, typename value_t>
	inline typename Descriptor<key_t, value_t>::Set Descriptor<key_t, value_t>::operator[](key_t const p0)
	{
		return(op_at(p0));
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::operator==(Descriptor<key_t, value_t>& p0)
	{
		return(op_compareEqual(p0));
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::operator<(Descriptor<key_t, value_t>& p0)
	{
		return(op_lessThan(p0));
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::operator>(Descriptor<key_t, value_t>& p0)
	{
		return(op_greaterThan(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::operator&(Descriptor<key_t, value_t>& p0)
	{
		return(op_and(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>::operator bool()
	{
		return(op_bool());
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::operator=(Descriptor<key_t, value_t> const & p0)
	{
		return(op_assign(p0));
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::operator=(Descriptor<key_t, value_t>&& p0)
	{
		return(op_assign(std::move(p0)));
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::valuePresent(key_t const key, value_t const value)
	{
		if (description.count(key)) {
			if (std::find(description.at(key).begin(), description.at(key).end(), value) != description.at(key).end()) {
				return(true);
			}
		}
		return(false);
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::keyPresent(key_t const key)
	{
		return(std::find_if(description.begin(), description.end(), [key](std::pair<key_t, std::vector<value_t>> const &p0) {
			return(p0.first == key);
		}) != description.end());
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::empty()
	{
		return(description.empty());
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::clear()
	{
		description.clear();
	}

	template<typename key_t, typename value_t>
	inline typename Descriptor<key_t, value_t>::Set Descriptor<key_t, value_t>::op_at(key_t const p0)
	{
		if (!keyPresent(p0))
			Set_addKey(p0);
		return(Set::Set(this, p0));
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::op_compareEqual(Descriptor<key_t, value_t>& p0)
	{
		//Find a more std::way to implement this
		auto keys = get_sorted_keys();
		if (keys == p0.get_sorted_keys()) {
			sort_values();
			p0.sort_values();
			for (auto &&element : keys) {
				if (description.at(element) != p0.description.at(element)) {
					return(false);
				}
			}
			return(true);
		}
		return(false);
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::op_lessThan(Descriptor<key_t, value_t>& p0)
	{
		auto keys = get_sorted_keys();
		if (keys == p0.get_sorted_keys()) {
			sort_values();
			p0.sort_values();
			for (auto &&element : keys) {
				if (description.at(element) != p0.description.at(element)) {
					return(description.at(element) < p0.description.at(element));
				}
			}
			return(false);
		}
		return(keys < okeys);
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::op_greaterThan(Descriptor<key_t, value_t>& p0)
	{
		auto keys = get_sorted_keys();
		if (keys == p0.get_sorted_keys()) {
			sort_values();
			p0.sort_values();
			for (auto &&element : keys) {
				if (description.at(element) != p0.description.at(element)) {
					return(description.at(element) > p0.description.at(element));
				}
			}
			return(false);
		}
		return(keys > okeys);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t> Descriptor<key_t, value_t>::op_and(Descriptor<key_t, value_t>& p0)
	{
		eg::Descriptor<key_t, value_t> rtrn;
		auto keys = get_sorted_keys();
		auto p0_keys = p0.get_keys();
		std::vector<key_t> common_keys;
		std::set_intersection(keys.begin(), keys.end(), p0_keys.begin(), p0_keys.end(), std::back_inserter(common_keys));
		if (common_keys.size() == 0)
			return(rtrn);
		for (auto &&key : common_keys) {
			sort_key(key);
			p0.sort_key(key);
			std::set_intersection(
				description.at(key).begin(), description.at(key).end(),
				p0.description.at(key).begin(), p0.description.at(key).end(),
				std::back_inserter((*(rtrn.description.insert(std::make_pair(key, std::vector<value_t>::vector())).first)).second));
		}
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline bool Descriptor<key_t, value_t>::op_bool()
	{
		if (description.empty())
			return(false);
		for (auto &&element : description) {
			if (!element.second.empty())
				return(true);
		}
		return(false);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::op_assign(Descriptor<key_t, value_t> const & p0)
	{
		description = p0.description;
		return(*this);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>& Descriptor<key_t, value_t>::op_assign(Descriptor<key_t, value_t>&& p0)
	{
		description = std::move(p0.description);
		return(*this);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>::Descriptor()
	{
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>::Descriptor(std::map<key_t, std::vector<value_t>> const description) : description(description)
	{
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>::Descriptor(Descriptor<key_t, value_t> const & p0)
	{
		op_assign(p0);
	}

	template<typename key_t, typename value_t>
	inline Descriptor<key_t, value_t>::Descriptor(Descriptor<key_t, value_t>&& p0)
	{
		op_assign(std::move(p0));
	}

	template<typename key_t, typename value_t>
	inline std::vector<key_t> Descriptor<key_t, value_t>::get_keys()
	{
		std::vector<key_t> rtrn;
		rtrn.reserve(description.size());
		std::for_each(description.begin(), description.end(), [&](std::pair<key_t, std::vector<value_t>> const &p0) { rtrn.push_back(p0.first); });
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline std::vector<key_t> Descriptor<key_t, value_t>::get_sorted_keys()
	{
		auto rtrn = get_keys();
		std::sort(rtrn.begin(), rtrn.end());
		return(rtrn);
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::sort_values()
	{
		//std::for_each didn't work
		for (auto &&element : description) {
			std::sort(element.second.begin(), element.second.end());
		}
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::sort_key(key_t const key)
	{
	if (!std::is_sorted(description.at(key).begin(), description.at(key).end()))
		std::sort(description.at(key).begin(), description.at(key).end());
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::Container_set(typename std::vector<value_t>::iterator const iteration, value_t const element)
	{
		*iteration = element;
	}

	template<typename key_t, typename value_t>
	inline value_t & Descriptor<key_t, value_t>::Container_get(typename std::vector<value_t>::iterator const iteration)
	{
		return(*iteration);
	}

	template<typename key_t, typename value_t>
	inline typename std::vector<value_t>::iterator const Descriptor<key_t, value_t>::Set_getIterator(key_t const key, value_t const value)
	{
		return(std::find(description.at(key).begin(), description.at(key).end(), value));
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::Set_addValue(key_t const key, value_t const value)
	{
		if (!valuePresent(key, value))
			description[key].push_back(value);
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::Set_addValue(key_t const key, std::vector<value_t>& p0)
	{
		if (!keyPresent(key))
			Set_addKey(key);
		sort_key(key);
		if (!std::is_sorted(p0.begin(), p0.end()))
			std::sort(p0.begin(), p0.end());
		std::set_difference(p0.begin(), p0.end(), description.at(key).begin(), description.at(key).end(), std::back_inserter(description.at(key)));	//Likely point of error
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::Set_removeValue(key_t const key, value_t const value)
	{
		description.at(key).erase(std::remove(description.at(key).begin(), description.at(key).end(), value), description.at(key).end());
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::Set_removeValue(key_t const key, std::vector<value_t>& p0)
	{
		description.at(key).erase(
			std::remove_if(description.at(key).begin(), description.at(key).end(),
				[=](value_t const &p1) {
			return(std::find(p0.begin(), p0.end(), p1) != description.at(key).end()) }),
			description.at(key).end());
	}

	template<typename key_t, typename value_t>
	inline void Descriptor<key_t, value_t>::Set_addKey(key_t const key)
	{
		description.insert(std::make_pair(key, std::vector<value_t>::vector()));
	}

}
