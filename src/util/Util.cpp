//
// Created by Antiufieiev Michael on 07.08.2021.
//
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Cookie.hpp"
#include "Util.h"
#include "OpenGLPlatformSpecificData.h"

namespace cookie {

	void throwAPIUnsupported() {
		throw std::invalid_argument("Selected Rendering API isn't supported");
	}
}

