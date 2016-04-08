#include "../../include/base/eg_base.h"

static std::string const _egNAME_FILE_seg_ = eg::util::truncateFilename(__FILE__);

eg::Param<eg::Base::Base_Param_e> const eg::Base::Base_Param_d(3, true,
	eg::Base::Base_Param_e::State_RunRunoverInit, true,
	eg::Base::Base_Param_e::State_ControllerBound, false,
	eg::Base::Base_Param_e::Info_DynamicallyAllocated, false);

void eg::Base::base_runover(void* rundata) {
	if(base_param[Base_Param_e::State_RunRunoverInit]) {
		runover_init(rundata);
		base_param[Base_Param_e::State_RunRunoverInit] = false;
	}
	//Maybe do an 'else' runover
	runover(rundata);
}

void eg::Base::runover_init(void* rundata) {
}

void eg::Base::runover(void* rundata) {
}

void eg::Base::set_boundController(eg::BlankController* const ncontroller) {
	if (base_param[Base_Param_e::State_ControllerBound]) {
		base_param[Base_Param_e::State_ControllerBound] = false;
		this->base_unbindController();
		boundController = nullptr;
	}
	if (ncontroller != nullptr) {
		boundController = ncontroller;
		this->base_bindController();
		base_unbindFunction = boundController->base_get_unbindFunction(this);
		base_param[Base_Param_e::State_ControllerBound] = true;
	}
}

eg::FunctionType eg::Base::get_functionType() const {
	return(functionType);
}

eg::BlankController* eg::Base::get_boundController() const {
	return(boundController);
}

eg::Base::Base() : base_param(Base_Param_d), boundController(nullptr) {
}

eg::Base::~Base() {
	if (base_param[Base_Param_e::State_ControllerBound]) {
		base_unbindFunction(this);
	}
}

bool eg::Base::loadData(eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-ref";
	eg::GlbRtrn rtrn;
	loadData(rtrn, dataReference, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Base::freeData(eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-ref";
	eg::GlbRtrn rtrn;
	freeData(rtrn, dataReference, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Base::writeData(eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-ref";
	eg::GlbRtrn rtrn;
	writeData(rtrn, dataReference, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Base::loadData(eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-set";
	eg::GlbRtrn rtrn;
	loadData(rtrn, dataReferenceSet, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Base::freeData(eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-set";
	eg::GlbRtrn rtrn;
	freeData(rtrn, dataReferenceSet, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Base::writeData(eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-set";
	eg::GlbRtrn rtrn;
	writeData(rtrn, dataReferenceSet, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Base::loadData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-glb,ref";
	if (base_param[Base_Param_e::State_ControllerBound]) {
		boundController->base_loadData(rtrn, this, dataReference, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Base::freeData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-glb,ref";
	if (base_param[Base_Param_e::State_ControllerBound]) {
		boundController->base_freeData(rtrn, this, dataReference, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Base::writeData(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-glb,ref";
	if (base_param[Base_Param_e::State_ControllerBound]) {
		boundController->base_writeData(rtrn, this, dataReference, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Base::loadData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-glb,set";
	if (base_param[Base_Param_e::State_ControllerBound]) {
		boundController->base_loadData(rtrn, this, dataReferenceSet, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Base::freeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-glb,set";
	if (base_param[Base_Param_e::State_ControllerBound]) {
		boundController->base_freeData(rtrn, this, dataReferenceSet, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Base::writeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-glb,set";
	if (base_param[Base_Param_e::State_ControllerBound]) {
		boundController->base_writeData(rtrn, this, dataReferenceSet, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

eg::Base* eg::Base::requestPointer(eg::FunctionType type, eg::Param<eg::Scope_Param_e> param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "requestPointer";
	eg::GlbRtrn rtrn;
	eg::Base* base_rtrn = requestPointer(rtrn, type, param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(base_rtrn);
}

eg::Base* eg::Base::requestPointer(eg::GlbRtrn& rtrn, eg::FunctionType type, eg::Param<eg::Scope_Param_e> param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "requestPointer-glb";
	if (base_param[Base_Param_e::State_ControllerBound]) {
		eg::Base* base_rtrn = boundController->base_requestPointer(rtrn, this, type, param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
		return(base_rtrn);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(nullptr);
}