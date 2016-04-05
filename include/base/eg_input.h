#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_util.h"
#include "eg_dataReference.h" 
#include "eg_base.h"

namespace eg {
	class Input : public eg::Base {
	public:
		static std::string const _egNAME_OBJECT_seg_;
		Input();
	protected:
		virtual void base_bindController(eg::BlankController* ncontroller = nullptr) override;
		virtual void base_unbindController(eg::BlankController* ncontroller = nullptr) override;
	};
}