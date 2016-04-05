#include "../../include/base/eg_model.h"

std::string const eg::Model::_egNAME_OBJECT_seg_ = "eg::Model";

eg::Model::Model() {
#if defined(_CPPRTTI) || defined(__RTTI)
	functionType.set_basetype<eg::Model>();
#else
	functionType.set_basetype(_egNAME_OBJECT_seg_);
#endif
}

void eg::Model::base_bindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->add_egFunctionObject(this);
}

void eg::Model::base_unbindController(eg::BlankController* ncontroller) {
	if (ncontroller == nullptr)
		ncontroller = boundController;
	ncontroller->remove_egFunctionObject(this);
}