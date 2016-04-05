#pragma once

#include <cstdint>
#include <vector>

#include "eg_declaration.h"
#include "eg_util.h"
#include "eg_type.h"
#include "eg_dataReference.h"
#include "eg_blankController.h"

namespace eg {
	class Base {
	public:
		static size_t const BASE_PARAM_RUNOVER_INIT;							//Default = 1; States if the init function will be run
		static size_t const BASE_PARAM_CONTROLLER_BOUND;						//Default = 0; States if a controller is bound to the base
		static size_t const BASE_PARAM_DYMALLOC;								//Default = 0; States if object was dynamically allocated
		static eg::Param const BASE_Param_DEFAULT;

		virtual void base_runover(void* rundata);								//Base runover, including -rundata- (sort of up to personal interpretation)
		virtual void runover_init(void* rundata);								//Will run before first runover, or according to -RUNOVER_INIT-
		virtual void runover(void* rundata);									//Main runover for subclasses

		virtual void set_boundController(eg::BlankController* const ncontroller);			//Sets -boundController- and adds itself to the controller

		virtual eg::FunctionType get_functionType() const;						//Will return the functionType
		virtual eg::BlankController* get_boundController() const;					//Will return the boundcontroller

		eg::Param base_param;

		Base();
		virtual ~Base();
	protected:
		virtual eg::GlbRtrn loadData(eg::DataReference& dataReference, eg::Param const param = eg::DATAMANIPULATOR_LOADDATA_Param_DEFAULT) const;
		virtual eg::GlbRtrn freeData(eg::DataReference& dataReference, eg::Param const param = eg::DATAMANIPULATOR_FREEDATA_Param_DEFAULT) const;
		virtual eg::GlbRtrn writeData(eg::DataReference const& dataReference, eg::Param const param = eg::DATAMANIPULATOR_WRITEDATA_Param_DEFAULT) const;
		virtual eg::GlbRtrn loadData(eg::DataReferenceSet& dataReferenceSet, eg::Param const param = eg::DATAMANIPULATOR_LOADDATA_Param_DEFAULT) const;
		virtual eg::GlbRtrn freeData(eg::DataReferenceSet& dataReferenceSet, eg::Param const param = eg::DATAMANIPULATOR_FREEDATA_Param_DEFAULT) const;
		virtual eg::GlbRtrn writeData(eg::DataReferenceSet const& dataReferenceSet, eg::Param const param = eg::DATAMANIPULATOR_WRITEDATA_Param_DEFAULT) const;

		virtual void base_bindController() = 0;		//Apparently there needs to be a subclass implementation of this... Probably because it's specific to base subclass
		virtual void base_unbindController() = 0;	//Apparently there also needs to be a subclass implementation of this...

		eg::FunctionType functionType;
		eg::BlankController* boundController;
		std::function<void(Base* const nobject)> base_unbindFunction;
	};

} //end namespace eg
