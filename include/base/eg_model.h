#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "eg_declaration.h"
#include "eg_util.h"
#include "eg_type.h"
#include "eg_base.h"

namespace eg {
	class Model : public eg::Base {
	public:
		static std::string const _egNAME_OBJECT_seg_;
		Model();
	protected:
		virtual void base_bindController(eg::BlankController* ncontroller = nullptr) override;
		virtual void base_unbindController(eg::BlankController* ncontroller = nullptr) override;
	};
}