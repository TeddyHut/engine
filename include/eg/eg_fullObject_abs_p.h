#pragma once

#include <functional>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_definition.h"
#include "eg_dataReference.h"

namespace eg {
	class FullObject_abs_p {
	public:
		virtual bool object_loadData(GlbRtrn &rtrn, Object const *const object, DataReference &dataReference, Param<LoadData_Param_e> const param, Param<Scope_Param_e> const scope_param) const = 0;
		virtual bool object_loadData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet &dataReferenceSet, Param<LoadData_Param_e> const param, Param<Scope_Param_e> const scope_param) const = 0;
		virtual bool object_freeData(GlbRtrn &rtrn, Object const *const object, DataReference &dataReference, Param<FreeData_Param_e> const param, Param<Scope_Param_e> const scope_param) const = 0;
		virtual bool object_freeData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet &dataReferenceSet, Param<FreeData_Param_e> const param, Param<Scope_Param_e> const scope_param) const = 0;
		virtual bool object_writeData(GlbRtrn &rtrn, Object const *const object, DataReference const &dataReferece, Param<WriteData_Param_e> const param, Param<Scope_Param_e> const scope_param) const = 0;
		virtual bool object_writeData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet const &dataReferenceSet, Param<WriteData_Param_e> const param, Param<Scope_Param_e> const scope_param) const = 0;

		virtual Object *object_requestPointer(GlbRtrn &rtrn, Object const *const requester, eg::Descriptor<> const desc, Param<Scope_Param_e> param) const = 0;

		virtual void add_egObject(Object *const nobject) = 0;
		virtual void remove_egObject(Object *const nobject) = 0;
		virtual std::function<void(Object *const nobject)> object_get_unbindFunction() = 0;
	};
}