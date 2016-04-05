#include "../../include/base/eg_controller.h"

static std::string const _egNAME_FILE_seg_ = eg::util::truncateFilename(__FILE__);
std::string const eg::Controller::_egNAME_OBJECT_seg_ = "eg::Controller";

eg::Param<eg::Controller::Controller_Param_e> const eg::Controller::Controller_Param_d(5, true,
	eg::Controller::Controller_Param_e::Deallocate_Attached_Controller, true,
	eg::Controller::Controller_Param_e::Deallocate_Attached_Input, true,
	eg::Controller::Controller_Param_e::Deallocate_Attached_Model, true,
	eg::Controller::Controller_Param_e::Deallocate_Attached_View, true,
	eg::Controller::Controller_Param_e::Deallocate_Attached_DataManipulator, true);

void eg::Controller::runover_controller(void* rundata) {
	for (auto&& element : attachedController) {
		element->runover_controller(rundata);
	}
	base_runover(rundata);
}

void eg::Controller::runover_input(void* rundata) {
	for (auto&& element : attachedController) {
		element->runover_input(rundata);
	}
	for (auto&& element : attachedInput) {
		element->base_runover(rundata);
	}
}

void eg::Controller::runover_model(void* rundata) {
	for (auto&& element : attachedController) {
		element->runover_model(rundata);
	}
	for (auto&& element : attachedModel) {
		element->base_runover(rundata);
	}
}

void eg::Controller::runover_view(void* rundata) {
	for (auto&& element : attachedController) {
		element->runover_view(rundata);
	}
	for (auto&& element : attachedView) {
		element->base_runover(rundata);
	}
}

void eg::Controller::runover_dataManipulator(void* rundata) {
	for (auto&& element : attachedController) {
		element->runover_dataManipulator(rundata);
	}
	for (auto&& element : attachedDataManipulator) {
		element->base_runover(rundata);
	}
}

