//
//  GLErrorHandler.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//

#ifndef GLErrorHandler_hpp
#define GLErrorHandler_hpp

#if COOKIE_OPENGL

#include "GL/glew.h"
#include "Macro.h"

namespace cookie {

	class GLErrorHandler {

	public :
		GLErrorHandler() = delete;
		~GLErrorHandler() = delete;
		static void printShaderLog(uint32_t shader);
		static void printProgramLog(int32_t prog);

		static inline void checkOpenGLError() {
#ifndef NDEBUG
			GLenum glErr = glGetError();
			while (glErr != GL_NO_ERROR) {
				LOG_E("%s", gluErrorString(glErr));
				glErr = glGetError();
			}
#endif
		}

	};
}

#endif
#endif /* GLErrorHandler_hpp */
