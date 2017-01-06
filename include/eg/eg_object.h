#pragma once

#include <cstdint>
#include <vector>

#include "eg_declaration.h"
#include "eg_util.h"
#include "eg_descriptor.h"
#include "eg_definition.h"
#include "eg_dataReference.h"
#include "eg_fullObject_abs_p.h"

namespace eg {
	class Object {
	public:
		enum class Object_Param_e : size_t {
			State_RunRunoverInit = 0,		//Default = 1; States if the init function will be run
			State_FullObjectBound,			//Default = 0; States if the object is bound to a fullObject
			Info_DynamicallyAllocated		//Default = 0; States if object was dynamically allocated
		}; static Param<Object_Param_e> const Object_Param_d;

		virtual void object_runover(void *rundata);								//Object runover, including -rundata- (sort of up to personal interpretation)
		virtual void runover_init(void *rundata);								//Will run before first runover, or according to -RUNOVER_INIT-
		virtual void runover(void *rundata);									//Main runover for subclasses

		virtual void set_boundFullObject(FullObject_abs_p *const nobject);			//Sets -boundFullObject- and adds itself to the fullObjects

		virtual FullObject_abs_p *get_boundFullObject() const;					//Will return the boundFullObject

		Param<Object_Param_e> object_param = Object_Param_d;
		
		Descriptor<> description = eg::Descriptor<>::Descriptor({ {Key::egType, {Value::egType::Object} } });

		Object();
		virtual ~Object();

	protected:
		virtual bool loadData(DataReference &dataReference, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		virtual bool freeData(DataReference &dataReference, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(DataReference const &dataReference, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		virtual bool loadData(DataReferenceSet &dataReferenceSet, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		virtual bool freeData(DataReferenceSet &dataReferenceSet, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(DataReferenceSet const &dataReferenceSet, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;

		virtual bool loadData(GlbRtrn &rtrn, DataReference &dataReference, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		virtual bool freeData(GlbRtrn &rtrn, DataReference  &dataReference, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(GlbRtrn &rtrn, DataReference const &dataReference, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		virtual bool loadData(GlbRtrn &rtrn, DataReferenceSet &dataReferenceSet, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		virtual bool freeData(GlbRtrn &rtrn, DataReferenceSet &dataReferenceSet, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(GlbRtrn &rtrn, DataReferenceSet const &dataReferenceSet, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;

		virtual Object *requestPointer(Descriptor<> const desc, Param<Scope_Param_e> param = Scope_Param_d) const;
		virtual Object *requestPointer(GlbRtrn &rtrn, Descriptor<> const desc, Param<Scope_Param_e> param = Scope_Param_d) const;

		//Will call unbind function of nullptr is given; Will add to -nobject- bound object list otherwise
		virtual void object_bindFullObject(FullObject_abs_p *const nobject = nullptr);

		FullObject_abs_p *boundFullObject = nullptr;
		std::function<void(Object *const nobject)> object_unbindFunction;
	};

} //end namespace eg
