#pragma once

#include <cstdint>
#include <vector>

#include "eg_declaration.h"
#include "eg_util.h"
#include "eg_type.h"
#include "eg_definition.h"
#include "eg_dataReference.h"
#include "eg_blankController.h"

namespace eg {
	class Base {
	public:
		enum class Base_Param_e : size_t {
			State_RunRunoverInit = 0,		//Default = 1; States if the init function will be run
			State_ControllerBound,			//Default = 0; States if a controller is bound to the base
			Info_DynamicallyAllocated		//Default = 0; States if object was dynamically allocated
		}; static eg::Param<Base_Param_e> const Base_Param_d;

		virtual void base_runover(void* rundata);								//Base runover, including -rundata- (sort of up to personal interpretation)
		virtual void runover_init(void* rundata);								//Will run before first runover, or according to -RUNOVER_INIT-
		virtual void runover(void* rundata);									//Main runover for subclasses

		virtual void set_boundController(eg::BlankController* const ncontroller);			//Sets -boundController- and adds itself to the controller

		virtual eg::FunctionType get_functionType() const;						//Will return the functionType
		virtual eg::BlankController* get_boundController() const;					//Will return the boundcontroller

		eg::Param<Base_Param_e> base_param;

		Base();
		virtual ~Base();
	protected:
		virtual bool loadData(eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool freeData(eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param = eg::WriteData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool loadData(eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool freeData(eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param = eg::WriteData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		//Well dang it.
		virtual bool loadData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool freeData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param = eg::WriteData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool loadData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool freeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d_Scope_SetDestination1) const;
		virtual bool writeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param = eg::WriteData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;

		virtual eg::Base* requestPointer(eg::FunctionType type, eg::Param<eg::Scope_Param_e> param = eg::Scope_Param_d) const;
		virtual eg::Base* requestPointer(eg::GlbRtrn& rtrn, eg::FunctionType type, eg::Param<eg::Scope_Param_e> param = eg::Scope_Param_d) const;

		virtual void base_bindController(eg::BlankController* controller = nullptr) = 0;		//Apparently there needs to be a subclass implementation of this... Probably because it's specific to base subclass
		virtual void base_unbindController(eg::BlankController* controller = nullptr) = 0;	//Apparently there also needs to be a subclass implementation of this...

		eg::FunctionType functionType;
		eg::BlankController* boundController;
		std::function<void(Base* const nobject)> base_unbindFunction;
	};

} //end namespace eg
