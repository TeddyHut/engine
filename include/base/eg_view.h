#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "eg_base.h"

namespace eg {
	class View : public eg::Base {
	public:
		static std::string const _egNAME_OBJECT_seg_;
		View();
	protected:
		virtual void base_bindController(eg::BlankController* ncontroller = nullptr) override;
		virtual void base_unbindController(eg::BlankController* ncontroller = nullptr) override;
	};
}