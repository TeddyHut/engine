#pragma once

#include <cstdint>
#include <vector>
#include <functional>
#include <tuple>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_util.h"
#include "eg_dataReference.h"
#include "eg_base.h"

namespace eg {

	class DataManipulator : public eg::Base {
	public:
		class DataReferenceWrapper {
		public:
			operator eg::DataReference&();
			DataReferenceWrapper& operator= (DataReference const& p0);

			eg::DataReference dataReference;
			size_t referenceCount;
			DataReferenceWrapper(DataReference const& ndataReference, size_t const nreferenceCount);
		};
		static size_t const DATAMANIPULATOR_GLBRTRN_DEFAULTEXE;			//Error when using data operation; Default exe function
		static size_t const DATAMANIPULATOR_GLBRTRN_LOAD;				//Error when loading data;
		static size_t const DATAMANIPULATOR_GLBRTRN_FREE;				//Error when freeing data;
		static size_t const DATAMANIPULATOR_GLBRTRN_WRITE;				//Error when writing data;

		static size_t const DATAMANIPULATOR_PARAM_DEALLOC;				//Default = 1; All data will be deallocated on desctruction of manipulator
		static eg::Param const DATAMANIPULATOR_Param_DEFAULT;

		//virtual void runover(DataManipulator_rundata* dataManipulator_rundata);

		virtual eg::GlbRtrn dataManipulator_loadData(eg::DataReference& dataReference, eg::Param const param = DATAMANIPULATOR_LOADDATA_Param_DEFAULT);					//loadData according to dataReference
		virtual eg::GlbRtrn dataManipulator_freeData(eg::DataReference& dataReference, eg::Param const param = DATAMANIPULATOR_FREEDATA_Param_DEFAULT);					//freeData according to dataReference
		virtual eg::GlbRtrn dataManipulator_writeData(eg::DataReference const& dataReference, eg::Param const param = DATAMANIPULATOR_WRITEDATA_Param_DEFAULT);			//writeData according to dataReference
		virtual eg::GlbRtrn dataManipulator_loadData(eg::DataReferenceSet& dataReferenceSet, eg::Param const param = DATAMANIPULATOR_LOADDATA_Param_DEFAULT);			//loadData according to dataReferenceSet
		virtual eg::GlbRtrn dataManipulator_freeData(eg::DataReferenceSet& dataReferenceset, eg::Param const param = DATAMANIPULATOR_FREEDATA_Param_DEFAULT);			//freeData according to dataReferenceSet
		virtual eg::GlbRtrn dataManipulator_writeData(eg::DataReferenceSet const& dataReferenceSet, eg::Param const param = DATAMANIPULATOR_WRITEDATA_Param_DEFAULT);	//writeData according to dataReferenceSet

		virtual eg::GlbRtrn dataManipulator_deallocAllData();	//Deallocates all data within allocatedData

		eg::Param dataManipulator_param;

		DataManipulator();	//Constructor
		virtual ~DataManipulator();		//Destructor
	protected:
		std::function<eg::GlbRtrn(eg::DataReference& dataReference)> dataManipulator_loadData_exe;			//Loaddata sublass -> Should point to a lambda calling a static function
		std::function<eg::GlbRtrn(eg::DataReference& dataReference)> dataManipulator_freeData_exe;			//Loaddata sublass -> Should point to a lambda calling a static function
		std::function<eg::GlbRtrn(eg::DataReference const& dataReference)> dataManipulator_writeData_exe;	//Loaddata sublass -> Should point to a lambda calling a static function
		
		virtual eg::GlbRtrn dataManipulator_loadData_process(eg::DataReference& dataReference, eg::Param const param = DATAMANIPULATOR_LOADDATA_Param_DEFAULT);	//Acts upon param
		virtual eg::GlbRtrn dataManipulator_freeData_process(eg::DataReference& dataReference, eg::Param const param = DATAMANIPULATOR_FREEDATA_Param_DEFAULT);	//Acts upon param
		
		virtual void base_bindController();
		virtual void base_unbindController();

		std::vector<DataReferenceWrapper> dataManipulator_allocatedData;	//Vector of all allocated dataReference
	};

}