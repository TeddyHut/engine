#pragma once

#include <cstdint>
#include <vector>

#include "eg_declaration.h"
#include "eg_glbRtrn.h"
#include "eg_util.h"
#include "eg_dataReference.h" 
#include "eg_base.h"

namespace eg {
	class Input : public eg::Base {
	public:
		Input();
	protected:
		virtual void base_bindController();
		virtual void base_unbindController();
	};
}