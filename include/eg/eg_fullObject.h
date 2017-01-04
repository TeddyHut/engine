#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <functional>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_util.h"
#include "eg_descriptor.h"
#include "eg_param.h"
#include "eg_definition.h"
#include "eg_dataReference.h"
#include "eg_fullObject_abs_p.h"
#include "eg_object.h"
#include "eg_dataManipulator.h"

namespace eg {

	class FullObject : public Object, public FullObject_abs_p {
	public:
		static std::string const _egNAME_OBJECT_seg_;
		//Constants
		enum class FullObject_Param_e : size_t {
		}; static Param<FullObject_Param_e> const FullObject_Param_d;

		//Functionality

		//Calls runover_fullObject for attached fullObjects, and runover for all attached objects
		virtual void runover_fullObject(void *rundata = nullptr);
		
		//Calls find_matching_dataManipulator and calls dataManipulator_loadData
		virtual bool object_loadData(GlbRtrn &rtrn, Object const *const object, DataReference &dataReference, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const override;
		//Calls find_matching_dataManipulator and calls dataManipulator_freeData
		virtual bool object_freeData(GlbRtrn &rtrn, Object const *const object, DataReference &dataReference, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const override;
		//Calls find_matching_dataManipulator and calls dataManipulator_writeData
		virtual bool object_writeData(GlbRtrn &rtrn, Object const *const object, DataReference &dataReference, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const override;

		//Calls find_matching_dataManipulator and calls dataManipulator_loadData
		virtual bool object_loadData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet &dataReferenceSet, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const override;
		//Calls find_matching_dataManipulator and calls dataManipulator_freeData
		virtual bool object_freeData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet &dataReferenceSet, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const override;
		//Calls find_matching_dataManipulator and calls dataManipulator_writeData
		virtual bool object_writeData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet &dataReferenceSet, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const override;

		//Attempt to get the pointer of an attached object that matches conditions
		virtual Object *object_requestPointer(GlbRtrn &rtrn, Object const *const requester, Descriptor<> desc, Param<Scope_Param_e> param = Scope_Param_d) const override;

		//Data Manipulation
		//TODO V2: Rather than write these out 1000 times, do something where it all just happens... (whatever that something is)
		//Maybe need to use specialised templates instead for these

		//Add an object to the attached objects (called automatically when fullObject set to boundObject)
		virtual void add_egObject(Object *const nobject) override;

		//Remove an object from the attached objects (called automatically upon attached object destruction)
		virtual void remove_egObject(Object *const nobject) override;

		//Attempt to delete dynamically allocated objects
		virtual void dealloc_egObject();

		//Called upon attached objects set_boundFullObject
		virtual std::function<void(Object *const nobject)> object_get_unbindFunction() override;

		//Sets functionType basetype to *work this out*
		FullObject();
		//Attempts to deallocate attached objects if conditions allow
		virtual ~FullObject();
	protected:
		//Actually adds an object to the vector (if it doesn't already exist)
		virtual void add_object(Object *const nobject);		//Change to add_egFunctionObject spec? Check overload resolution.
		//Removes an object from the vector
		virtual void remove_object(Object *const nobject);

		//Locates matching dataManipulator according to conditions
		DataManipulator *find_matching_dataManipulator(GlbRtrn &rtrn, DataReference &dataReference, Param<Scope_Param_e> const param = Scope_Param_d) const;
		
		std::vector<Object *> attachedObject;

		Param<FullObject_Param_e> fullObject_param;
	};

}
