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
#include "eg_object.h"

namespace eg {

	class DataManipulator : public Object {
	public:
		static std::string const _egNAME_OBJECT_seg_;
		class DataReferenceWrapper {
		public:
			operator DataReference&();
			DataReferenceWrapper& operator= (DataReference const& p0);

			DataReference dataReference;
			size_t referenceCount;
			DataReferenceWrapper(DataReference const& ndataReference, size_t const nreferenceCount);
		};
		enum class DataManipulator_Param_e {
			Deallocate_AllData_UponDecontruction = 0	//Default = 1; All data will be deallocated on desctruction of manipulator
		}; static Param<DataManipulator_Param_e> const DataManipulator_Param_d;

		//virtual void runover(DataManipulator_rundata* dataManipulator_rundata);

		virtual bool dataManipulator_loadData(GlbRtrn& rtrn, DataReference& dataReference, Param<LoadData_Param_e> const param = LoadData_Param_d);				//loadData according to dataReference
		virtual bool dataManipulator_freeData(GlbRtrn& rtrn, DataReference& dataReference, Param<FreeData_Param_e> const param = FreeData_Param_d);				//freeData according to dataReference
		virtual bool dataManipulator_writeData(GlbRtrn& rtrn, DataReference const& dataReference, Param<WriteData_Param_e> const param = WriteData_Param_d);	//writeData according to dataReference

		virtual bool dataManipulator_deallocAllData(GlbRtrn& rtrn);	//Deallocates all data within allocatedData

		virtual bool dataManipulator_loadedData(DataReference const& dataReference) const;			//Will return true if -dataReference- is loaded
		virtual bool dataManipulator_loadedData(DataReferenceSet const& detaReferenceSet) const;	//Will return true if -dataReferenceSet- is loaded
		
		Param<DataManipulator_Param_e> dataManipulator_param;

		DataManipulator();	//Constructor
		virtual ~DataManipulator();		//Destructor
	protected:
		std::function<bool(GlbRtrn& rtrn, DataReference& dataReference)> dataManipulator_loadData_exe;			//Loaddata sublass -> Should point to a lambda calling a static function
		std::function<bool(GlbRtrn& rtrn, DataReference& dataReference)> dataManipulator_freeData_exe;			//Loaddata sublass -> Should point to a lambda calling a static function
		std::function<bool(GlbRtrn& rtrn, DataReference const& dataReference)> dataManipulator_writeData_exe;	//Loaddata sublass -> Should point to a lambda calling a static function
		
		virtual bool dataManipulator_loadData_process(GlbRtrn& rtrn, DataReference& dataReference, Param<LoadData_Param_e> const param = LoadData_Param_d);	//Acts upon param
		virtual bool dataManipulator_freeData_process(GlbRtrn& rtrn, DataReference& dataReference, Param<FreeData_Param_e> const param = FreeData_Param_d);	//Acts upon param

		std::vector<DataReferenceWrapper> dataManipulator_allocatedData;	//Vector of all allocated dataReference
	};

}