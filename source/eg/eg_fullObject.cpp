#include "../../include/base/eg_fullObject.h"

static std::string const _egNAME_FILE_seg_ = eg::util::truncateFilename(__FILE__);
std::string const eg::FullObject::_egNAME_OBJECT_seg_ = "eg::FullObject";

eg::Param<eg::FullObject::FullObject_Param_e> const eg::FullObject::FullObject_Param_d;

bool eg::FullObject::object_loadData(eg::GlbRtrn& rtrn, eg::Object const*const object, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const { //Maybe rewrite this for priority (eg compare_equal has higher importance than compare true)
	static std::string const _egNAME_FUNCTION_seg_ = "object_loadData-ref";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_loadData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_freeData(eg::GlbRtrn& rtrn, eg::Object const*const object, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_freeData-ref";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_freeData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_writeData(eg::GlbRtrn& rtrn, eg::Object const*const object, eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_writeData-ref";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_writeData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_loadData(eg::GlbRtrn& rtrn, eg::Object const*const object, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_loadData-set";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReferenceSet, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_loadData(rtrn, dataReferenceSet, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_freeData(eg::GlbRtrn& rtrn, eg::Object const*const object, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_freeData-set";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReferenceSet, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_freeData(rtrn, dataReferenceSet, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::FullObject::object_writeData(eg::GlbRtrn& rtrn, eg::Object const*const object, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "object_writeData-set";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReferenceSet, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_writeData(rtrn, dataReferenceSet, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

eg::Object* eg::FullObject::object_requestPointer(eg::GlbRtrn& rtrn, eg::Object const*const object0, eg::FunctionType const type0, eg::Param<eg::Scope_Param_e> param) const {
	auto searchLocal = [&]()->eg::Object* {
		static std::string const _egNAME_FUNCTION_seg_ = "object_requestPointer/searchLocal";
		for (auto&& element0 : attachedObject) {
			if ((eg::FunctionType::compare_true(type0, element0->get_functionType())) && (eg::FunctionType::compare_objectmatch(type0, element0->get_functionType()))) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(element0);
			}
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};
	auto searchExternal = [&]()->eg::Object* {
		static std::string const _egNAME_FUNCTION_seg_ = "object_requestPointer/searchExternal";
		eg::Object* object_rtrn;
		for (auto&& element : externalFullObject) {
			object_rtrn = element->object_requestPointer(rtrn, this, type0, param);
			if (!rtrn) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(object_rtrn);
			}
			rtrn.validate();
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};
	static std::string const _egNAME_FUNCTION_seg_ = "object_requestPointer";
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

void eg::FullObject::add_Object(eg::Object* const nobject) {
#if defined(_CPPRTTI) || defined(__RTTI)
	if (typeid(eg::FullObject).hash_code() == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(dynamic_cast<eg::FullObject* const>(nobject));
	if (typeid(eg::Input).hash_code() == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(dynamic_cast<eg::Input* const>(nobject));
	if (typeid(eg::Model).hash_code() == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(dynamic_cast<eg::Model* const>(nobject));
	if (typeid(eg::View).hash_code() == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(dynamic_cast<eg::View* const>(nobject));
	if (typeid(eg::DataManipulator).hash_code() == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(dynamic_cast<eg::DataManipulator* const>(nobject));
#else
	if (eg::type::get_string_hash(eg::FullObject::_egNAME_OBJECT_seg_) == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(static_cast<eg::FullObject* const>(nobject));
	if (eg::type::get_string_hash(eg::Input::_egNAME_OBJECT_seg_) == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(static_cast<eg::Input* const>(nobject));
	if (eg::type::get_string_hash(eg::Model::_egNAME_OBJECT_seg_) == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(static_cast<eg::Model* const>(nobject));
	if (eg::type::get_string_hash(eg::View::_egNAME_OBJECT_seg_) == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(static_cast<eg::View* const>(nobject));
	if (eg::type::get_string_hash(eg::DataManipulator::_egNAME_OBJECT_seg_) == nobject->get_functionType().objecttype_hashcode) add_egFunctionObject(static_cast<eg::DataManipulator* const>(nobject));
#endif
}





std::function<void(eg::Object* const nobject)> eg::FullObject::object_get_unbindFunction(eg::FullObject const*const nobject) {
	return([this](Object* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::FullObject* const>(nobject));
	});
}

eg::DataManipulator* eg::FullObject::find_matching_dataManipulator(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<eg::Scope_Param_e> const param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "find_matching_dataManipulator-ref";
	eg::DataReferenceSet dataReferenceSet;
	dataReferenceSet.add_DataReference(dataReference);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(find_matching_dataManipulator(rtrn, dataReferenceSet, param));
}

eg::DataManipulator* eg::FullObject::find_matching_dataManipulator(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::Scope_Param_e> const param) const {
	auto searchLocal = [&]()->eg::DataManipulator* {
		static std::string const _egNAME_FUNCTION_seg_ = "find_matching_dataManipulator-set/searchLocal";
		eg::FunctionType dataFunction;
		dataFunction.set_objecttype<eg::DataManipulator>();
		for (auto&& element1 : dataReferenceSet) {
			dataFunction.functionType.push_back(static_cast<eg::DataReference const&>(element1).dataType);
		}
		for (auto&& element0 : attachedDataManipulator) {
			eg::FunctionType manipulatorFunction = element0->get_functionType();
			if (eg::FunctionType::compare_true(dataFunction, manipulatorFunction)) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(element0);
			}
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};
	auto searchExternal = [&]()->eg::DataManipulator* {
		static std::string const _egNAME_FUNCTION_seg_ = "find_matching_dataManipulator-set/searchExternal";
		eg::DataManipulator* dataManipulator_rtrn;
		eg::FunctionType dataFunction;
#if defined(_CPPRTTI) || defined(__RTTI)
		dataFunction.set_objecttype<eg::DataManipulator>();
#else
		dataFunction.set_objecttype(eg::DataManipulator::_egNAME_OBJECT_seg_);
#endif
		for (auto&& element1 : dataReferenceSet) {
			dataFunction.functionType.push_back(static_cast<eg::DataReference const&>(element1).dataType);
		}
		for (auto&& element : externalFullObject) {
			dataManipulator_rtrn = static_cast<eg::DataManipulator*>(element->object_requestPointer(rtrn, this, dataFunction, param));
			if (!rtrn) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(dataManipulator_rtrn);
			}
			rtrn.validate();
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};
	static std::string const _egNAME_FUNCTION_seg_ = "find_matching_dataManipulator-set";
	eg::DataManipulator* dataManipulator_rtrn;
	if (param[Scope_Param_e::Scope_LocalFirst] || param[Scope_Param_e::Scope_LocalOnly]) {
		dataManipulator_rtrn = searchLocal();
		if (!rtrn) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
			return(dataManipulator_rtrn);
		}
		else if (param[Scope_Param_e::Scope_LocalOnly]) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
			return(nullptr);
		}
		rtrn.validate();
	}
	dataManipulator_rtrn = searchExternal();
	if (!rtrn) {
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
		return(dataManipulator_rtrn);
	}
	else if (!param[Scope_Param_e::Scope_LocalFirst]) {
		rtrn.validate();
		dataManipulator_rtrn = searchLocal();
		if (!rtrn) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
			return(dataManipulator_rtrn);
		}
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(nullptr);
}

void eg::FullObject::object_bindFullObject(eg::BlankFullObject* nfullObject) {
	if (nfullObject == nullptr) {
		nfullObject = boundFullObject;
	}
	nfullObject->add_egFunctionObject(this);
}

void eg::FullObject::object_unbindFullObject(eg::BlankFullObject* nfullObject) {
	if (nfullObject == nullptr)
		nfullObject = boundFullObject;
	nfullObject->remove_egFunctionObject(this);
}