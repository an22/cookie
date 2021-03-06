//
//  OpenGLBufferStorage.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLBufferStorage_hpp
#define OpenGLBufferStorage_hpp

#if COOKIE_OPENGL

#include "BufferStorage.hpp"
#include "GL/glew.h"

namespace cookie {

	struct Vertex;
	struct MeshData;
	struct PointsData;

	class OpenGLBufferStorage : public cookie::BufferStorage {
	private:
		GLuint vao{};
		GLuint uboMaterial{};
		GLuint vboVertex{};
		GLuint vboIndex{};
		GLuint sboMatrices{};
		void setupVertexElementBuffer(const cookie::MeshData &meshData) const;
		void setupPointElementBuffer(const cookie::PointsData &pointsData) const;
		void setupMatricesBuffer(const std::vector<glm::mat4> &matrices) const;
		void setupMaterialBuffer(const cookie::MeshData &meshData) const;
		void fillElementsBuffer(const std::vector<uint32_t> &indices) const;
		void fillVertexBuffer(const std::vector<Vertex> &meshData) const;
		void fillPointsBuffer(const std::vector<glm::vec4> &vertices) const;
		static void setVertexAttributePointers();
		static void setPointAttributePointers();
	public:
		explicit OpenGLBufferStorage();
		void bind() const override;
		void unbind() const override;
		void saveToBuffer(
				const cookie::MeshData &meshData,
				const std::vector<glm::mat4> &matrices
		) const override;
		void saveToBuffer(
				const cookie::PointsData &pointsData,
				const std::vector<glm::mat4> &matrices
		) const override;
		~OpenGLBufferStorage() override;
	};
}

#endif
#endif /* OpenGLBufferStorage_hpp */
