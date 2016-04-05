#include "../../include/base/eg_controller.h"

size_t const eg::Controller::CONTROLLER_PARAM_DEALLOCCONTROLLER = 1;
size_t const eg::Controller::CONTROLLER_PARAM_DEALLOCINPUT = 2;
size_t const eg::Controller::CONTROLLER_PARAM_DEALLOCMODEL = 3;
size_t const eg::Controller::CONTROLLER_PARAM_DEALLOCVIEW = 4;
size_t const eg::Controller::CONTROLLER_PARAM_DEALLOCDATAMANIPULATOR = 5;
eg::Param const eg::Controller::CONTROLLER_Param_DEFAULT(5,
	eg::Controller::CONTROLLER_PARAM_DEALLOCCONTROLLER, true,
	eg::Controller::CONTROLLER_PARAM_DEALLOCINPUT, true,
	eg::Controller::CONTROLLER_PARAM_DEALLOCMODEL, true,
	eg::Controller::CONTROLLER_PARAM_DEALLOCVIEW, true,
	eg::Controller::CONTROLLER_PARAM_DEALLOCDATAMANIPULATOR, true);

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

eg::GlbRtrn eg::Controller::base_loadData(eg::Base const*const base, eg::DataReference& dataReference, eg::Param const param) { //Maybe rewrite this for priority (eg compare_equal has higher importance than compare true)
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_FAILURE;
	for (auto&& element0 : attachedDataManipulator) {
		eg::FunctionType manipulatorFunction = element0->get_functionType();
		eg::FunctionType dataFunction;
		dataFunction.functionType.push_back(dataReference.dataType);
		if (eg::FunctionType::compare_true(dataFunction, manipulatorFunction)) {
			rtrn = element0->dataManipulator_loadData(dataReference, param);
			break;
		}
	}
	return(rtrn);
}

eg::GlbRtrn eg::Controller::base_freeData(eg::Base const*const base, eg::DataReference& dataReference, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_FAILURE;
	for (auto&& element0 : attachedDataManipulator) {
		eg::FunctionType manipulatorFunction = element0->get_functionType();
		eg::FunctionType dataFunction;
		dataFunction.functionType.push_back(dataReference.dataType);
		if (eg::FunctionType::compare_true(dataFunction, manipulatorFunction)) {
			rtrn = element0->dataManipulator_freeData(dataReference, param);
			break;
		}
	}
	return(rtrn);
}

eg::GlbRtrn eg::Controller::base_writeData(eg::Base const*const base, eg::DataReference const& dataReference, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_FAILURE;
	for (auto&& element0 : attachedDataManipulator) {
		eg::FunctionType manipulatorFunction = element0->get_functionType();
		eg::FunctionType dataFunction;
		dataFunction.functionType.push_back(dataReference.dataType);
		if (eg::FunctionType::compare_true(dataFunction, manipulatorFunction)) {
			rtrn = element0->dataManipulator_writeData(dataReference, param);
			break;
		}
	}
	return(rtrn);
}

eg::GlbRtrn eg::Controller::base_loadData(eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_FAILURE;
	for (auto&& element0 : attachedDataManipulator) {
		eg::FunctionType manipulatorFunction = element0->get_functionType();
		eg::FunctionType dataFunction;
		for (auto&& element1 : dataReferenceSet) {
			dataFunction.functionType.push_back(static_cast<eg::DataReference>(element1).dataType);
		}
		if (eg::FunctionType::compare_true(dataFunction, manipulatorFunction)) {
			rtrn = element0->dataManipulator_loadData(dataReferenceSet, param);
			break;
		}
	}
	return(rtrn);
}

eg::GlbRtrn eg::Controller::base_freeData(eg::Base const*const base, eg::DataReferenceSet& dataReferenceSet, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_FAILURE;
	for (auto&& element0 : attachedDataManipulator) {
		eg::FunctionType manipulatorFunction = element0->get_functionType();
		eg::FunctionType dataFunction;
		for (auto&& element1 : dataReferenceSet) {
			dataFunction.functionType.push_back(static_cast<eg::DataReference>(element1).dataType);
		}
		if (eg::FunctionType::compare_true(dataFunction, manipulatorFunction)) {
			rtrn = element0->dataManipulator_freeData(dataReferenceSet, param);
			break;
		}
	}
	return(rtrn);
}

eg::GlbRtrn eg::Controller::base_writeData(eg::Base const*const base, eg::DataReferenceSet const& dataReferenceSet, eg::Param const param) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_FAILURE;
	for (auto&& element0 : attachedDataManipulator) {
		eg::FunctionType manipulatorFunction = element0->get_functionType();
		eg::FunctionType dataFunction;
		for (auto&& element1 : dataReferenceSet) {
			dataFunction.functionType.push_back(static_cast<eg::DataReference>(element1).dataType);
		}
		if (eg::FunctionType::compare_true(dataFunction, manipulatorFunction)) {
			rtrn = element0->dataManipulator_writeData(dataReferenceSet, param);
			break;
		}
	}
	return(rtrn);
}

