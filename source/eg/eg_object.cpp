#include "../../include/eg/eg_object.h"

static std::string const _egNAME_FILE_seg_ = eg::util::truncateFilename(__FILE__);

eg::Param<eg::Object::Object_Param_e> const eg::Object::Object_Param_d(3, true,
	eg::Object::Object_Param_e::State_RunRunoverInit, true,
	eg::Object::Object_Param_e::State_FullObjectBound, false,
	eg::Object::Object_Param_e::Info_DynamicallyAllocated, false);

void eg::Object::object_runover(void *rundata) {
	if(object_param[Object_Param_e::State_RunRunoverInit]) {
		runover_init(rundata);
		object_param[Object_Param_e::State_RunRunoverInit] = false;
	}
	else
		runover(rundata);
}

void eg::Object::runover_init(void *rundata) {
}

void eg::Object::runover(void *rundata) {
}

void eg::Object::set_boundFullObject(eg::FullObject_abs_p* const nfullobject) {
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		object_bindFullObject(nullptr);
		object_param[Object_Param_e::State_FullObjectBound] = false;
		boundFullObject = nullptr;
	}
	if (nfullobject != nullptr) {
		boundFullObject = nfullobject;
		object_bindFullObject(boundFullObject);
		object_unbindFunction = boundFullObject->object_get_unbindFunction();
		object_param[Object_Param_e::State_FullObjectBound] = true;
	}
}

eg::FullObject_abs_p* eg::Object::get_boundFullObject() const {
	return(boundFullObject);
}

eg::Object::Object() {
}

eg::Object::~Object() {
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		object_unbindFunction(this);
	}
}

bool eg::Object::loadData(eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-ref";
	eg::GlbRtrn rtrn;
	loadData(rtrn, dataReference, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Object::freeData(eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-ref";
	eg::GlbRtrn rtrn;
	freeData(rtrn, dataReference, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Object::writeData(eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-ref";
	eg::GlbRtrn rtrn;
	writeData(rtrn, dataReference, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Object::loadData(eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-set";
	eg::GlbRtrn rtrn;
	loadData(rtrn, dataReferenceSet, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Object::freeData(eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-set";
	eg::GlbRtrn rtrn;
	freeData(rtrn, dataReferenceSet, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Object::writeData(eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-set";
	eg::GlbRtrn rtrn;
	writeData(rtrn, dataReferenceSet, param, scope_param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(rtrn);
}

bool eg::Object::loadData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-glb,ref";
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		boundFullObject->object_loadData(rtrn, this, dataReference, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Object::freeData(eg::GlbRtrn& rtrn, eg::DataReference& dataReference, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-glb,ref";
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		boundFullObject->object_freeData(rtrn, this, dataReference, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Object::writeData(eg::GlbRtrn& rtrn, eg::DataReference const& dataReference, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-glb,ref";
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		boundFullObject->object_writeData(rtrn, this, dataReference, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Object::loadData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::LoadData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "loadData-glb,set";
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		boundFullObject->object_loadData(rtrn, this, dataReferenceSet, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Object::freeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet& dataReferenceSet, eg::Param<eg::FreeData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "freeData-glb,set";
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		boundFullObject->object_freeData(rtrn, this, dataReferenceSet, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

bool eg::Object::writeData(eg::GlbRtrn& rtrn, eg::DataReferenceSet const& dataReferenceSet, eg::Param<eg::WriteData_Param_e> const param, eg::Param<eg::Scope_Param_e> const scope_param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "writeData-glb,set";
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		boundFullObject->object_writeData(rtrn, this, dataReferenceSet, param, scope_param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	}
	else eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(rtrn);
}

eg::Object* eg::Object::requestPointer(eg::Descriptor<> const desc, eg::Param<eg::Scope_Param_e> param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "requestPointer";
	eg::GlbRtrn rtrn;
	eg::Object* object_rtrn = requestPointer(rtrn, desc, param);
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
	rtrn.check();
	return(object_rtrn);
}

eg::Object* eg::Object::requestPointer(eg::GlbRtrn& rtrn, eg::Descriptor<> const desc, eg::Param<eg::Scope_Param_e> param) const {
	static std::string const _egNAME_FUNCTION_seg_ = "requestPointer-glb";
	if (object_param[Object_Param_e::State_FullObjectBound]) {
		eg::Object* object_rtrn = boundFullObject->object_requestPointer(rtrn, this, desc, param);
		eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Success_r);
		return(object_rtrn);
	}
	eg_GlbRtrn_egResult(rtrn, eg::Main_Result_Failure_r);
	return(nullptr);
}

void eg::Object::object_bindFullObject(eg::FullObject_abs_p *const nobject) {
	if (nobject == nullptr) {
		if (object_param[Object_Param_e::State_FullObjectBound]) {
			object_unbindFunction(this);
		}
	}
	else {
		nobject->add_egObject(this);
	}
}
