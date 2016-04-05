#include "../../include/base/eg_input.h"

std::string const eg::Input::_egNAME_OBJECT_seg_ = "eg::Input";

eg::Input::Input() {
#if defined(_CPPRTTI) || defined(__RTTI)
	functionType.set_basetype<eg::Input>();
#else
	functionType.set_basetype(_egNAME_OBJECT_seg_);
#endif
}

void eg::Input::base_bindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->add_egFunctionObject(this);
}

void eg::Input::base_unbindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->remove_egFunctionObject(this);
}