eg::GlbRtrn eg::Controller::base_requestPointer(eg::Base* base0, eg::Base** base1, eg::FunctionType const type0) {
	eg::GlbRtrn rtrn = eg::GlbRtrn::RTRN_FAILURE;
	*base1 = nullptr;
	for (auto&& element0 : attachedBase) {
		if (eg::FunctionType::compare_true(type0, element0->get_functionType())) {
			rtrn = eg::GlbRtrn::RTRN_SUCCESS;
			*base1 = element0;
			break;
		}
	}
	return(rtrn);
}

void eg::Controller::add_egFunctionObject(eg::Base* const nobject) {
	if (typeid(eg::Controller).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::Controller* const>(nobject));
	if (typeid(eg::Input).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::Input* const>(nobject));
	if (typeid(eg::Model).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::Model* const>(nobject));
	if (typeid(eg::View).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::View* const>(nobject));
	if (typeid(eg::DataManipulator).hash_code() == nobject->get_functionType().basetype_hashcode) add_egFunctionObject(dynamic_cast<eg::DataManipulator* const>(nobject));
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

void eg::Controller::remove_egFunctionObject(eg::Base* const nobject) {
	if (typeid(eg::Controller).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::Controller* const>(nobject));
	if (typeid(eg::Input).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::Input* const>(nobject));
	if (typeid(eg::Model).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::Model* const>(nobject));
	if (typeid(eg::View).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::View* const>(nobject));
	if (typeid(eg::DataManipulator).hash_code() == nobject->get_functionType().basetype_hashcode) remove_egFunctionObject(dynamic_cast<eg::DataManipulator* const>(nobject));
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

template<typename egFunctionObject_t> void eg::Controller::dealloc_egFunctionObject() {
	//That's right. Nothing.
}

template<> void eg::Controller::dealloc_egFunctionObject<eg::Controller>() {
	std::vector<eg::Controller*> temp = attachedController;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::BASE_PARAM_DYMALLOC]) delete element;
	}
}

template<> void eg::Controller::dealloc_egFunctionObject<eg::Input>() {
	std::vector<eg::Input*> temp = attachedInput;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::BASE_PARAM_DYMALLOC]) delete element;
	}
}

template<> void eg::Controller::dealloc_egFunctionObject<eg::Model>() {
	std::vector<eg::Model*> temp = attachedModel;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::BASE_PARAM_DYMALLOC]) delete element;
	}
}

template<> void eg::Controller::dealloc_egFunctionObject<eg::View>() {
	std::vector<eg::View*> temp = attachedView;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::BASE_PARAM_DYMALLOC]) delete element;
	}
}

template<> void eg::Controller::dealloc_egFunctionObject<eg::DataManipulator>() {
	std::vector<eg::DataManipulator*> temp = attachedDataManipulator;
	for (auto&& element : temp) {
		if (element->base_param[eg::Base::BASE_PARAM_DYMALLOC]) delete element;
	}
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Base const*const nobject) {
	if (typeid(eg::Controller).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::Controller const*const>(nobject)));
	if (typeid(eg::Input).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::Input const*const>(nobject)));
	if (typeid(eg::Model).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::Model const*const>(nobject)));
	if (typeid(eg::View).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::View const*const>(nobject)));
	if (typeid(eg::DataManipulator).hash_code() == nobject->get_functionType().basetype_hashcode) return(base_get_unbindFunction(dynamic_cast<eg::DataManipulator const*const>(nobject)));
	return(nullptr);
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Controller const*const nobject) {
	return([=](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::Controller* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Input const*const nobject) {
	return([=](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::Input* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::Model const*const nobject) {
	return([=](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::Model* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::View const*const nobject) {
	return([=](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::View* const>(nobject));
	});
}

std::function<void(eg::Base* const nobject)> eg::Controller::base_get_unbindFunction(eg::DataManipulator const*const nobject) {
	return([=](Base* const nobject)->void {
		this->remove_egFunctionObject(static_cast<eg::DataManipulator* const>(nobject));
	});
}

eg::Controller::Controller() : controller_param(CONTROLLER_Param_DEFAULT) {
}

eg::Controller::~Controller() {
	if (controller_param[CONTROLLER_PARAM_DEALLOCCONTROLLER]) dealloc_egFunctionObject<eg::Controller>();
	if (controller_param[CONTROLLER_PARAM_DEALLOCINPUT]) dealloc_egFunctionObject<eg::Input>();
	if (controller_param[CONTROLLER_PARAM_DEALLOCMODEL]) dealloc_egFunctionObject<eg::Model>();
	if (controller_param[CONTROLLER_PARAM_DEALLOCVIEW]) dealloc_egFunctionObject<eg::View>();
	if (controller_param[CONTROLLER_PARAM_DEALLOCDATAMANIPULATOR]) dealloc_egFunctionObject<eg::DataManipulator>();
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

void eg::Controller::base_bindController() {
	boundController->add_egFunctionObject(this);
}

void eg::Controller::base_unbindController() {
	boundController->remove_egFunctionObject(this);
}