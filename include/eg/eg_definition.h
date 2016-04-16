#pragma once

#include <cstdint>
#include <string>

#include "thirdparty/murmur3_32.h"
#include "eg_param.h"
#include "eg_glbRtrn.h"

namespace eg {
	namespace Desc {
		struct Key {
#include "macro/rm_w4307_0.h"
			enum e {
				egType = murmur3_32_value("egType", 6, 0),						//Specifies the egType
			};
#include "macro/rm_w4307_1.h"
		};
		struct Value {
#include "macro/rm_w4307_0.h"
			enum e {
				Object = murmur3_32_value("Object", 6, 0),						//K = egType; Entity is an object (AKA inherited from eg::Object)
				FullObject = murmur3_32_value("FullObject", 10, 0),				//K = egType; Entity is a fullObject (AKA inherited from eg::FullObject)
				DataManipulator = murmur3_32_value("DataManipulator", 15, 0),	//K = egType; Entity is a dataManipulator (AKA inherited from eg::DataManipulator)
			};
#include "macro/rm_w4307_1.h"
		};
	}
	enum class LoadData_Param_e : size_t {
		Data_New = 0,					//Default = 0; Create a new set of data for the alloc
		Condition_IgnoreAlteration		//Default = 0; When searching previous reference will ignore the alteration
	}; extern size_t const LoadData_Param_z; extern eg::Param<LoadData_Param_e> const LoadData_Param_d;

	enum class FreeData_Param_e : size_t {
		Function_All = 0,				//Default = 0; Free all allocated data matching conditions
		Condition_TypeOnly,				//Default = 0; When searching reference to dealloc will only look at type (and alteration if it isn't to be ignored)
		Condition_FromEnd,				//Default = 0; When searching reference to dealloc will start search from end of allocatedData
		Condition_IgnoreAlteration,		//Default = 0; When searching reference to dealloc will ignore the alteration
		Condition_IgnoreReferenceCount,	//Default = 0; When determining whether to dealloc data, will ignore referenceCount
		Data_SetNull					//Default = 1; When dealloc data occurs, external source will have values set to null
	}; extern size_t const FreeData_Param_z; extern eg::Param<FreeData_Param_e> const FreeData_Param_d;

	enum class WriteData_Param_e : size_t {
	}; extern size_t const WriteData_Param_z;  extern eg::Param<WriteData_Param_e> const WriteData_Param_d;

	enum class Scope_Param_e : size_t {
		Scope_LocalOnly = 0,	//Default = 0; Will only load data from controller attached datamanipulators
		Scope_LocalFirst,		//Default = 0; Will first search local dataManipulators for data, then external
		Scope_SetDestination	//Default = 0 (not freedata); Return to the dataManipulator that loaded dataReference for desctuction (or something else later)
	}; extern size_t const Scope_Param_z; extern eg::Param<Scope_Param_e> const Scope_Param_d; extern eg::Param<Scope_Param_e> const Scope_Param_d_Scope_SetDestination1;

	enum class LoadData_Result_e : size_t {
		Error = 2,				//Err... Why does error = 2? Don't think that that is needed.
		DefaultFunction			//No subclass dataManipulator_loadData has been specified
	};
	extern eg::GlbRtrn::Result const LoadData_Result_Error_r;
	extern eg::GlbRtrn::Result const LoadData_Result_DefaultFunction_r;

	enum class FreeData_Result_e : size_t {
		Error = 2,
		DefaultFunction
	};
	extern eg::GlbRtrn::Result const FreeData_Result_Error_r;
	extern eg::GlbRtrn::Result const FreeData_Result_DefaultFunction_r;

	enum class WriteData_Result_e : size_t {
		Error = 2,
		DefaultFunction
	};
	extern eg::GlbRtrn::Result const WriteData_Result_Error_r;
	extern eg::GlbRtrn::Result const WriteData_Result_DefaultFunction_r;
}