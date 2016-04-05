#include "../../include/base/eg_view.h"

eg::View::View() {
	functionType.set_basetype<eg::View>();
}

void eg::View::base_bindController() {
	boundController->add_egFunctionObject(this);
}

void eg::View::base_unbindController() {
	boundController->remove_egFunctionObject(this);
}