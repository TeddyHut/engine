#pragma once

#include <functional>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_type.h"
#include "eg_definition.h"
#include "eg_dataReference.h"

namespace eg {
	//Come up with a better name than 'BlankController'
	class BlankController {
	public:
		virtual bool base_loadData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const = 0;
		virtual bool base_loadData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const = 0;
		virtual bool base_freeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const = 0;
		virtual bool base_freeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const = 0;
		virtual bool base_writeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReference const& dataReferece, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const = 0;
		virtual bool base_writeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const = 0;

		virtual eg::Base* base_requestPointer(eg::GlbRtrn& rtrn, eg::Base const*const base0, eg::FunctionType const type0, eg::Param<eg::Scope_Param_e> param) const = 0;

		virtual void add_egFunctionObject(Base* const nobject) = 0;
		virtual void remove_egFunctionObject(Base* const nobject) = 0;
		virtual std::function<void(Base* const nobject)> base_get_unbindFunction(eg::Base const*const nobject) = 0;
	};
}