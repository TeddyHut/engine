#pragma once

#include <utility>
#include <vector>
#include <map>
#include <algorithm>

#include "eg_foundation.h"

namespace eg {
	template <typename key_t, typename value_t>
	class Descriptor;

	template <typename key_t, typename value_t, typename descriptor_t>
	class Const_Set {
	public:
		util::Container::Element<descriptor_t, value_t, typename std::vector<value_t>::const_iterator> op_at(value_t const p0) const {
			return(util::Container::Element<descriptor_t, value_t, typename std::vector<value_t>::const_iterator>::Element(master, master->Set_getIterator(_iteration, p0)));
		}

		descriptor_t op_add(std::vector<value_t> const &p0) const {
			descriptor_t rtrn = *master;
			rtrn.Set_addValue(_iteration, p0);
			return(rtrn);
		}
		descriptor_t op_add(std::vector<value_t> &&p0) const {
			descriptor_t rtrn = *master;
			rtrn.Set_addValue(_iteration, std::move(p0));
			return(rtrn);
		}
		descriptor_t op_add(Const_Set const &p0) const {
			descriptor_t rtrn = *master;
			if (_iteration == p0._iteration)
				rtrn.Set_addValue(_iteration, p0.master->description.at(_iteration));
			return(rtrn);
		}
		descriptor_t op_add(value_t const p0) const {
			descriptor_t rtrn = *master;
			rtrn.Set_addValue(_iteration, p0);
			return(rtrn);
		}

		descriptor_t op_subtract(std::vector<value_t> const &p0) const {
			descriptor_t rtrn = *master;
			rtrn.Set_removeValue(_iteration, p0);
			return(rtrn);
		}
		descriptor_t op_subtract(Const_Set const &p0) const {
			descriptor_t rtrn = *master;
			if (_iteration == p0._iteration)
				rtrn.Set_removeValue(_iteration, p0.master->description.at(_iteration));
			return(rtrn);
		}
		descriptor_t op_subtract(value_t const p0) const {
			descriptor_t rtrn = *master;
			rtrn.Set_removeValue(_iteration, p0);
			return(rtrn);
		}
		bool op_compareEqual(Const_Set const &p0) const {
			if (_iteration == p0._iteration) {
				if ((!master->key_sorted(_iteration)) || (!p0.master->key_sorted(_iteration)))
					return(false);
				return(master->description.at(_iteration) == p0.master->description.at(_iteration));
			}
			return(false);
		}
		bool op_compareEqual(value_t const p0) const {
			return((master->description.at(_iteration).size() == 1) && (master->description.at(_iteration).at(0) == p0));
		}

		descriptor_t op_and(Const_Set const &p0) const {
			descriptor_t rtrn;
			if (_iteration == p0._iteration) {
				if ((!master->key_sorted(_iteration)) || (!p0.master->key_sorted(_iteration)))
					return(rtrn);
				std::set_intersection(
					master->description.at(_iteration).begin(), master->description.at(_iteration).end(),
					p0.master->description.at(_iteration).begin(), p0.master->description.at(_iteration).end(),
					std::back_inserter((*(rtrn.description.insert(std::make_pair(_iteration, std::vector<value_t>::vector())).first)).second));
				if (!rtrn.op_bool())
					rtrn.clear();
			}
			return(rtrn);
		}
		descriptor_t op_and(value_t const p0) const {
			descriptor_t rtrn;
			if (master->valuePresent(_iteration, p0))
				rtrn.Set_addValue(_iteration, p0);
			return(rtrn);
		}

		descriptor_t op_descriptor() const {
			descriptor_t rtrn;
			rtrn.Set_addValue(_iteration, master->description.at(_iteration));
			return(rtrn);
		}

		//Called on 'descriptor[x][y]'
		//"descriptor vector[x] value[y]"
		util::Container::Element<descriptor_t, value_t, typename std::vector<value_t>::const_iterator> operator[](value_t const p0) const {
			return(op_at(p0));
		}

		//Called on 'descriptor0[x] + vector{value0, value1, ...}'
		//"return a descriptor that contains the net values of the two sets"
		descriptor_t operator+(std::vector<value_t> const &p0) const {
			return(op_add(p0));
		}
		descriptor_t operator+(std::vector<value_t> &&p0) const {
			return(op_add(std::move(p0)));
		}

		//Called on 'descriptor0[x] + descriptor[y]'
		//"return a descriptor that contains the net values of the two sets"
		descriptor_t operator+(Const_Set const &p0) const {
			return(op_add(p0));
		}

		//Called on 'descriptor[x] + value_t'
		//"return a descriptor that contains set[x] + value_t"
		descriptor_t operator+(value_t const p0) const {
			return(op_add(p0));
		}

		//Called on 'descriptor0[x] - vector{value0, value1, ...}'
		//"return a descriptor that contains the values that are in vector[x], except for the values that are in vector"
		descriptor_t operator-(std::vector<value_t> const &p0) const {
			return(op_subtract(p0));
		}

		//Called on 'descriptor0[x] - descriptor1[y]'
		//"return a descriptor that contains the values that are in vector[x], except for the values that are in vector[y]"
		descriptor_t operator-(Const_Set const &p0) const {
			return(op_subtract(p0));
		}

