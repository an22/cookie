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
			const GLubyte* string;
			while (glErr != GL_NO_ERROR) {
				string = gluErrorString(glErr);
				LOG_E("%s", string);
				glErr = glGetError();
			}
#endif
		}

	};
}

#endif
#endif /* GLErrorHandler_hpp */
