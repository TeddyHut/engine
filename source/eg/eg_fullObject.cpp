#include "../../include/eg/eg_fullObject.h"

static std::string const _egNAME_FILE_seg_ = eg::util::truncateFilename(__FILE__);
std::string const eg::FullObject::_egNAME_OBJECT_seg_ = "eg::FullObject";

eg::Param<eg::FullObject::FullObject_Param_e> const eg::FullObject::FullObject_Param_d;

void eg::FullObject::runover_fullObject(void *rundata) {
	//Runover self
	object_runover(rundata);
	//Runover attached dataManipulators
	for (auto &&element : attachedObject) {
		if ((element->description[Key::egType] & Value::egType::DataManipulator) && (!(element->description[Key::egType] & Value::egType::FullObject))) {
			element->object_runover(rundata);
		}
	}
	//Runover attached non-dataManipulator objects
	for (auto &&element : attachedObject) {
		if ((!(element->description[Key::egType] & Value::egType::DataManipulator)) && (!(element->description[Key::egType] & Value::egType::FullObject))) {
			element->object_runover(rundata);
		}
	}
	//Call runover_fullObject (this function) for attached fullObjects
	for (auto &&element : attachedObject) {
		if (element->description[Key::egType] & Value::egType::FullObject) {
			FullObject *fullObject = dynamic_cast<FullObject *>(element);
			fullObject->runover_fullObject(rundata);
		}
	}
}

