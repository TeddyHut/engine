#include "../../include/base/eg_type.h"

size_t const eg::FunctionType::FUNCTIONTYPE_COMPARE_PARAM_BASEMATCH = 0;
size_t const eg::FunctionType::FUNCTIONTYPE_COMPARE_PARAM_EQUAL = 1;
size_t const eg::FunctionType::FUNCTIONTYPE_COMPARE_PARAM_TRUE = 2;

bool eg::FunctionType::compare_basematch(eg::FunctionType const& p0,eg::FunctionType const& p1) {
	return(p0.basetype_hashcode == p1.basetype_hashcode);
}

bool eg::FunctionType::compare_equal(eg::FunctionType const& p0,eg::FunctionType const& p1) {
	return((p0.functionType.size() == p1.functionType.size()) && (compare_true(p0, p1)));
}

bool eg::FunctionType::compare_true(eg::FunctionType const& p0,eg::FunctionType const& p1) {
	std::vector<size_t> p0_functionType_c = p0.functionType;
	std::vector<size_t> p1_functionType_c = p1.functionType;
	bool err = false;
	size_t p0_itr = 0;
	while(1) {
		if(p0_itr == p0_functionType_c.size()) return(true);
		if(p1_functionType_c.size() == 0) err = true;
		if(err) break;
		err = true;
		for(size_t p1_itr = 0;p1_itr < p1_functionType_c.size();p1_itr++) {
			if(p0_functionType_c[p0_itr] == p1_functionType_c[p1_itr]) {
				p1_functionType_c.erase(p1_functionType_c.begin()+p1_itr);
				err = false;
				break;
			}
		}
		p0_itr++;
	}
	return(false);
}

eg::Param eg::FunctionType::compare(eg::FunctionType const& p0,eg::FunctionType const& p1) {
	return(eg::Param::Param(3,
		FUNCTIONTYPE_COMPARE_PARAM_BASEMATCH, compare_basematch(p0,p1),
		FUNCTIONTYPE_COMPARE_PARAM_EQUAL, compare_equal(p0,p1),
		FUNCTIONTYPE_COMPARE_PARAM_TRUE, compare_true(p0,p1)));
}

eg::FunctionType::FunctionType() {
}

eg::FunctionType::~FunctionType() {
}

bool operator== (eg::FunctionType const& lhs,eg::FunctionType const& rhs) {
	return(eg::FunctionType::compare_equal(lhs,rhs));	//Make inline?
}
