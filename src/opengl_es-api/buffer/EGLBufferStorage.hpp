//
//  OpenGLBufferStorage.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef EGLBufferStorage_hpp
#define EGLBufferStorage_hpp

#if COOKIE_EGL

#include "BufferStorage.hpp"
#include "PlatformSpecificBufferData.h"
#include "OpenGLPSBufferData.h"

namespace cookie {

	class EGLBufferStorage : public cookie::BufferStorage {
	private:
		GLuint vao{};
		GLuint uboMaterial{};
		GLuint vboVertex{};
		GLuint vboIndex{};
		GLuint sboMatrices{};
		GLuint texMatrices{};
		std::unique_ptr<OpenGLPSBufferData> bufferData;
		void setupVertexElementBuffer(const cookie::MeshData &meshData) const;
		void setupMatricesBuffer(const std::vector<glm::mat4> &matrices) const;
		void setupMaterialBuffer(const cookie::MeshData &meshData) const;

	public:
		explicit EGLBufferStorage();
		void bind() const override;
		void unbind() const override;
		void saveToBuffer(
				const cookie::MeshData &meshData,
				const std::vector<glm::mat4> &matrices,
				std::unique_ptr<cookie::PlatformSpecificBufferData> data
		) const override;
		~EGLBufferStorage() override;
	};
}

#endif
#endif /* EGLBufferStorage_hpp */
