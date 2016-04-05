#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_util.h"
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
		//Constants
		static size_t const CONTROLLER_PARAM_DEALLOCCONTROLLER;			//Default = 1; Will dealloc attached controllers upon delete
		static size_t const CONTROLLER_PARAM_DEALLOCINPUT;				//Default = 1; Will dealloc attached inputs upon delete
		static size_t const CONTROLLER_PARAM_DEALLOCMODEL;				//Default = 1; Will dealloc attached models upon delete
		static size_t const CONTROLLER_PARAM_DEALLOCVIEW;				//Default = 1; Will dealloc attached views upon delete
		static size_t const CONTROLLER_PARAM_DEALLOCDATAMANIPULATOR;	//Default = 1; Will dealloc attached loaders upon delete
		static eg::Param const CONTROLLER_Param_DEFAULT;

		//Functionality
		virtual void runover_controller(void* rundata = nullptr);	//Maybe change from controllerrundata to rundata
		virtual void runover_input(void* rundata = nullptr);
		virtual void runover_model(void* rundata = nullptr);
		virtual void runover_view(void* rundata = nullptr);
		virtual void runover_dataManipulator(void* rundata = nullptr);
		
		//TODO V2: Make these have an optional param to search higher in (or lower in) the controller heirachy (so that copies aren't everywhere)
		virtual eg::GlbRtrn base_loadData(eg::Base const*const base,eg::DataReference& dataReference, eg::Param const param = eg::DATAMANIPULATOR_LOADDATA_Param_DEFAULT);
		virtual eg::GlbRtrn base_freeData(eg::Base const*const base,eg::DataReference& dataReference, eg::Param const param = eg::DATAMANIPULATOR_FREEDATA_Param_DEFAULT);
		virtual eg::GlbRtrn base_writeData(eg::Base const*const base,eg::DataReference const& dataReference, eg::Param const param = eg::DATAMANIPULATOR_WRITEDATA_Param_DEFAULT);

		virtual eg::GlbRtrn base_loadData(eg::Base const*const base,eg::DataReferenceSet& dataReferenceSet, eg::Param const param = eg::DATAMANIPULATOR_LOADDATA_Param_DEFAULT);
		virtual eg::GlbRtrn base_freeData(eg::Base const*const base,eg::DataReferenceSet& dataReferenceSet, eg::Param const param = eg::DATAMANIPULATOR_FREEDATA_Param_DEFAULT);
		virtual eg::GlbRtrn base_writeData(eg::Base const*const base,eg::DataReferenceSet const& dataReferenceSet, eg::Param const param = eg::DATAMANIPULATOR_WRITEDATA_Param_DEFAULT);

		virtual eg::GlbRtrn base_requestPointer(eg::Base* const base0,eg::Base** const base1,eg::FunctionType const type0);
//												Sender ptr	Return				what type

		//Data Manipulation
		//TODO V2: Rather than write these out 1000 times, do something where it all just happens... (whatever that something is)
		//Maybe need to use specialised templates instead for these

		virtual void add_egFunctionObject(eg::Base* const nobject);
		virtual void add_egFunctionObject(eg::Controller* const nobject);
		virtual void add_egFunctionObject(eg::Input* const nobject);
		virtual void add_egFunctionObject(eg::Model* const nobject);
		virtual void add_egFunctionObject(eg::View* const nobject);
		virtual void add_egFunctionObject(eg::DataManipulator* const nobject);

		virtual void remove_egFunctionObject(eg::Base* const nobject);
		virtual void remove_egFunctionObject(eg::Controller* const nobject);
		virtual void remove_egFunctionObject(eg::Input* const nobject);
		virtual void remove_egFunctionObject(eg::Model* const nobject);
		virtual void remove_egFunctionObject(eg::View* const nobject);
		virtual void remove_egFunctionObject(eg::DataManipulator* const nobject);
		
		template<typename egFunctionObject_t> void dealloc_egFunctionObject();						//Currently not implemented (just there so it works)
		template<> void dealloc_egFunctionObject<eg::Controller>();
		template<> void dealloc_egFunctionObject<eg::Input>();
		template<> void dealloc_egFunctionObject<eg::Model>();
		template<> void dealloc_egFunctionObject<eg::View>();
		template<> void dealloc_egFunctionObject<eg::DataManipulator>();

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

		virtual void base_bindController();
		virtual void base_unbindController();

		std::vector<eg::Controller*> attachedController;
		std::vector<eg::Input*> attachedInput;
		std::vector<eg::Model*> attachedModel;
		std::vector<eg::View*> attachedView;
		std::vector<eg::DataManipulator*> attachedDataManipulator;
		std::vector<eg::Base*> attachedBase;						//Should only be used for search sort of things

		eg::Param controller_param;
		eg::Controller* boundController;
	};

} //end namspace eg