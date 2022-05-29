//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include <stdexcept>
#include "Util.h"

namespace cookie {

	void throwAPIUnsupported() {
		throw std::invalid_argument("Selected Rendering API isn't supported");
	}
}