		//Called on 'descriptor0[x] - descriptor1[y]'
		//"return a descriptor that contains the values that are in vector[x], except for value_t"
		descriptor_t operator-(value_t const p0) const {
			return(op_subtract(p0));
		}

		//Called on 'descriptor0[x] == descriptor1[y]'
		//"descriptor0 vector[x] is equal to descriptor1 vector[y]"
		bool operator==(Const_Set const &p0) const {
			return(op_compareEqual(p0));
		}

		//Called on 'descriptor[x] == value_t'
		//"descriptor vector[x] contains only value_t"
		bool operator==(value_t const p0) const {
			return(op_compareEqual(p0));
		}

		//Called on 'descriptor[x] & descriptor[y]'
		//"create a descriptor that contains vector[x] if(x equals y) with the values that were equal in both vectors"
		descriptor_t operator&(Const_Set const &p0) const {
			return(op_and(p0));
		}

		//Called on 'descriptor[x] & value_t'
		//"create a descriptor that contains vector[x] with only value_t if value_t was already present"
		descriptor_t operator&(value_t const p0) const {
			return(op_and(p0));
		}

		//Called on '*_cast<descriptor_t(descriptor[x])'
		//"create a descriptor that contains only key set[x], with all values that were in key set[x]"
		operator descriptor_t() const {
			return(op_descriptor());
		}

		//Don't think that we need a move version of this (might cause some havoc)

		Const_Set(descriptor_t const *const master, key_t const iteration) : master(master), _iteration(iteration) {}
	protected:
		descriptor_t const *master;
		key_t _iteration;
	};
	
	//Primary template for Set
	template <typename key_t, typename value_t, typename = void>
	class Set {
	};

	//Partial specialization of Set for a const descriptor. Inherits from const_set.
	template <typename key_t, typename value_t>
	class Set<key_t, value_t, Descriptor<key_t, value_t> const> : public Const_Set<key_t, value_t, Descriptor<key_t, value_t>> {
	public:
		using Const_Set::master;
		using Const_Set::_iteration;

		Set(Descriptor<key_t, value_t> const *const master, key_t const iteration) : Const_Set<key_t, value_t, Descriptor<key_t, value_t>>(master, iteration) {}
	};

	//Partial specialization of Set for a non-const descriptor. Inherits from const_set.
	template <typename key_t, typename value_t>
	class Set<key_t, value_t, Descriptor<key_t, value_t>> : public Const_Set<key_t, value_t, Descriptor<key_t, value_t>> {
	public:
		using Const_Set::master;
		using Const_Set::_iteration;

		util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> op_at(value_t const p0) const {
			return(util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator>::Element(mutable_master, mutable_master->Set_getIterator(_iteration, p0)));
		}

