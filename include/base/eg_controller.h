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
#include "eg_blankController.h"
#include "eg_base.h"
#include "eg_input.h"
#include "eg_model.h"
#include "eg_view.h"
#include "eg_dataManipulator.h"

namespace eg {

	class Controller : public eg::Base, public eg::BlankController {
	public:
		static std::string const _egNAME_OBJECT_seg_;
		//Constants
		enum class Controller_Param_e : size_t {
			//Default = 1; Will dealloc attached controllers upon delete
			Deallocate_Attached_Controller = 0,
			//Default = 1; Will dealloc attached inputs upon delete
			Deallocate_Attached_Input,
			//Default = 1; Will dealloc attached models upon delete
			Deallocate_Attached_Model,
			//Default = 1; Will dealloc attached views upon delete
			Deallocate_Attached_View,
			//Default = 1; Will dealloc attached dataManipulators upon delete
			Deallocate_Attached_DataManipulator
		}; static eg::Param<Controller_Param_e> const Controller_Param_d;

		//Functionality
		virtual void runover_controller(void* rundata = nullptr);	//Maybe change from controllerrundata to rundata
		virtual void runover_input(void* rundata = nullptr);
		virtual void runover_model(void* rundata = nullptr);
		virtual void runover_view(void* rundata = nullptr);
		virtual void runover_dataManipulator(void* rundata = nullptr);
		
		virtual bool base_loadData(eg::GlbRtrn& rtrn, eg::Base const*const base,eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool base_freeData(eg::GlbRtrn& rtrn, eg::Base const*const base,eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d_Scope_SetDestination1) const;
		virtual bool base_writeData(eg::GlbRtrn& rtrn, eg::Base const*const base,eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param = eg::WriteData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;

		virtual bool base_loadData(eg::GlbRtrn& rtrn, eg::Base const*const base,eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;
		virtual bool base_freeData(eg::GlbRtrn& rtrn, eg::Base const*const base,eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d_Scope_SetDestination1) const;
		virtual bool base_writeData(eg::GlbRtrn& rtrn, eg::Base const*const base,eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param = eg::WriteData_Param_d, eg::Param<eg::Scope_Param_e> const scope_param = eg::Scope_Param_d) const;


		virtual eg::Base* base_requestPointer(eg::GlbRtrn& rtrn, eg::Base const*const base0, eg::FunctionType const type0, eg::Param<eg::Scope_Param_e> param = eg::Scope_Param_d) const;
//																		Sender ptr	Return				what type

		//Data Manipulation
		//TODO V2: Rather than write these out 1000 times, do something where it all just happens... (whatever that something is)
		//Maybe need to use specialised templates instead for these

		virtual void add_egFunctionObject(eg::Base* const nobject);
		virtual void add_egFunctionObject(eg::Controller* const nobject);
		virtual void add_egFunctionObject(eg::Input* const nobject);
		virtual void add_egFunctionObject(eg::Model* const nobject);
		virtual void add_egFunctionObject(eg::View* const nobject);
		virtual void add_egFunctionObject(eg::DataManipulator* const nobject);
		virtual void add_externalController(eg::Controller const*const nobject);

		virtual void remove_egFunctionObject(eg::Base* const nobject);
		virtual void remove_egFunctionObject(eg::Controller* const nobject);
		virtual void remove_egFunctionObject(eg::Input* const nobject);
		virtual void remove_egFunctionObject(eg::Model* const nobject);
		virtual void remove_egFunctionObject(eg::View* const nobject);
		virtual void remove_egFunctionObject(eg::DataManipulator* const nobject);
		virtual void remove_externalController(eg::Controller const*const nobject);
		
		/*
		//Darn it GCC and C++ Standard :(
		template<typename egFunctionObject_t> void dealloc_egFunctionObject();						//Currently not implemented (just there so it works)
		template<> void dealloc_egFunctionObject<eg::Controller>();
		template<> void dealloc_egFunctionObject<eg::Input>();
		template<> void dealloc_egFunctionObject<eg::Model>();
		template<> void dealloc_egFunctionObject<eg::View>();
		template<> void dealloc_egFunctionObject<eg::DataManipulator>();
		*/

		virtual void dealloc_egFunctionObject_Controller();
		virtual void dealloc_egFunctionObject_Input();
		virtual void dealloc_egFunctionObject_Model();
		virtual void dealloc_egFunctionObject_View();
		virtual void dealloc_egFunctionObject_DataManipulator();

		virtual std::function<void(eg::Base* const nobject)> base_get_unbindFunction(eg::Base const*const nobject);
		virtual std::function<void(eg::Base* const nobject)> base_get_unbindFunction(eg::Controller const*const nobject);
		virtual std::function<void(eg::Base* const nobject)> base_get_unbindFunction(eg::Input const*const nobject);
		virtual std::function<void(eg::Base* const nobject)> base_get_unbindFunction(eg::Model const*const nobject);
		virtual std::function<void(eg::Base* const nobject)> base_get_unbindFunction(eg::View const*const nobject);
		virtual std::function<void(eg::Base* const nobject)> base_get_unbindFunction(eg::DataManipulator const*const nobject);

		Controller();
		virtual ~Controller();
	protected:
		virtual void add_Base(eg::Base* const nbase);		//Change to add_egFunctionObject spec? Check overload resolution.
		virtual void remove_Base(eg::Base* const nbase);

		eg::DataManipulator* find_matching_dataManipulator(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<Scope_Param_e> const param = Scope_Param_d) const;
		eg::DataManipulator* find_matching_dataManipulator(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<Scope_Param_e> const param = Scope_Param_d) const;
		
		virtual void base_bindController(eg::BlankController* ncontroller = nullptr) override;
		virtual void base_unbindController(eg::BlankController* ncontroller = nullptr) override;

		std::vector<eg::BlankController const*> externalController;
		std::vector<eg::Controller*> attachedController;
		std::vector<eg::Input*> attachedInput;
		std::vector<eg::Model*> attachedModel;
		std::vector<eg::View*> attachedView;
		std::vector<eg::DataManipulator*> attachedDataManipulator;
		std::vector<eg::Base*> attachedBase;						//Should only be used for search sort of things

		eg::Param<Controller_Param_e> controller_param;
	};

} //end namspace eg