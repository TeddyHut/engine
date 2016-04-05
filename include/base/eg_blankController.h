#pragma once

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_type.h"
#include "eg_dataReference.h"

namespace eg {
	//Come up with a better name than 'BlankController'
	class BlankController {
	public:
		virtual eg::GlbRtrn base_loadData(eg::Base const*const base, eg::DataReference& dataReference, eg::Param const param) = 0;
		virtual eg::GlbRtrn base_loadData(eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param const param) = 0;
		virtual eg::GlbRtrn base_freeData(eg::Base const*const base, eg::DataReference& dataReference, eg::Param const param) = 0;
		virtual eg::GlbRtrn base_freeData(eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param const param) = 0;
		virtual eg::GlbRtrn base_writeData(eg::Base const*const base, eg::DataReference const& dataReferece, eg::Param const param) = 0;
		virtual eg::GlbRtrn base_writeData(eg::Base const*const base, eg::DataReferenceSet const& dataReferenceSet, eg::Param const param) = 0;

		virtual eg::GlbRtrn base_requestPointer(eg::Base* const base0, eg::Base** const base1, eg::FunctionType const type0) = 0;

		virtual void add_egFunctionObject(Base* const nobject) = 0;
		virtual void remove_egFunctionObject(Base* const nobject) = 0;
		virtual std::function<void(Base* const nobject)> base_get_unbindFunction(eg::Base const*const nobject) = 0;
	};
}