#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include "eg_param.h"

namespace eg {
	namespace util {
		enum class Remove_p0_from_p1_Param_e : size_t {
			Condition_All = 0	//Default 0; Removes all of the instance matching conditions from the vector
		}; extern Param<Remove_p0_from_p1_Param_e> const Remove_p0_from_p1_Param_d;
		template<typename vec_t> void remove_p0_from_p1_idn(std::vector<vec_t> const &p0, std::vector<vec_t> &p1); //Removes exacly what is told to
		template<typename vec_t> void remove_p0_from_p1_all(std::vector<vec_t> const &p0, std::vector<vec_t> &p1); //Removes all matches of type if found
		template<typename vec_t> void remove_p0_from_p1(std::vector<vec_t> const &p0, std::vector<vec_t> &p1, Param<Remove_p0_from_p1_Param_e> const param0 = Remove_p0_from_p1_Param_d);

		enum class Add_p0_to_p1_Param_e : size_t {
			Condition_New = 0	//Default = 1; Will only add the item if it is the first occurence of it in the vector
		}; extern Param<Add_p0_to_p1_Param_e> const Add_p0_to_p1_Param_d;

		void edianSwap(void *buffer, size_t buffer_len, size_t type_len = 0);	//Swaps the edian of the buffer. -buffer_len- is measured in bytes. -type_len- default = buffer_len
		std::string truncateFilename(std::string filename, size_t const level = 1);
	}
}

template<typename vec_t> void eg::util::remove_p0_from_p1_idn(std::vector<vec_t> const &p0, std::vector<vec_t> &p1) {
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
template<typename vec_t> void eg::util::remove_p0_from_p1_all(std::vector<vec_t> const &p0, std::vector<vec_t> &p1) {
	for (size_t i = 0; i < p0.size(); i++) {
		for (size_t j = 0; j < p1.size(); j++) {
			if (p1[j] == p0[i]) {
				p1.erase(p1.begin() + j);
				j--;	//Added this in to fix above problem... May also cause problems.
			}
		}
	}
}

template<typename vec_t> void eg::util::remove_p0_from_p1(std::vector<vec_t> const &p0, std::vector<vec_t> &p1, Param<Remove_p0_from_p1_Param_e> const param0) {
	if (param0[Remove_p0_from_p1_Param_e::Condition_All]) {
		remove_p0_from_p1_all<vec_t>(p0, p1);
	}
	else {
		remove_p0_from_p1_idn<vec_t>(p0, p1);
	}
}
