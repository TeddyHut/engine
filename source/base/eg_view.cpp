#include "../../include/base/eg_view.h"

std::string const eg::View::_egNAME_OBJECT_seg_ = "eg::View";

eg::View::View() {
#if defined(_CPPRTTI) || defined(__RTTI)
	functionType.set_basetype<eg::View>();
#else
	functionType.set_basetype(_egNAME_OBJECT_seg_);
#endif
}

void eg::View::base_bindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->add_egFunctionObject(this);
}

void eg::View::base_unbindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->remove_egFunctionObject(this);
}