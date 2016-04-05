#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <functional>
#include <tuple>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_util.h"
#include "eg_definition.h"
#include "eg_dataReference.h"
#include "eg_base.h"

namespace eg {

	class DataManipulator : public eg::Base {
	public:
		static std::string const _egNAME_OBJECT_seg_;
		class DataReferenceWrapper {
		public:
			operator eg::DataReference&();
			DataReferenceWrapper& operator= (DataReference const& p0);

			eg::DataReference dataReference;
			size_t referenceCount;
			DataReferenceWrapper(DataReference const& ndataReference, size_t const nreferenceCount);
		};
		enum class DataManipulator_Param_e {
			Deallocate_AllData_UponDecontruction = 0	//Default = 1; All data will be deallocated on desctruction of manipulator
		}; static eg::Param<DataManipulator_Param_e> const DataManipulator_Param_d;

		//virtual void runover(DataManipulator_rundata* dataManipulator_rundata);

		virtual bool dataManipulator_loadData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d);				//loadData according to dataReference
		virtual bool dataManipulator_freeData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d);				//freeData according to dataReference
		virtual bool dataManipulator_writeData(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param = eg::WriteData_Param_d);	//writeData according to dataReference
		virtual bool dataManipulator_loadData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d);		//loadData according to dataReferenceSet
		virtual bool dataManipulator_freeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceset, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d);		//freeData according to dataReferenceSet
		virtual bool dataManipulator_writeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<WriteData_Param_e> const param = eg::WriteData_Param_d);	//writeData according to dataReferenceSet

		virtual bool dataManipulator_deallocAllData(eg::GlbRtrn& rtrn);	//Deallocates all data within allocatedData

		virtual bool dataManipulator_loadedData(eg::DataReference const& dataReference) const;			//Will return true if -dataReference- is loaded
		virtual bool dataManipulator_loadedData(eg::DataReferenceSet const& detaReferenceSet) const;	//Will return true if -dataReferenceSet- is loaded
		
		eg::Param<DataManipulator_Param_e> dataManipulator_param;

		DataManipulator();	//Constructor
		virtual ~DataManipulator();		//Destructor
	protected:
		std::function<bool(eg::GlbRtrn& rtrn, eg::DataReference& dataReference)> dataManipulator_loadData_exe;			//Loaddata sublass -> Should point to a lambda calling a static function
		std::function<bool(eg::GlbRtrn& rtrn, eg::DataReference& dataReference)> dataManipulator_freeData_exe;			//Loaddata sublass -> Should point to a lambda calling a static function
		std::function<bool(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference)> dataManipulator_writeData_exe;	//Loaddata sublass -> Should point to a lambda calling a static function
		
		virtual bool dataManipulator_loadData_process(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param = eg::LoadData_Param_d);	//Acts upon param
		virtual bool dataManipulator_freeData_process(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param = eg::FreeData_Param_d);	//Acts upon param
		
		virtual void base_bindController(eg::BlankController* ncontroller = nullptr) override;
		virtual void base_unbindController(eg::BlankController* ncontroller = nullptr) override;

		std::vector<DataReferenceWrapper> dataManipulator_allocatedData;	//Vector of all allocated dataReference
	};

}