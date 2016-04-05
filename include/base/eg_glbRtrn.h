#pragma once

#include <cstdint>

namespace eg {

	class GlbRtrn {
	public:
		static size_t const RTRN_SUCCESS;
		static size_t const RTRN_FAILURE;
		
		size_t rtrn;

		eg::GlbRtrn& operator= (size_t const& rhs);

		GlbRtrn();
		GlbRtrn(size_t const& nrtrn);
	};

} //end namespace eg

bool operator== (eg::GlbRtrn& lhs,size_t const& rhs);