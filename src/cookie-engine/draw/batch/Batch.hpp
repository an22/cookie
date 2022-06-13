//
// Created by Antiufieiev Michael on 10.10.2021.
//

#ifndef COOKIE_ENGINE_BATCH_HPP
#define COOKIE_ENGINE_BATCH_HPP

#include <memory>
#include "BatchConfig.hpp"
#include "Renderable.hpp"

namespace cookie {

	struct Vertex;

	class SceneObject;

	class Material;

	class DrawUtils;

	class BufferStorage;

	class Batch : public Renderable {
	private:
		std::vector<std::shared_ptr<SceneObject>> sceneObjects;
		std::unique_ptr<BufferStorage> bufferStorage;
		std::shared_ptr<Material> material;
		BatchConfig config;

		bool isStatic = true;

		void combineMeshData(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, std::vector<glm::mat4> &matrices);
		void calculateVertexAndIndexSize(uint32_t &vertexCount, uint32_t &indexCount);
		void initBatchConfig();
	protected:
		void draw(const DrawUtils &drawUtils) override;
	public:

		explicit Batch(const std::shared_ptr<Material> &material);
		~Batch() override;

		void addObject(std::shared_ptr<SceneObject> sceneObject);
		void removeObject(const std::shared_ptr<SceneObject> &sceneObject);
		void saveToGPU() override;
	};
}


#endif //COOKIE_ENGINE_BATCH_HPP
