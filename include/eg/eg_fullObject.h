#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <functional>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_util.h"
#include "eg_param.h"
#include "eg_definition.h"
#include "eg_type.h"
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
			//Default = 1; Will dealloc attached controllers upon delete
		}; static Param<FullObject_Param_e> const FullObject_Param_d;

		//Functionality

		//Calls runover_fullObject for attached fullObjects
		virtual void runover_fullObject(void *rundata = nullptr);	//Maybe change from controllerrundata to rundata
		//Calls object_runover for attached objects
		virtual void runover_object(void *rundata = nullptr);
		
		//Calls find_matching_dataManipulator and calls dataManipulator_loadData
		virtual bool object_loadData(GlbRtrn &rtrn, Object const *const object, DataReference &dataReference, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		//Calls find_matching_dataManipulator and calls dataManipulator_freeData
		virtual bool object_freeData(GlbRtrn &rtrn, Object const *const object, DataReference &dataReference, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const;
		//Calls find_matching_dataManipulator and calls dataManipulator_writeData
		virtual bool object_writeData(GlbRtrn &rtrn, Object const *const object, DataReference const &dataReference, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;

		//Calls find_matching_dataManipulator and calls dataManipulator_loadData
		virtual bool object_loadData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet &dataReferenceSet, Param<LoadData_Param_e> const param = LoadData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;
		//Calls find_matching_dataManipulator and calls dataManipulator_freeData
		virtual bool object_freeData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet &dataReferenceSet, Param<FreeData_Param_e> const param = FreeData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d_Scope_SetDestination1) const;
		//Calls find_matching_dataManipulator and calls dataManipulator_writeData
		virtual bool object_writeData(GlbRtrn &rtrn, Object const *const object, DataReferenceSet const &dataReferenceSet, Param<WriteData_Param_e> const param = WriteData_Param_d, Param<Scope_Param_e> const scope_param = Scope_Param_d) const;

		//Attempt to get the pointer of an attached object that matches conditions
		virtual Object *object_requestPointer(GlbRtrn &rtrn, Object const *const object0, FunctionType const type0, Param<Scope_Param_e> param = Scope_Param_d) const;
//																		Sender ptr	Return				what type

		//Data Manipulation
		//TODO V2: Rather than write these out 1000 times, do something where it all just happens... (whatever that something is)
		//Maybe need to use specialised templates instead for these

		//Add an object to the attached objects (called automatically when fullObject set to boundObject)
		virtual void add_Object(Object *const nobject);
		//Add a dataManipulator
		virtual void add_DataManipulator(DataManipulator *const nobject);

		//Remove an object from the attached objects (called automatically upon attached object destruction)
		virtual void remove_Object(Object *const nobject);
		//Remove a dataManipulator
		virtual void remove_DataManipulator(DataManipulator *const nobject);
		
		/*
		//Darn it GCC and C++ Standard :(
		template<typename egFunctionObject_t> void dealloc_egFunctionObject();						//Currently not implemented (just there so it works)
		template<> void dealloc_egFunctionObject<Controller>();
		template<> void dealloc_egFunctionObject<Input>();
		template<> void dealloc_egFunctionObject<Model>();
		template<> void dealloc_egFunctionObject<View>();
		template<> void dealloc_egFunctionObject<DataManipulator>();
		*/

		//Attmpe to delete dynamically allocated objects
		virtual void dealloc_Object();

		//Called upon attached objects set_boundFullObject
		virtual std::function<void(Object *const nobject)> object_get_unbindFunction(Object const *const nobject);

		//Sets functionType basetype to *work this out*
		FullObject();
		//Attempts to deallocate attached objects if conditions allow
		virtual ~FullObject();
	protected:
		//Figure this one out
		virtual void add_object(Object *const nobject);		//Change to add_egFunctionObject spec? Check overload resolution.
		virtual void remove_object(Object *const nobject);

		//Locates matching dataManipulator according to conditions
		DataManipulator *find_matching_dataManipulator(GlbRtrn &rtrn, DataReference const &dataReference, Param<Scope_Param_e> const param = Scope_Param_d) const;
		//Locates matching dataManipulator according to conditions
		DataManipulator *find_matching_dataManipulator(GlbRtrn &rtrn, DataReferenceSet const &dataReferenceSet, Param<Scope_Param_e> const param = Scope_Param_d) const;
		
		//Don't think that we need these in here anymore.
		virtual void object_bindObject(FullObject_abs_p *ncontroller = nullptr) override;
		virtual void object_unbindObject(FullObject_abs_p *ncontroller = nullptr) override;

		std::vector<DataManipulator *> attachedDataManipulator;
		std::vector<Object *> attachedObject;						//Should only be used for search sort of things

		Param<FullObject_Param_e> fullObject_param;
	};

} //end namspace eg