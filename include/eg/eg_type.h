#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <typeinfo>
#include <functional>

#include "eg_util.h"

namespace eg {

	namespace type {
		template<typename T0> std::string get_typeName();
		size_t get_string_hash(std::string const data);
	}

	class FunctionType {
	public:
		enum class FunctionType_Compare_Param_e : size_t {
			Condition_Basematch = 0,	//1; base type matches (eg, 'Input' == 'Input')
			Condition_Equal,			//1; typesfunctions are exactly equal
			Condition_True				//1; typesfunctions contain all neccacary typefunctions
		};
		
		static bool compare_basematch(eg::FunctionType const& p0,eg::FunctionType const& p1);
		static bool compare_equal(eg::FunctionType const& p0,eg::FunctionType const& p1);
		static bool compare_true(eg::FunctionType const& p0,eg::FunctionType const& p1);
		static eg::Param<FunctionType_Compare_Param_e> compare(eg::FunctionType const& p0,eg::FunctionType const& p1);	//p0 takes from p1 (checks p1 has all p0)
		template<typename T0> void set_basetype();  //DON'T FORGET TO CALL THIS (couldn't work out how to PII constuctor)
		std::vector<size_t> functionType;	//Things this particular type can do (eg DataManipulator that can load x y and z)
		std::string basetype_formatname;
		size_t basetype_hashcode;			//The basetype (why I doing std::string?) -> Think that this is supposed to be what class after eg::Base it is (eg eg::Model)

		FunctionType();
		FunctionType(size_t const nfunctionType);
		FunctionType(std::vector<size_t> const nfunctionType);
		virtual ~FunctionType();
	};

}	//end namespace eg

bool operator== (eg::FunctionType const& lhs,eg::FunctionType const& rhs);	//Compare Equal

//Template Implementation

template<typename T0>
std::string eg::type::get_typeName() {
	std::string r0 = typeid(T0).name();
	return(r0);
}

template<typename T0> void eg::FunctionType::set_basetype() {
	basetype_hashcode = typeid(T0).hash_code();
	basetype_formatname = eg::type::get_typeName<T0>();
}