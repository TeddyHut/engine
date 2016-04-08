#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include "eg_foundation.h"
#include "eg_param.h"

namespace eg {
	namespace util {
		//TODO: Use vector::find (or whatever) instead of searching through
		enum class Remove_p0_from_p1_Param_e : size_t {
			Condition_All = 0	//Default 0; Removes all of the instance matching conditions from the vector
		}; extern eg::Param<Remove_p0_from_p1_Param_e> const Remove_p0_from_p1_Param_d;
		template<typename T0> void remove_p0_from_p1_idn(std::vector<T0> const& p0, std::vector<T0>& p1); //Removes exacly what is told to
		template<typename T0> void remove_p0_from_p1_all(std::vector<T0> const& p0, std::vector<T0>& p1); //Removes all matches of type if found
		template<typename T0> void remove_p0_from_p1(std::vector<T0> const& p0, std::vector<T0>& p1, eg::Param<Remove_p0_from_p1_Param_e> const param0 = Remove_p0_from_p1_Param_d);
		void edianSwap(void* buffer, size_t buffer_len, size_t type_len = 0);	//Swaps the edian of the buffer. -buffer_len- is measured in bytes. -type_len- default = buffer_len
		std::string truncateFilename(std::string filename, size_t const level = 1);
	} //end namespace util

} //end namespace eg

//Legit... Like.. WHAT? Templates are so sillly.

template<typename T0> void eg::util::remove_p0_from_p1_idn(std::vector<T0> const& p0, std::vector<T0>& p1) {
	for (size_t i = 0; i < p0.size(); i++) {
		for (size_t j = 0; j < p1.size(); j++) {
			if (p1[j] == p0[i]) {
				p1.erase(p1.begin() + j);
				break;
			}
		}
	}
}

//Hmm... Check this works (erase at pos 7 yet still +1 = pos 9)
template<typename T0> void eg::util::remove_p0_from_p1_all(std::vector<T0> const& p0, std::vector<T0>& p1) {
	for (size_t i = 0; i < p0.size(); i++) {
		for (size_t j = 0; j < p1.size(); j++) {
			if (p1[j] == p0[i]) {
				p1.erase(p1.begin() + j);
				j--;	//Added this in to fix above problem... May also cause problems.
			}
		}
	}
}

template<typename T0> void eg::util::remove_p0_from_p1(std::vector<T0> const& p0, std::vector<T0>& p1, eg::Param<eg::util::Remove_p0_from_p1_Param_e> const param0) {
	if (param0[eg::util::Remove_p0_from_p1_Param_e::Condition_All]) {
		eg::util::remove_p0_from_p1_all<T0>(p0, p1);
	}
	else {
		eg::util::remove_p0_from_p1_idn<T0>(p0, p1);
	}
}