		Descriptor<key_t, value_t> &op_addAssign(std::vector<value_t> const &p0) const {
			mutable_master->Set_addValue(_iteration, p0);
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_addAssign(std::vector<value_t> &&p0) const {
			mutable_master->Set_addValue(_iteration, std::move(p0));
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_addAssign(Set const &p0) const {
			if (_iteration == p0._iteration)
				mutable_master->Set_addValue(_iteration, p0.mutable_master->description.at(_iteration));
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_addAssign(Set<key_t, value_t, Descriptor<key_t, value_t> const> const &p0) const {
			if (_iteration == p0._iteration)
				mutable_master->Set_addValue(_iteration, p0.master->description.at(_iteration));
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_addAssign(value_t const p0) const {
			mutable_master->Set_addValue(_iteration, p0);
			return(*mutable_master);
		}

		Descriptor<key_t, value_t> &op_subtractAssign(std::vector<value_t> const &p0) const {
			mutable_master->Set_removeValue(_iteration, p0);
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_subtractAssign(Set &p0) const {
			if (_iteration == p0._iteration)
				mutable_master->Set_removeValue(_iteration, p0.mutable_master->description.at(_iteration));
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_subtractAssign(Set<key_t, value_t, Descriptor<key_t, value_t> const> const &p0) const {
			if (_iteration == p0._iteration)
				mutable_master->Set_removeValue(_iteration, p0.master->description.at(_iteration));
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_subtractAssign(value_t const p0) const {
			mutable_master->Set_removeValue(_iteration, p0);
			return(*mutable_master);
		}

		Descriptor<key_t, value_t> &op_assign(std::vector<value_t> const &p0) const {
			mutable_master->description.at(_iteration) = p0;
			mutable_master->sort_key(_iteration);
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_assign(std::vector<value_t> &&p0) const {
			mutable_master->description.at(_iteration) = std::move(p0);
			mutable_master->sort_key(_iteration);
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_assign(Set const &p0) const {
			if (_iteration == p0._iteration) {
				mutable_master->description.at(_iteration) = p0.mutable_master->description.at(_iteration);
				mutable_master->sort_key(_iteration);
			}
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_assign(Set<key_t, value_t, Descriptor<key_t, value_t> const> const &p0) const {
			if (_iteration == p0._iteration) {
				mutable_master->description.at(_iteration) = p0.master->description.at(_iteration);
				mutable_master->sort_key(_iteration);
			}
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_assign(Descriptor<key_t, value_t> const &p0) const {
			if (p0.keyPresent(_iteration)) {
				mutable_master->description.at(_iteration) = p0.description.at(_iteration);
				mutable_master->sort_key(_iteration);
			}
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_assign(Descriptor<key_t, value_t> &&p0) const {
			if (p0.keyPresent(_iteration)) {
				mutable_master->description.at(_iteration) = std::move(p0.description.at(_iteration));
				mutable_master->sort_key(_iteration);
			}
			return(*mutable_master);
		}
		Descriptor<key_t, value_t> &op_assign(value_t const p0) const {
			mutable_master->description.at(_iteration).clear();
			mutable_master->description.at(_iteration).push_back(p0);
			return(*mutable_master);
		}

		//Called on 'descriptor[x][y]'
		//"descriptor vector[x] value[y]"
		util::Container::Element<Descriptor<key_t, value_t>, value_t, typename std::vector<value_t>::iterator> operator[](value_t const p0) const {
			return(op_at(p0));
		}

		//Called on 'descriptor0[x] += descriptor1[y]'
		//"add values from descriptor1[y] to descriptor0[x] that are not already present"
		Descriptor<key_t, value_t> &operator+=(Set const &p0) const {
			return(op_addAssign(p0));
		}
		Descriptor<key_t, value_t> &operator+=(Set<key_t, value_t, Descriptor<key_t, value_t> const> const &p0) const {
			return(op_addAssign(p0));
		}

		//Called on 'descriptor[x] += vector{value0, value1, ...}
		//"add the contents of vector to descriptor vector[x] that are not already present"
		Descriptor<key_t, value_t> &operator+=(std::vector<value_t> const &p0) const {
			return(op_addAssign(p0));
		}
		Descriptor<key_t, value_t> &operator+=(std::vector<value_t> &&p0) const {
			return(op_addAssign(std::move(p0)));
		}

		//Called on 'descriptor[x] += value_t'
		//"add value_t to descriptor vector [x] if not already present"
		Descriptor<key_t, value_t> &operator+=(value_t const p0) const {
			return(op_addAssign(p0));
		}

		//Called on 'descriptor[x] -= vector{value0, value1, ...}
		//"remove the contents of vector from descriptor vector[x]"
		Descriptor<key_t, value_t> &operator-=(std::vector<value_t> const &p0) const {
			return(op_subtractAssign(p0));
		}

		//Called on 'descriptor0[x] -= descriptor1[y]'
		//"remove the values that are in descriptor vector[y] from descriptor vector[x]"
		Descriptor<key_t, value_t> &operator-=(Set const &p0) const {
			return(op_subtractAssign(p0));
		}
		Descriptor<key_t, value_t> &operator-=(Set<key_t, value_t, Descriptor<key_t, value_t> const> const &p0) const {
			return(op_subtractAssign(p0));
		}

		//Called on 'descriptor0[x] -= value_t'
		//"remove value_t from descriptor vector[x]"
		Descriptor<key_t, value_t> &operator-=(value_t const p0) const {
			return(op_subtractAssign(p0));
		}

		//Called on 'descriptor[x] = vector{value0, value1...}
		//"make the only values in vector [x] those inside the initializer_list"
		Descriptor<key_t, value_t> &operator=(std::vector<value_t> const &p0) const {
			return(op_assign(p0));
		}

		//Called on 'descriptor[x] = std::move(some vector)'
		//"make the only values in vector [x] those inside some vector"
		Descriptor<key_t, value_t> &operator=(std::vector<value_t> &&p0) const {
			return(op_assign(std::move(p0)));
		}

		//Called on 'descriptor[x] = descriptor[y]'
		//"make the values in descriptor vector [x] equal the values in descriptor vector[y]'
		Descriptor<key_t, value_t> &operator=(Set const &p0) const {
			return(op_assign(p0));
		}
		Descriptor<key_t, value_t> &operator=(Set<key_t, value_t, Descriptor<key_t, value_t> const> const &p0) const {
			return(op_assign(p0));
		}

		//Called on 'descriptor[x] = descriptor1'
		//"make the values in descriptor vector[x] equal to the values in descriptor1 vector[x]"
		Descriptor<key_t, value_t> &operator=(Descriptor<key_t, value_t> const &p0) const {
			return(op_assign(p0));
		}
		Descriptor<key_t, value_t> &operator=(Descriptor<key_t, value_t> &&p0) const {
			return(op_assign(std::move(p0)));
		}

		//Called on 'descriptor[x] = value_t'
		//"make the only value in vector[x] value_t"
		Descriptor<key_t, value_t> &operator=(value_t const p0) const {
			return(op_assign(p0));
		}

		Set(Descriptor<key_t, value_t> *const master, key_t const iteration) : Const_Set<key_t, value_t, Descriptor<key_t, value_t>>(master, iteration), mutable_master(master) {}
	private:
		Descriptor<key_t, value_t> *mutable_master;
	};
}
