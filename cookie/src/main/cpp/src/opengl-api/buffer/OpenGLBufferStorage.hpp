//
//  OpenGLBufferStorage.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLBufferStorage_hpp
#define OpenGLBufferStorage_hpp

#include "BufferStorage.hpp"
#include "PlatformSpecificBufferData.h"
#include "OpenGLPSBufferData.h"

class OpenGLBufferStorage : public cookie::BufferStorage {
private:
	GLuint vao{};
	GLuint uboMaterial{};
	GLuint vboVertex{};
	GLuint vboIndex{};
	GLuint tboMatrices{};
	GLuint texMatrices{};

	std::unique_ptr<OpenGLPSBufferData> bufferData;

	void setupVertexElementBuffer(const cookie::MeshData &meshData) const;
	void setupMatricesBuffer(const std::vector<glm::mat4>& matrices) const;
	void setupMaterialBuffer(const cookie::MeshData &meshData) const;

public:
	explicit OpenGLBufferStorage();


	void bind() const override;
    void unbind() const override;
	void saveToBuffer(
			const cookie::MeshData &meshData,
			const std::vector<glm::mat4>& matrices,
			std::unique_ptr<cookie::PlatformSpecificBufferData> data
	) const override;

	~OpenGLBufferStorage() override;
};

#endif /* OpenGLBufferStorage_hpp */
