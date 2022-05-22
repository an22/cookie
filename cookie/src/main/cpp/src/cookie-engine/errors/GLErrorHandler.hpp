//
//  GLErrorHandler.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 21.06.2021.
//

#ifndef GLErrorHandler_hpp
#define GLErrorHandler_hpp

#include "EGL/egl.h"
#include "GLES3/gl32.h"
#include "Macro.h"

namespace cookie {

	class GLErrorHandler {

	public :
		GLErrorHandler() = delete;
		~GLErrorHandler() = delete;
		static inline void printShaderLog(uint32_t shader);
		static inline void printProgramLog(int32_t prog);

		static inline void checkOpenGLError() {
#ifndef NDEBUG
			GLenum glErr = eglGetError();
			while (glErr != EGL_SUCCESS) {
				LOG_E("%d", glErr);
				glErr = eglGetError();
			}
#endif
		}

	};
}

#endif /* GLErrorHandler_hpp */
