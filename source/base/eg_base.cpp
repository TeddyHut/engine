#include "../../include/base/eg_base.h"

size_t const eg::Base::BASE_PARAM_RUNOVER_INIT = 0;
size_t const eg::Base::BASE_PARAM_CONTROLLER_BOUND = 1;
size_t const eg::Base::BASE_PARAM_DYMALLOC = 2;
eg::Param const eg::Base::BASE_Param_DEFAULT(3,
	eg::Base::BASE_PARAM_RUNOVER_INIT, true,
	eg::Base::BASE_PARAM_CONTROLLER_BOUND, false,
	eg::Base::BASE_PARAM_DYMALLOC, false);

void eg::Base::base_runover(void* rundata) {
	if(base_param[BASE_PARAM_RUNOVER_INIT]) {
		runover_init(rundata);
		base_param[BASE_PARAM_RUNOVER_INIT] = false;
	}
	runover(rundata);
}

void eg::Base::runover_init(void* rundata) {
}

void eg::Base::runover(void* rundata) {
}

void eg::Base::set_boundController(eg::BlankController* const ncontroller) {
	if (base_param[BASE_PARAM_CONTROLLER_BOUND]) {
		base_param[BASE_PARAM_CONTROLLER_BOUND] = false;
		this->base_unbindController();
		boundController = nullptr;
	}
	if (ncontroller != nullptr) {
		boundController = ncontroller;
		this->base_bindController();
		base_unbindFunction = boundController->base_get_unbindFunction(this);
		base_param[BASE_PARAM_CONTROLLER_BOUND] = true;
	}
}

eg::FunctionType eg::Base::get_functionType() const {
	return(functionType);
}

eg::BlankController* eg::Base::get_boundController() const {
	return(boundController);
}

eg::Base::Base() : boundController(nullptr), base_param(BASE_Param_DEFAULT) {
}

eg::Base::~Base() {
	if (base_param[BASE_PARAM_CONTROLLER_BOUND]) {
		base_unbindFunction(this);
	}
}

eg::GlbRtrn eg::Base::loadData(eg::DataReference& dataReference, eg::Param const param) const {
	if(base_param[BASE_PARAM_CONTROLLER_BOUND])	return(boundController->base_loadData(this, dataReference, param));
	return(eg::GlbRtrn::GlbRtrn(eg::GlbRtrn::RTRN_FAILURE));
}

eg::GlbRtrn eg::Base::freeData(eg::DataReference& dataReference, eg::Param const param) const {
	if(base_param[BASE_PARAM_CONTROLLER_BOUND]) return(boundController->base_freeData(this, dataReference, param));
	return(eg::GlbRtrn::GlbRtrn(eg::GlbRtrn::RTRN_FAILURE));
}

eg::GlbRtrn eg::Base::writeData(eg::DataReference const& dataReference, eg::Param const param) const {
	if(base_param[BASE_PARAM_CONTROLLER_BOUND]) return(boundController->base_writeData(this, dataReference, param));
	return(eg::GlbRtrn::GlbRtrn(eg::GlbRtrn::RTRN_FAILURE));
}

eg::GlbRtrn eg::Base::loadData(eg::DataReferenceSet& dataReferenceSet, eg::Param const param) const {
	if (base_param[BASE_PARAM_CONTROLLER_BOUND]) return(boundController->base_loadData(this, dataReferenceSet, param));
	return(eg::GlbRtrn::GlbRtrn(eg::GlbRtrn::RTRN_FAILURE));
}

eg::GlbRtrn eg::Base::freeData(eg::DataReferenceSet& dataReferenceSet, eg::Param const param) const {
	if (base_param[BASE_PARAM_CONTROLLER_BOUND]) return(boundController->base_freeData(this, dataReferenceSet, param));
	return(eg::GlbRtrn::GlbRtrn(eg::GlbRtrn::RTRN_FAILURE));
}

eg::GlbRtrn eg::Base::writeData(eg::DataReferenceSet const& dataReferenceSet, eg::Param const param) const {
	if(base_param[BASE_PARAM_CONTROLLER_BOUND]) return(boundController->base_writeData(this, dataReferenceSet, param));
	return(eg::GlbRtrn::GlbRtrn(eg::GlbRtrn::RTRN_FAILURE));
}