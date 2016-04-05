#pragma once

#include <cstdint>
#include <vector>

#include "eg_declaration.h"
#include "eg_util.h"
#include "eg_type.h"
#include "eg_base.h"

namespace eg {
	class Model : public eg::Base {
	public:
		Model();
	protected:
		virtual void base_bindController();
		virtual void base_unbindController();
	};
}