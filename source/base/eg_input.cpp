#include "../../include/base/eg_input.h"

eg::Input::Input() {
	functionType.set_basetype<eg::Input>();
}

void eg::Input::base_bindController() {
	boundController->add_egFunctionObject(this);
}

void eg::Input::base_unbindController() {
	boundController->remove_egFunctionObject(this);
}