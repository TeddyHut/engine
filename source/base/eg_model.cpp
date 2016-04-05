#include "../../include/base/eg_model.h"

eg::Model::Model() {
	functionType.set_basetype<eg::Model>();
}

void eg::Model::base_bindController() {
	boundController->add_egFunctionObject(this);
}

void eg::Model::base_unbindController() {
	boundController->remove_egFunctionObject(this);
}