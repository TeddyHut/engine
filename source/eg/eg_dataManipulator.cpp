#include "../../include/base/eg_dataManipulator.h"

static std::string const _egNAME_FILE_seg_ = eg::util::truncateFilename(__FILE__);
std::string const eg::DataManipulator::_egNAME_OBJECT_seg_ = "eg::DataManipulator";

eg::DataManipulator::DataReferenceWrapper::operator eg::DataReference&() {
	return(dataReference);
}

eg::DataManipulator::DataReferenceWrapper& eg::DataManipulator::DataReferenceWrapper::operator= (eg::DataReference const& p0) {
	dataReference = p0;
	return(*this);
}

eg::DataManipulator::DataReferenceWrapper::DataReferenceWrapper(DataReference const& ndataReference, size_t const nreferenceCount) : dataReference(ndataReference), referenceCount(nreferenceCount) {
}

eg::Param<eg::DataManipulator::DataManipulator_Param_e> const eg::DataManipulator::DataManipulator_Param_d(1, true,
	eg::DataManipulator::DataManipulator_Param_e::Deallocate_AllData_UponDecontruction, true);


bool eg::DataManipulator::dataManipulator_loadData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param) {
	return(dataManipulator_loadData_process(rtrn, dataReference, param));
}

bool eg::DataManipulator::dataManipulator_freeData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param) {
	return(dataManipulator_freeData_process(rtrn, dataReference, param));
}

bool eg::DataManipulator::dataManipulator_writeData(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param) {
	return(dataManipulator_writeData_exe(rtrn, dataReference));
}

bool eg::DataManipulator::dataManipulator_loadData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param) {
	static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_loadData-set";
	size_t loaded = 0;															//Initialise loaded -> Will count how many are allocated
	for (auto&& element0 : dataReferenceSet) {									//Iterate through elements
		dataManipulator_loadData_process(rtrn, element0, param);				//Attempt to load element
		if (rtrn) {																//If failure
			for (size_t i = 0; i < loaded;i++) {								//Iterate through loaded elements
				dataManipulator_freeData_process(rtrn, dataReferenceSet[i]);	//Free loaded element
				if (rtrn) break;												//If that doesn't work... Well.
			}
			break;																//Exit loop
		}
		loaded++;																//Add to count of loaded elements
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);						//This function has been successfull (I guess)
	return(rtrn);																//Return result
}

