#include "../../include/base/eg_glbRtrn.h"

size_t const eg::GlbRtrn::RTRN_SUCCESS = 0;
size_t const eg::GlbRtrn::RTRN_FAILURE = 1;

eg::GlbRtrn& eg::GlbRtrn::operator= (size_t const& rhs) {
	rtrn = rhs;
	return(*this);
}

eg::GlbRtrn::GlbRtrn() : rtrn(eg::GlbRtrn::RTRN_SUCCESS) {
}

eg::GlbRtrn::GlbRtrn(size_t const& nrtrn) : rtrn(nrtrn) {
}

bool operator== (eg::GlbRtrn& lhs,size_t const& rhs) {
	if(lhs.rtrn == rhs) return(true);
	else if((lhs.rtrn == eg::GlbRtrn::RTRN_FAILURE)&&(rhs != eg::GlbRtrn::RTRN_SUCCESS)) return(true);
	else if ((lhs.rtrn != eg::GlbRtrn::RTRN_SUCCESS) && (rhs == eg::GlbRtrn::RTRN_FAILURE)) return(true);
	return(false);
}