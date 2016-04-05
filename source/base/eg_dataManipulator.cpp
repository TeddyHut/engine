#include "../../include/base/eg_dataManipulator.h"

eg::DataManipulator::DataReferenceWrapper::operator eg::DataReference&() {
	return(dataReference);
}

eg::DataManipulator::DataReferenceWrapper& eg::DataManipulator::DataReferenceWrapper::operator= (eg::DataReference const& p0) {
	dataReference = p0;
	return(*this);
}

eg::DataManipulator::DataReferenceWrapper::DataReferenceWrapper(DataReference const& ndataReference, size_t const nreferenceCount) : dataReference(ndataReference), referenceCount(nreferenceCount) {
}

//BLAH! Use strongly typed enums next time :(
size_t const eg::DataManipulator::DATAMANIPULATOR_GLBRTRN_DEFAULTEXE = 2;
size_t const eg::DataManipulator::DATAMANIPULATOR_GLBRTRN_LOAD = 3;
size_t const eg::DataManipulator::DATAMANIPULATOR_GLBRTRN_FREE = 4;
size_t const eg::DataManipulator::DATAMANIPULATOR_GLBRTRN_WRITE = 5;

size_t const eg::DataManipulator::DATAMANIPULATOR_PARAM_DEALLOC = 0;
eg::Param const eg::DataManipulator::DATAMANIPULATOR_Param_DEFAULT(1,
	eg::DataManipulator::DATAMANIPULATOR_PARAM_DEALLOC, true);