bool eg::DataManipulator::dataManipulator_freeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param) {
	static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_freeData-set";
	for (auto&& element0 : dataReferenceSet) {
		dataManipulator_freeData_process(rtrn, element0, param);
		if (rtrn) break;
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::DataManipulator::dataManipulator_writeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param) {
	static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_writeData-set";
	for (auto&& element0 : dataReferenceSet) {
		dataManipulator_writeData_exe(rtrn, element0);
		if (rtrn) break;
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::DataManipulator::dataManipulator_deallocAllData(eg::GlbRtrn& rtrn) {
	static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_deallocAllData";
	for (size_t i = 0; i < dataManipulator_allocatedData.size();i++) {		//If this doesn't work out just make a copy of allocatedData and use that
		size_t a = dataManipulator_allocatedData.size();
		eg::Param<eg::FreeData_Param_e> param(eg::FreeData_Param_z, true,
			FreeData_Param_e::Function_All, true,
			FreeData_Param_e::Condition_TypeOnly, false,
			FreeData_Param_e::Condition_FromEnd, false,
			FreeData_Param_e::Condition_IgnoreAlteration, true,
			FreeData_Param_e::Condition_IgnoreReferenceCount, true,
			FreeData_Param_e::Data_SetNull, true);
		dataManipulator_freeData(rtrn, dataManipulator_allocatedData[i], param);
		i -= (a - dataManipulator_allocatedData.size());
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::DataManipulator::dataManipulator_loadedData(eg::DataReference const& dataReference) const {
	for (auto&& element : dataManipulator_allocatedData) {
		if (element.dataReference.dataType == dataReference.dataType) {
			return(true);
		}
	}
	return(false);
}

bool eg::DataManipulator::dataManipulator_loadedData(eg::DataReferenceSet const& dataReferenceSet) const {
	for (auto&& element0 : dataReferenceSet) {
		if (!dataManipulator_loadedData(element0)) {
			return(false);
		}
	}
	return(true);
}

eg::DataManipulator::DataManipulator() :
	dataManipulator_param(DataManipulator_Param_d),
	dataManipulator_loadData_exe([](eg::GlbRtrn& rtrn, eg::DataReference& dataReference)->bool { static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_loadData_exe-defualt"; eg_GlbRtrn_egResult(rtrn, eg::LoadData_Result_DefaultFunction_r); return(rtrn); }),
	dataManipulator_freeData_exe([](eg::GlbRtrn& rtrn, eg::DataReference& dataReference)->bool { static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_freeData_exe-defualt"; eg_GlbRtrn_egResult(rtrn, eg::FreeData_Result_DefaultFunction_r); return(rtrn); }),
	dataManipulator_writeData_exe([](eg::GlbRtrn& rtrn, eg::DataReference const& dataReference)->bool { static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_writeData_exe-defualt"; eg_GlbRtrn_egResult(rtrn, eg::WriteData_Result_DefaultFunction_r); return(rtrn); }) {
	
#if defined(_CPPRTTI) || defined(__RTTI)
	functionType.set_basetype<eg::DataManipulator>();
#else
	functionType.set_basetype(_egNAME_OBJECT_seg_);
#endif
}

eg::DataManipulator::~DataManipulator() {
	eg::GlbRtrn rtrn;
	dataManipulator_deallocAllData(rtrn);
	rtrn.check();
}

bool eg::DataManipulator::dataManipulator_loadData_process(eg::GlbRtrn& rtrn, eg::DataReference& dataReference,eg::Param<eg::LoadData_Param_e> const param) {
	static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_loadData_process";
	std::function<bool(eg::GlbRtrn&, eg::DataReference&)> allocateData = [this](eg::GlbRtrn& rtrn, eg::DataReference& dataReference)->bool {	//Create a lambda to allocate data because... Reasons.
		static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_loadData_process/allocateData";
		dataManipulator_loadData_exe(rtrn, dataReference);																	//Attemp to load element
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);																//Did what it should
		if (!rtrn) dataReference.load_dataManipulator = this;																//Set loading dataManipulator to this
		return(rtrn);																										//Return result
	};
	if(!param[eg::LoadData_Param_e::Data_New]) {																			//If wants to check for pre-allocated one
		for (auto&& element : dataManipulator_allocatedData) {																//Iterate through loaded elements
			if ((element == dataReference) && (param[eg::LoadData_Param_e::Condition_IgnoreAlteration] || (element.dataReference.alteration == dataReference.alteration))) {																					//If a matching type is found
				dataReference = element.dataReference;																		//Copy data over
				element.referenceCount++;																					//Increase the reference count
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(rtrn);																								//Return result
			}
		}
	}
	allocateData(rtrn, dataReference);																						//Allocate new data
	if(!rtrn) dataManipulator_allocatedData.push_back(DataReferenceWrapper(dataReference,1));								//Add element to loaded data
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);																	//Did what it should
	return(rtrn);																											//Return result
}

bool eg::DataManipulator::dataManipulator_freeData_process(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param) {
	std::function<bool(eg::GlbRtrn& rtrn, size_t const)> freeData = [&](eg::GlbRtrn& rtrn, size_t const itr)->bool {	//Will decrement the reference count of allocatedData[-itr-], and free if necessary
		static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_freeData_process/freeData";
		dataManipulator_allocatedData[itr].referenceCount--;										//Subtract -referenceCount-
		if ((dataManipulator_allocatedData[itr].referenceCount == 0)||(param[FreeData_Param_e::Condition_IgnoreReferenceCount])) {	//If the -referenceCount- reaches 0 or ignore reference count
			dataManipulator_freeData_exe(rtrn, dataManipulator_allocatedData[itr]);					//Free the data
			if (!rtrn) {																			//If it was successful
				dataManipulator_allocatedData.erase(dataManipulator_allocatedData.begin() + itr);	//Erase from allocatedData
				if (param[FreeData_Param_e::Data_SetNull]) {										//if requests setnull
					dataReference.dataSize = eg::DataReference::DATASIZE_UNDEFINED;					//Set external -dataReference- size to undefined
					dataReference.dataType = eg::DataReference::DATATYPE_UNDEFINED;					//Set external -dataReference- type to undefined
					dataReference.dataPointer = nullptr;											//Set external -dataReference- pointer to nullptr
				}
			}
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
		return(rtrn);																				//Return result
	};
	std::function<bool(eg::DataReference const&, eg::DataReference const&)> compare_typeonly_f = [param](eg::DataReference const& p0, eg::DataReference const& p1)->bool {	//Will compare -p0- and -p1- according to param
		return((param[FreeData_Param_e::Condition_IgnoreAlteration] || (p0.alteration == p1.alteration)) && (((param[FreeData_Param_e::Condition_TypeOnly]) && (p0 == p1)) || ((p0.dataType == p1.dataType) && (p0.dataPointer == p1.dataPointer) && (p0.dataSize == p1.dataSize))));	//Longest conditional statement ever (maybe check if not working)
	};
	std::function<std::tuple<size_t const,size_t const>(DataReference const&,size_t const)> dataReference_fromend_f = [&](eg::DataReference const& p0, const size_t bgn_itr = 0)->std::tuple<size_t const,size_t const> {	//Will find the location of the next allocatedData matching -p0- after -bgn_itr-
		if (param[FreeData_Param_e::Condition_FromEnd]) {				//If searching from end
			size_t const fromend_begin = dataManipulator_allocatedData.size() - 1 - bgn_itr;	//Set -fromend_begin- to size-1 (size = 1 past end) --bgn_itr- (where to start)
			for (size_t i = fromend_begin;true;i--) {											//Set -i- to fromend_begin, iterate forever, decrement -i-
				if (compare_typeonly_f(dataManipulator_allocatedData[i], p0)) return(std::make_tuple(i, dataManipulator_allocatedData.size()-i));	//If a match was found within conditions conditions return return location and match location
				if (i == 0)  break;																//If -i- == 0 break
			}
		}
		else {																					//If not searching from end
			for (size_t i = bgn_itr; i < dataManipulator_allocatedData.size(); i++) {			//Iterate through -allocatedData-
				if (compare_typeonly_f(dataManipulator_allocatedData[i], p0)) {
					return(std::make_tuple(i, i+1));	//If a match was found within conditions conditions return return location and match location
				}
			}
		}
		return(std::make_tuple(dataManipulator_allocatedData.size(), dataManipulator_allocatedData.size()));	//Nothing was found
	};
	static std::string const _egNAME_FUNCTION_seg_ = "dataManipulator_freeData_process";
	if (param[FreeData_Param_e::Function_All]) {											//if asked to free all matching -dataReference-
		for (size_t itr = 0; itr != dataManipulator_allocatedData.size();) {				//while values are still being found
			auto tuple_fromend = dataReference_fromend_f(dataReference, itr);				//Find next matching dataReference
			itr = std::get<1>(tuple_fromend);												//Offset to start at if going to find one again
			if (std::get<0>(tuple_fromend) != dataManipulator_allocatedData.size()) {		//if one was found
				freeData(rtrn, std::get<0>(tuple_fromend));									//Free the data
				if (dataReference.dataPointer == nullptr) itr--;							//if data was deleted -> subtract itr to make up for .erase()
				if (rtrn) break;															//if there was a failure -> break
			}
		}
	}
	else {																					//if not asked to free all matching -dataReference-
		auto tuple_fromend = dataReference_fromend_f(dataReference, 0);						//Find matching dataReference
			if (std::get<0>(tuple_fromend) != dataManipulator_allocatedData.size()) {		//if one was found
			freeData(rtrn, std::get<0>(tuple_fromend));										//Free the data
		}
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);																			//Return result
}

void eg::DataManipulator::base_bindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->add_egFunctionObject(this);
}

void eg::DataManipulator::base_unbindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->remove_egFunctionObject(this);
}