bool eg::FullObject::object_loadData(eg::GlbRtrn &rtrn, eg::Object const *const object, eg::DataReference &dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const { //Maybe rewrite this for priority (eg compare_equal has higher importance than compare true)
	static std::string const _egNAME_FUNCTION_seg_ = "object_loadData-ref";
	auto result = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		result->dataManipulator_loadData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_freeData(eg::GlbRtrn &rtrn, eg::Object const *const object, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_freeData-ref";
	auto result = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		result->dataManipulator_freeData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_writeData(eg::GlbRtrn &rtrn, eg::Object const *const object, eg::DataReference &dataReference, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_writeData-ref";
	auto result = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		result->dataManipulator_writeData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_loadData(eg::GlbRtrn &rtrn, eg::Object const *const object, eg::DataReferenceSet &dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_loadData-set";
	size_t loaded = 0;															//Initialise loaded -> Will count how many are allocated
	for (auto&& element0 : dataReferenceSet) {									//Iterate through elements
		object_loadData(rtrn, this, element0, param);							//Attempt to load element
		if (rtrn) {																//If failure
			eg_GlbRtrn_egResult(rtrn, Main_Result_Failure_r);					//Add failure to rtrn
			for (size_t i = 0; i < loaded; i++) {								//Iterate through loaded elements
				object_freeData(rtrn, object, dataReferenceSet[i]);				//Free loaded element
				if (rtrn) break;												//If that doesn't work... Well.
			}
			break;																//Exit loop
		}
		loaded++;																//Add to count of loaded elements
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);						//This function has been successfull (I guess)
	return(rtrn);																//Return result
}

bool eg::FullObject::object_freeData(eg::GlbRtrn &rtrn, eg::Object const *const object, eg::DataReferenceSet &dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_freeData-set";
	for (auto&& element0 : dataReferenceSet) {
		object_freeData(rtrn, object, element0, param, scope_param);
		if (rtrn) break;
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_writeData(eg::GlbRtrn &rtrn, eg::Object const *const object, eg::DataReferenceSet &dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_writeData-set";
	for (auto&& element0 : dataReferenceSet) {
		object_writeData(rtrn, object, element0, param, scope_param);
		if (rtrn) break;
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

eg::Object* eg::FullObject::object_requestPointer(eg::GlbRtrn &rtrn, eg::Object const *const requester, eg::Descriptor<> desc, eg::Param<eg::Scope_Param_e> param) const {
	//Create lambda for localSearch function
	auto searchLocal = [&]()->eg::Object * {
		static std::string const _egNAME_FUNCTION_seg_ = "object_requestPointer/searchLocal";
		//Iterate through attached objects
		for (auto &&element0 : attachedObject) {
			//Compare to determine whether the iterated object in question has all the necessary descriptions
			if((element0->description & desc) == desc) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(element0);
			}
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};

	//Create lambda for externalSearch function
	auto searchExternal = [&]()->eg::Object* {
		static std::string const _egNAME_FUNCTION_seg_ = "object_requestPointer/searchExternal";
		//The object to be returned
		eg::Object* object_rtrn;
		//Need to do this because there is a chance that if being called up the chain, then rtrn will be false
		rtrn.validate();
		//Check to determine whether a search can be conducted further up the chain
		if (this->object_param[Object_Param_e::State_FullObjectBound]) {
			object_rtrn = this->boundFullObject->object_requestPointer(rtrn, requester, desc, param);
			//If it a result was found
			if (!rtrn) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(object_rtrn);
			}
		}
		//If a result cannot be found, return a failure.
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};

	static std::string const _egNAME_FUNCTION_seg_ = "object_requestPointer";
	//Check to make sure that there is something in the description
	if (!desc) {
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	}
	eg::Object* object_rtrn;
	if (param[Scope_Param_e::Scope_LocalFirst] || param[Scope_Param_e::Scope_LocalOnly]) {
		object_rtrn = searchLocal();
		if (!rtrn) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
			return(object_rtrn);
		}
		else if (param[Scope_Param_e::Scope_LocalOnly]) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
			return(nullptr);
		}
		rtrn.validate();
	}
	object_rtrn = searchExternal();
	if (!rtrn) {
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
		return(object_rtrn);
	}
	else if (!param[Scope_Param_e::Scope_LocalFirst]) {
		rtrn.validate();
		object_rtrn = searchLocal();
		if (!rtrn) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
			return(object_rtrn);
		}
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(nullptr);
}

void eg::FullObject::add_egObject(eg::Object *const nobject) {
	add_object(nobject);
}

void eg::FullObject::remove_egObject(eg::Object *const nobject) {
	remove_object(nobject);
}

void eg::FullObject::dealloc_egObject() {
	//Pretty dodgy, but whatevs for now
	for (auto &&object : attachedObject) {
		if (object->object_param[Object_Param_e::Info_DynamicallyAllocated]) {
			delete object;
			object = nullptr;
		}
	}
}

std::function<void(eg::Object* const nobject)> eg::FullObject::object_get_unbindFunction() {
	return([this](Object* const nobject)->void {
		this->remove_egObject(static_cast<eg::FullObject* const>(nobject));
	});
}

eg::FullObject::FullObject() {
	//For some reason it didn't like this being in the constructor initializer...
	description[Key::egType] += Value::egType::FullObject;
}

eg::FullObject::~FullObject() {
	for (auto &&element : attachedObject) {
		if (element->object_param[Object_Param_e::Info_DynamicallyAllocated]) {
			delete element;
			//Meh.
		}
	}
}

void eg::FullObject::add_object(Object *const nobject) {
	attachedObject.push_back(nobject);
}

void eg::FullObject::remove_object(Object *const nobject) {
	util::remove_p0_from_p1(std::vector<eg::Object *>{nobject}, attachedObject);
}

eg::DataManipulator* eg::FullObject::find_matching_dataManipulator(eg::GlbRtrn& rtrn, eg::DataReference &dataReference, eg::Param<eg::Scope_Param_e> const param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "find_matching_dataManipulator-ref";
	//Get the description of the data requested
	if (!(dataReference.description)) {
		eg_GlbRtrn_egResult(rtrn, Main_Result_Failure_r);
		//Return the result
		return(nullptr);
	}
	auto dataManipulator_description = dataReference.description;
	//Add the value DataManipulator to key eg::Type to make sure that only DataManipulators are searched
	dataManipulator_description[Key::egType] += Value::egType::DataManipulator;
	//Search for the respective dataManipulator
	DataManipulator *result = dynamic_cast<DataManipulator *>(object_requestPointer(rtrn, this, dataManipulator_description, param));
	//This function did what it was supposed to
	eg_GlbRtrn_egResult(rtrn, Main_Result_Success_r);
	//Return the result
	return(result);
}
