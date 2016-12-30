#include "../../include/eg/eg_definition.h"

size_t const eg::LoadData_Param_z = 2;
eg::Param<eg::LoadData_Param_e> const eg::LoadData_Param_d(eg::LoadData_Param_z, true,
	eg::LoadData_Param_e::Data_New, false,
	eg::LoadData_Param_e::Condition_IgnoreAlteration, false);

size_t const eg::FreeData_Param_z = 6;
eg::Param<eg::FreeData_Param_e> const eg::FreeData_Param_d(eg::FreeData_Param_z, true,
	eg::FreeData_Param_e::Function_All, false,
	eg::FreeData_Param_e::Condition_DescriptionOnly, false,
	eg::FreeData_Param_e::Condition_FromEnd, false,
	eg::FreeData_Param_e::Condition_IgnoreAlteration, false,
	eg::FreeData_Param_e::Condition_IgnoreReferenceCount, false,
	eg::FreeData_Param_e::Data_SetNull, true);

size_t const eg::WriteData_Param_z = 0;
eg::Param<eg::WriteData_Param_e> const eg::WriteData_Param_d;

size_t const eg::Scope_Param_z = 3;
eg::Param<eg::Scope_Param_e> const eg::Scope_Param_d(eg::Scope_Param_z, true,
	eg::Scope_Param_e::Scope_LocalOnly, false,
	eg::Scope_Param_e::Scope_LocalFirst, false,
	eg::Scope_Param_e::Scope_SetDestination, false);
eg::Param <eg::Scope_Param_e> const eg::Scope_Param_d_Scope_SetDestination1(eg::Scope_Param_z, true,
	eg::Scope_Param_e::Scope_LocalOnly, false,
	eg::Scope_Param_e::Scope_LocalFirst, false,
	eg::Scope_Param_e::Scope_SetDestination, true);

eg::GlbRtrn::Result const eg::LoadData_Result_Error_r(static_cast<size_t>(eg::LoadData_Result_e::Error), true, "LoadData_Error");
eg::GlbRtrn::Result const eg::LoadData_Result_DefaultFunction_r(static_cast<size_t>(eg::LoadData_Result_e::DefaultFunction), true, "LoadData_DefaultFunction");
eg::GlbRtrn::Result const eg::FreeData_Result_Error_r(static_cast<size_t>(eg::FreeData_Result_e::Error), true, "FreeData_Error");
eg::GlbRtrn::Result const eg::FreeData_Result_DefaultFunction_r(static_cast<size_t>(eg::FreeData_Result_e::DefaultFunction), true, "FreeData_DefaultFunction");
eg::GlbRtrn::Result const eg::WriteData_Result_Error_r(static_cast<size_t>(eg::WriteData_Result_e::Error), true, "WriteData_Error");
eg::GlbRtrn::Result const eg::WriteData_Result_DefaultFunction_r(static_cast<size_t>(eg::WriteData_Result_e::DefaultFunction), true, "WriteData_DefaultFunction");