#pragma once

#include <cstdint>
#include <vector>

#include "eg_base.h"

namespace eg {
	class View : public eg::Base {
	public:
		View();
	protected:
		virtual void base_bindController();
		virtual void base_unbindController();
	};
}