bool eg::Controller::base_loadData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const { //Maybe rewrite this for priority (eg compare_equal has higher importance than compare true)
	static std::string const _egNAME_FUNCTION_seg_ = "base_loadData-ref";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_loadData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::Controller::base_freeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "base_freeData-ref";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_freeData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::Controller::base_writeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "base_writeData-ref";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReference, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_writeData(rtrn, dataReference, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::Controller::base_loadData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "base_loadData-set";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReferenceSet, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_loadData(rtrn, dataReferenceSet, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::Controller::base_freeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "base_freeData-set";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReferenceSet, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_freeData(rtrn, dataReferenceSet, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

bool eg::Controller::base_writeData(eg::GlbRtrn& rtrn, eg::Base const*const base, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "base_writeData-set";
	eg::DataManipulator* dataManipulator = find_matching_dataManipulator(rtrn, dataReferenceSet, scope_param);
	if (!rtrn) {
		dataManipulator->dataManipulator_writeData(rtrn, dataReferenceSet, param);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(rtrn);
}

eg::Base* eg::Controller::base_requestPointer(eg::GlbRtrn& rtrn, eg::Base const*const base0, eg::FunctionType const type0, eg::Param<eg::Scope_Param_e> param) const {
	auto searchLocal = [&]()->eg::Base* {
		static std::string const _egNAME_FUNCTION_seg_ = "base_requestPointer/searchLocal";
		for (auto&& element0 : attachedBase) {
			if ((eg::FunctionType::compare_true(type0, element0->get_functionType())) && (eg::FunctionType::compare_basematch(type0, element0->get_functionType()))) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(element0);
			}
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};
	auto searchExternal = [&]()->eg::Base* {
		static std::string const _egNAME_FUNCTION_seg_ = "base_requestPointer/searchExternal";
		eg::Base* base_rtrn;
		for (auto&& element : externalController) {
			base_rtrn = element->base_requestPointer(rtrn, this, type0, param);
			if (!rtrn) {
				eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
				return(base_rtrn);
			}
			rtrn.validate();
		}
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
		return(nullptr);
	};
	static std::string const _egNAME_FUNCTION_seg_ = "base_requestPointer";
	eg::Base* base_rtrn;
	if (param[Scope_Param_e::Scope_LocalFirst] || param[Scope_Param_e::Scope_LocalOnly]) {
		base_rtrn = searchLocal();
		if (!rtrn) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
			return(base_rtrn);
		}
		else if (param[Scope_Param_e::Scope_LocalOnly]) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
			return(nullptr);
		}
		rtrn.validate();
	}
	base_rtrn = searchExternal();
	if (!rtrn) {
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
		return(base_rtrn);
	}
	else if (!param[Scope_Param_e::Scope_LocalFirst]) {
		rtrn.validate();
		base_rtrn = searchLocal();
		if (!rtrn) {
			eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
			return(base_rtrn);
		}
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(nullptr);
}

void eg::Controller::add_egFunctionObject(eg::Base* const nobject) {
#if defined(_CPPRTTI) || defined(__RTTI)
	if (typeid(eg::Controller).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::Controller* const>(nobject));
	if (typeid(eg::Input).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::Input* const>(nobject));
	if (typeid(eg::Model).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::Model* const>(nobject));
	if (typeid(eg::View).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::View* const>(nobject));
	if (typeid(eg::DataManipulator).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::DataManipulator* const>(nobject));
#else
	if (eg::type::get_string_hash(eg::Controller::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(static_cast<eg::Controller* const>(nobject));
	if (eg::type::get_string_hash(eg::Input::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(static_cast<eg::Input* const>(nobject));
	if (eg::type::get_string_hash(eg::Model::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(static_cast<eg::Model* const>(nobject));
	if (eg::type::get_string_hash(eg::View::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(static_cast<eg::View* const>(nobject));
	if (eg::type::get_string_hash(eg::DataManipulator::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(static_cast<eg::DataManipulator* const>(nobject));
#endif
}

void eg::Controller::add_egFunctionObject(eg::Controller* const nobject) {
	attachedController.push_back(nobject);
}

void eg::Controller::add_egFunctionObject(eg::Input* const nobject) {
	attachedInput.push_back(nobject);
	add_Base(nobject);
}

void eg::Controller::add_egFunctionObject(eg::Model* const nobject) {
	attachedModel.push_back(nobject);
	add_Base(nobject);
}

void eg::Controller::add_egFunctionObject(eg::View* const nobject) {
	attachedView.push_back(nobject);
	add_Base(nobject);
}

void eg::Controller::add_egFunctionObject(eg::DataManipulator* const nobject) {
	attachedDataManipulator.push_back(nobject);
	add_Base(nobject);
}

void eg::Controller::add_externalController(eg::Controller const*const nobject) {
	externalController.push_back(nobject);
}

void eg::Controller::remove_egFunctionObject(eg::Base* const nobject) {
#if defined(_CPPRTTI) || defined(__RTTI)
	if (typeid(eg::Controller).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::Controller* const>(nobject));
	if (typeid(eg::Input).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::Input* const>(nobject));
	if (typeid(eg::Model).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::Model* const>(nobject));
	if (typeid(eg::View).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::View* const>(nobject));
	if (typeid(eg::DataManipulator).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::DataManipulator* const>(nobject));
#else
	if (eg::type::get_string_hash(eg::Controller::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(static_cast<eg::Controller* const>(nobject));
	if (eg::type::get_string_hash(eg::Input::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(static_cast<eg::Input* const>(nobject));
	if (eg::type::get_string_hash(eg::Model::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(static_cast<eg::Model* const>(nobject));
	if (eg::type::get_string_hash(eg::View::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(static_cast<eg::View* const>(nobject));
	if (eg::type::get_string_hash(eg::DataManipulator::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(static_cast<eg::DataManipulator* const>(nobject));
#endif
}

void eg::Controller::remove_egFunctionObject(eg::Controller* const nobject) {
	for (size_t i = 0; i < attachedController.size(); i++) {
		if (attachedController[i] == nobject) {
			attachedController.erase(attachedController.begin() + i);
			break;
			//Mabye some more implementation here (like set the object to haveing no controller... Who knows.
		}
	}
}

void eg::Controller::remove_egFunctionObject(eg::Input* const nobject) {
	for (size_t i = 0; i < attachedInput.size(); i++) {
		if (attachedInput[i] == nobject) {
			attachedInput.erase(attachedInput.begin() + i);
			break;
			//Mabye some more implementation here (like set the object to haveing no controller... Who knows.
		}
	}
	remove_Base(nobject);
}

void eg::Controller::remove_egFunctionObject(eg::Model* const nobject) {
	for (size_t i = 0; i < attachedModel.size(); i++) {
		if (attachedModel[i] == nobject) {
			attachedModel.erase(attachedModel.begin() + i);
			break;
			//Mabye some more implementation here (like set the object to haveing no controller... Who knows.
		}
	}
	remove_Base(nobject);
}

void eg::Controller::remove_egFunctionObject(eg::View* const nobject) {
	for (size_t i = 0; i < attachedView.size(); i++) {
		if (attachedView[i] == nobject) {
			attachedView.erase(attachedView.begin() + i);
			break;
			//Mabye some more implementation here (like set the object to haveing no controller... Who knows.
		}
	}
	remove_Base(nobject);
}

void eg::Controller::remove_egFunctionObject(eg::DataManipulator* const nobject) {
	for (size_t i = 0; i < attachedDataManipulator.size(); i++) {
		if (attachedDataManipulator[i] == nobject) {
			attachedDataManipulator.erase(attachedDataManipulator.begin() + i);
			break;
			//Mabye some more implementation here (like set the object to haveing no controller... Who knows.
		}
	}
	remove_Base(nobject);
}

void eg::Controller::remove_externalController(eg::Controller const*const nobject) {
	for (size_t i = 0; i < externalController.size(); i++) {
		if (externalController[i] == nobject) {
			externalController.erase(externalController.begin() + i);
			break;
			//Mabye some more implementation here (like set the object to haveing no controller... Who knows.
		}
	}
}

void eg::Controller::dealloc_egFunctionObject_Controller() {
	std::vector<eg::Controller*> temp = attachedController;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::Base_Param_e::Info_DynamicallyAllocated]) delete element;
	}
}

void eg::Controller::dealloc_egFunctionObject_Input() {
	std::vector<eg::Input*> temp = attachedInput;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::Base_Param_e::Info_DynamicallyAllocated]) delete element;
	}
}

void eg::Controller::dealloc_egFunctionObject_Model() {
	std::vector<eg::Model*> temp = attachedModel;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::Base_Param_e::Info_DynamicallyAllocated]) delete element;
	}
}

void eg::Controller::dealloc_egFunctionObject_View() {
	std::vector<eg::View*> temp = attachedView;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::Base_Param_e::Info_DynamicallyAllocated]) delete element;
	}
}

void eg::Controller::dealloc_egFunctionObject_DataManipulator() {
	std::vector<eg::DataManipulator*> temp = attachedDataManipulator;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::Base_Param_e::Info_DynamicallyAllocated]) delete element;
	}
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Base const*const nobject) {
#if defined(_CPPRTTI) || defined(__RTTI)
	if (typeid(eg::Controller).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::Controller const*const>(nobject)));
	if (typeid(eg::Input).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::Input const*const>(nobject)));
	if (typeid(eg::Model).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::Model const*const>(nobject)));
	if (typeid(eg::View).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::View const*const>(nobject)));
	if (typeid(eg::DataManipulator).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::DataManipulator const*const>(nobject)));
#else
	if (eg::type::get_string_hash(eg::Controller::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(static_cast<eg::Controller const*const>(nobject)));
	if (eg::type::get_string_hash(eg::Input::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(static_cast<eg::Input const*const>(nobject)));
	if (eg::type::get_string_hash(eg::Model::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(static_cast<eg::Model const*const>(nobject)));
	if (eg::type::get_string_hash(eg::View::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(static_cast<eg::View const*const>(nobject)));
	if (eg::type::get_string_hash(eg::DataManipulator::_egNAME_OBJECT_seg_) == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(static_cast<eg::DataManipulator const*const>(nobject)));
#endif
	return(nullptr);
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Controller const*const nobject) {
	return([this](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::Controller* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Input const*const nobject) {
	return([this](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::Input* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Model const*const nobject) {
	return([this](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::Model* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::View const*const nobject) {
	return([this](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::View* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::DataManipulator const*const nobject) {
	return([this](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::DataManipulator* const>(nobject));
	});
}

eg::Controller::Controller() : controller_param(Controller_Param_d) {
#if defined(_CPPRTTI) || defined(__RTTI)
	functionType.set_basetype<eg::Controller>();
#else
	functionType.set_basetype(_egNAME_OBJECT_seg_);
#endif
}

eg::Controller::~Controller() {
	if (controller_param[Controller_Param_e::Deallocate_Attached_Controller]) dealloc_egFunctionObject_Controller();
	if (controller_param[Controller_Param_e::Deallocate_Attached_Input]) dealloc_egFunctionObject_Input();
	if (controller_param[Controller_Param_e::Deallocate_Attached_Model]) dealloc_egFunctionObject_Model();
	if (controller_param[Controller_Param_e::Deallocate_Attached_View]) dealloc_egFunctionObject_View();
	if (controller_param[Controller_Param_e::Deallocate_Attached_DataManipulator]) dealloc_egFunctionObject_DataManipulator();
}

void eg::Controller::add_Base(eg::Base* const nbase) {
	attachedBase.push_back(nbase);
}

void eg::Controller::remove_Base(eg::Base* const nbase) {
	for (size_t i = 0; i < attachedBase.size(); i++) {
		if (attachedBase[i] == nbase) {
			attachedBase.erase(attachedBase.begin() + i);
			break;
			//Mabye some more implementation here (like set the object to haveing no controller... Who knows.
		}
	}
}

eg::DataManipulator* eg::Controller::find_matching_dataManipulator(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<eg::Scope_Param_e> const param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "find_matching_dataManipulator-ref";
	eg::DataReferenceSet dataReferenceSet;
	dataReferenceSet.add_DataReference(dataReference);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	return(find_matching_dataManipulator(rtrn, dataReferenceSet, param));
}

eg::DataManipulator* eg::Controller::find_matching_dataManipulator(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::Scope_Param_e> const param) const {
	auto searchLocal = [&]()->eg::DataManipulator* {
		static std::string const _egNAME_FUNCTION_seg_ = "find_matching_dataManipulator-set/searchLocal";
		eg::FunctionType dataFunction;
#if defined(_CPPRTTI) || defined(__RTTI)
		dataFunction.set_basetype<eg::DataManipulator>();
#else
		dataFunction.set_basetype(eg::DataManipulator::_egNAME_OBJECT_seg_);
#endif
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
		dataFunction.set_basetype<eg::DataManipulator>();
#else
		dataFunction.set_basetype(eg::DataManipulator::_egNAME_OBJECT_seg_);
#endif
		for (auto&& element1 : dataReferenceSet) {
			dataFunction.functionType.push_back(static_cast<eg::DataReference const&>(element1).dataType);
		}
		for (auto&& element : externalController) {
			dataManipulator_rtrn = static_cast<eg::DataManipulator*>(element->base_requestPointer(rtrn, this, dataFunction, param));
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

void eg::Controller::base_bindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr) {
		ncontroller = boundController;
	}
	ncontroller->add_egFunctionObject(this);
}

void eg::Controller::base_unbindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->remove_egFunctionObject(this);
}