eg::GlbRtrn eg::DataManipulator::dataManipulator_loadData(eg::DataReference& dataReference, eg::Param const param) {
	return(dataManipulator_loadData_process(dataReference, param));
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_freeData(eg::DataReference& dataReference, eg::Param const param) {
	return(dataManipulator_freeData_process(dataReference, param));
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_writeData(eg::DataReference const& dataReference, eg::Param const param) {
	return(dataManipulator_writeData_exe(dataReference));
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_loadData(eg::DataReferenceSet& dataReferenceSet, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;								//Create rtrn = RTRN_SUCCESS
	size_t loaded = 0;															//Initialise loaded -> Will count how many are allocated
	for (auto&& element0 : dataReferenceSet) {									//Iterate through elements
		rtrn = dataManipulator_loadData_process(element0, param);				//Attempt to load element
		if (rtrn == eg::GlbRtrn::RTRN_FAILURE) {								//If failure
			for (size_t i = 0; i < loaded;i++) {								//Iterate through loaded elements
				rtrn = dataManipulator_freeData_process(dataReferenceSet[i]);	//Free loaded element
				if (rtrn == GlbRtrn::RTRN_FAILURE) break;						//If that doesn't work... Well.
			}
			break;																//Exit loop
		}
		loaded++;																//Add to count of loaded elements
	}
	return(rtrn);																//Return result
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_freeData(eg::DataReferenceSet& dataReferenceSet, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;
	for (auto&& element0 : dataReferenceSet) {
		rtrn = dataManipulator_freeData_process(element0, param);
		if (rtrn == eg::GlbRtrn::RTRN_FAILURE) break;
	}
	return(rtrn);
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_writeData(eg::DataReferenceSet const& dataReferenceSet, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;
	for (auto&& element0 : dataReferenceSet) {
		rtrn = dataManipulator_writeData_exe(element0);
		if (rtrn == eg::GlbRtrn::RTRN_FAILURE) break;
	}
	return(rtrn);
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_deallocAllData() {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;
	for (size_t i = 0; i < dataManipulator_allocatedData.size();i++) {		//If this doesn't work out just make a copy of allocatedData and use that
		size_t a = dataManipulator_allocatedData.size();
		eg::Param param(5,
			DATAMANIPULATOR_FREEDATA_PARAM_ALL, true,
			DATAMANIPULATOR_FREEDATA_PARAM_TYPEONLY, false,
			DATAMANIPULATOR_FREEDATA_PARAM_FROMEND, false,
			DATAMANIPULATOR_FREEDATA_PARAM_IGNORECOUNT, true,
			DATAMANIPULATOR_FREEDATA_PARAM_SETNULL, false);
		rtrn = dataManipulator_freeData(dataManipulator_allocatedData[i], param);
		i -= (a - dataManipulator_allocatedData.size());
	}
	return(rtrn);
}

eg::DataManipulator::DataManipulator() :
	dataManipulator_param(DATAMANIPULATOR_Param_DEFAULT),
	dataManipulator_loadData_exe([](eg::DataReference& dataReference)->eg::GlbRtrn { return(eg::GlbRtrn::GlbRtrn(eg::DataManipulator::DATAMANIPULATOR_GLBRTRN_DEFAULTEXE)); }),
	dataManipulator_freeData_exe([](eg::DataReference& dataReference)->eg::GlbRtrn { return(eg::GlbRtrn::GlbRtrn(eg::DataManipulator::DATAMANIPULATOR_GLBRTRN_DEFAULTEXE)); }),
	dataManipulator_writeData_exe([](eg::DataReference const& dataReference)->eg::GlbRtrn { return(eg::GlbRtrn::GlbRtrn(eg::DataManipulator::DATAMANIPULATOR_GLBRTRN_DEFAULTEXE)); }) {
	
	functionType.set_basetype<eg::DataManipulator>();
}

eg::DataManipulator::~DataManipulator() {
	dataManipulator_deallocAllData();
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_loadData_process(eg::DataReference& dataReference,eg::Param const param) {
	std::function<eg::GlbRtrn(eg::DataReference&)> allocateData = [this](eg::DataReference& dataReference)->eg::GlbRtrn {	//Create a lambda to allocate data because... Reasons.
		eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;																		//Create rtrn = RTRN_SUCCESS
		rtrn = dataManipulator_loadData_exe(dataReference);																	//Attemp to load element
		return(rtrn);																										//Return result
	};
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;																			//Create rtrn = RTRN_SUCCESS
	if(!param[DATAMANIPULATOR_LOADDATA_PARAM_NEW]){																			//If wants to check for pre-allocated one
		for (auto&& element : dataManipulator_allocatedData) {																//Iterate through loaded elements
			if (element == dataReference) {																					//If a matching type is found
				dataReference = element.dataReference;																		//Copy data over
				element.referenceCount++;																					//Increase the reference count
				return(rtrn);																								//Return result
			}
		}
	}
	rtrn = allocateData(dataReference);																						//Allocate new data
	if(rtrn == eg::GlbRtrn::RTRN_SUCCESS) dataManipulator_allocatedData.push_back(DataReferenceWrapper::DataReferenceWrapper(dataReference,1));	//Add element to loaded data
	return(rtrn);																											//Return result
}

eg::GlbRtrn eg::DataManipulator::dataManipulator_freeData_process(eg::DataReference& dataReference, eg::Param const param) {
	std::function<eg::GlbRtrn(size_t const)> freeData = [&](size_t const itr)->eg::GlbRtrn {	//Will decrement the reference count of allocatedData[-itr-], and free if necessary
		eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;												//Create rtrn = RTRN_SUCCESS
		dataManipulator_allocatedData[itr].referenceCount--;										//Subtract -referenceCount-
		if ((dataManipulator_allocatedData[itr].referenceCount == 0)||(param[DATAMANIPULATOR_FREEDATA_PARAM_IGNORECOUNT])) {	//If the -referenceCount- reaches 0 or ignore reference count
			rtrn = dataManipulator_freeData_exe(dataManipulator_allocatedData[itr]);				//Free the data
			if (rtrn == eg::GlbRtrn::RTRN_SUCCESS) {												//If it was successful
				dataManipulator_allocatedData.erase(dataManipulator_allocatedData.begin() + itr);	//Erase from allocatedData
				if (param[DATAMANIPULATOR_FREEDATA_PARAM_SETNULL]) {								//if requests setnull
					dataReference.dataSize = eg::DataReference::DATASIZE_UNDEFINED;					//Set external -dataReference- size to undefined
					dataReference.dataType = eg::DataReference::DATATYPE_UNDEFINED;					//Set external -dataReference- type to undefined
					dataReference.dataPointer = nullptr;											//Set external -dataReference- pointer to nullptr
				}
			}
		}
		return(rtrn);																				//Return result
	};
	std::function<bool(eg::DataReference const&, eg::DataReference const&)> compare_typeonly_f = [param](eg::DataReference const& p0, eg::DataReference const& p1)->bool {	//Will compare -p0- and -p1- according to param
		return((((param[DATAMANIPULATOR_FREEDATA_PARAM_TYPEONLY]) && (p0 == p1)) || ((!param[DATAMANIPULATOR_FREEDATA_PARAM_TYPEONLY]) && (p0.dataType == p1.dataType) && (p0.dataPointer == p1.dataPointer) && (p0.dataSize == p1.dataSize))));	//Longest conditional statement ever
	};
	std::function<std::tuple<size_t const,size_t const>(DataReference const&,size_t const)> dataReference_fromend_f = [&](eg::DataReference const& p0, const size_t bgn_itr = 0)->std::tuple<size_t const,size_t const> {	//Will find the location of the next allocatedData matching -p0- after -bgn_itr-
		if (param[DATAMANIPULATOR_FREEDATA_PARAM_FROMEND]) {				//If searching from end
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
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_SUCCESS;											//Create rtrn = RTRN_SUCCESS
	if (param[DATAMANIPULATOR_FREEDATA_PARAM_ALL]) {										//if asked to free all matching -dataReference-
		for (size_t itr = 0; itr != dataManipulator_allocatedData.size();) {				//while values are still being found
			auto tuple_fromend = dataReference_fromend_f(dataReference, itr);				//Find next matching dataReference
			itr = std::get<1>(tuple_fromend);												//Offset to start at if going to find one again
			if (std::get<0>(tuple_fromend) != dataManipulator_allocatedData.size()) {		//if one was found
				rtrn = freeData(std::get<0>(tuple_fromend));								//Free the data
				if (dataReference.dataPointer == nullptr) itr--;							//if data was deleted -> subtract itr to make up for .erase()
				if (rtrn == eg::GlbRtrn::RTRN_FAILURE) break;								//if there was a failure -> break
			}
		}
	}
	else {																					//if not asked to free all matching -dataReference-
		auto tuple_fromend = dataReference_fromend_f(dataReference, 0);						//Find matching dataReference
			if (std::get<0>(tuple_fromend) != dataManipulator_allocatedData.size()) {			//if one was found
			rtrn = freeData(std::get<0>(tuple_fromend));									//Free the data
		}
	}
	return(rtrn);																			//Return result
}

void eg::DataManipulator::base_bindController() {
	boundController->add_egFunctionObject(this);
}

void eg::DataManipulator::base_unbindController() {
	boundController->remove_egFunctionObject(this);
}