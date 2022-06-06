//
// Created by Antiufieiev Michael on 18.08.2021.
//
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define TINYGLTF_USE_CPP14

#ifdef __ANDROID__

#include "AndroidFileManager.hpp"

#define TINYGLTF_ANDROID_LOAD_FROM_ASSETS

#endif

#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include "Utils.hpp"
#include "Macro.h"
#include "CookieFactory.hpp"
#include "MeshComponent.hpp"
#include "TextureProcessor.hpp"
#include "AssetImporter.hpp"
#include "SceneObject.hpp"
#include "Transformation.hpp"
#include "MeshStruct.h"
#include "Material.h"
#include "Texture.hpp"
#include "Bounds.hpp"

namespace cookie {

	inline void fetchMaterials(
			const tinygltf::Model &model,
			std::vector<std::shared_ptr<cookie::Material>> &outMaterials
	) {
		for (auto &material: model.materials) {
			std::vector<cookie::Texture> textures;

			outMaterials.emplace_back(
					std::make_shared<cookie::Material>(
							material.name,
							glm::make_vec4(material.pbrMetallicRoughness.baseColorFactor.data()),
							glm::vec4(0),
							static_cast<float>(material.pbrMetallicRoughness.roughnessFactor),
							static_cast<float>(material.pbrMetallicRoughness.metallicFactor),
							0.5f,
							1.0f,
							material.doubleSided,
							textures
					)
			);
		}
		LOG_I("Imported materials count: %zu", outMaterials.size());
	}

	inline void fetchMatrix(cookie::SceneObject &obj, const tinygltf::Node &node) {
		if (!node.matrix.empty()) {
			LOG_I("Importing matrix");
			auto mat = glm::make_mat4(node.matrix.data());
			obj.getTransformation()->setModelMatrix(mat);
		} else {
			glm::vec3 translation(0.0f);
			auto rotation = glm::identity<glm::quat>();
			glm::vec3 scale(1.0f);
			if (node.translation.size() == 3) {
				translation = glm::make_vec3(node.translation.data());
			}
			if (node.rotation.size() == 4) {
				rotation = glm::quat(
						static_cast<float>(node.rotation[3]),
						static_cast<float>(node.rotation[0]),
						static_cast<float>(node.rotation[1]),
						static_cast<float>(node.rotation[2])
				);
			}
			if (node.scale.size() == 3) {
				scale = glm::make_vec3(node.scale.data());
			}
			obj.getTransformation()->transform(translation, rotation, scale);
		}
	}

	inline std::unique_ptr<intArrayBase> defineIndicesArray(
			const tinygltf::Model &model,
			const tinygltf::Primitive &meshPrimitive
	) {
		const auto &indicesAccessor = model.accessors[meshPrimitive.indices];
		const auto &bufferView = model.bufferViews[indicesAccessor.bufferView];
		const auto &buffer = model.buffers[bufferView.buffer];
		const auto dataAddress = buffer.data
										 .data() +
								 bufferView.byteOffset +
								 indicesAccessor.byteOffset;
		const auto byteStride = indicesAccessor.ByteStride(bufferView);
		const auto count = indicesAccessor.count;

		// Allocate the index array in the pointer-to-base declared in the parent scope
		// This permit to get a type agnostic way of reading the index buffer
		switch (indicesAccessor.componentType) {
			case TINYGLTF_COMPONENT_TYPE_INT:
				return std::make_unique<intArray<int32_t>>(
						arrayAdapter<int32_t>(dataAddress, count, byteStride)
				);
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
				return std::make_unique<intArray<uint32_t>>(
						arrayAdapter<uint32_t>(dataAddress, count, byteStride)
				);
			case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
				return std::make_unique<intArray<uint16_t>>(
						arrayAdapter<uint16_t>(dataAddress, count, byteStride)
				);
			case TINYGLTF_COMPONENT_TYPE_SHORT:
				return std::make_unique<intArray<int16_t>>(
						arrayAdapter<int16_t>(dataAddress, count, byteStride)
				);
			default:
				break;
		}
		throw std::runtime_error(
				"Unsupported GLTF component type, expected: TINYGLTF_COMPONENT_TYPE_INT, "
				"TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, "
				"TINYGLTF_COMPONENT_TYPE_SHORT"
		);
	}

	inline void fetchIndices(
			const tinygltf::Model &model,
			const tinygltf::Primitive &meshPrimitive,
			std::vector<uint32_t> &outIndices
	) {
		auto indices = defineIndicesArray(model, meshPrimitive);
		for (size_t i = 0; i < indices->size(); ++i) {
			outIndices.emplace_back((*indices)[i]);
		}
		LOG_I("Indices count %zu", indices->size());
	}

	inline void fetchTexCoords(
			const tinygltf::Accessor &attribAccessor,
			const unsigned char *dataPtr,
			size_t count,
			const int byteStride,
			std::vector<glm::vec2> &texCoords
	) {

		LOG_I("Texture coordinates type: %d", attribAccessor.type);

		switch (attribAccessor.type) {
			case TINYGLTF_TYPE_VEC2: {
				LOG_I("Texture component type: %d", attribAccessor.componentType);
				switch (attribAccessor.componentType) {
					case TINYGLTF_COMPONENT_TYPE_FLOAT: {
						v2fArray uvs(arrayAdapter<v2f>(dataPtr, count, byteStride));

						for (size_t i = 0; i < count; i++) {
							texCoords.emplace_back(uvs[i]);
						}
						break;
					}
					case TINYGLTF_COMPONENT_TYPE_DOUBLE: {
						v2dArray uvs(arrayAdapter<v2d>(dataPtr, count, byteStride));

						for (size_t i = 0; i < count; i++) {
							texCoords.emplace_back(uvs[i]);
						}
						break;
					}
					default:
						throw std::runtime_error("Unrecognized vector type for UV");
				}
			}
				break;
			default:
				throw std::runtime_error("Unrecognized component type for UV");
		}
	}

	inline void fetchNormals(
			const tinygltf::Accessor &attribAccessor,
			const unsigned char *dataPtr,
			size_t count,
			const int byteStride,
			std::vector<glm::vec3> &outNormals
	) {

		LOG_I("Normal type: %d", attribAccessor.type);

		switch (attribAccessor.type) {
			case TINYGLTF_TYPE_VEC3: {
				LOG_I("Normal component type: %d", attribAccessor.componentType);
				switch (attribAccessor.componentType) {
					case TINYGLTF_COMPONENT_TYPE_FLOAT: {
						v3fArray _normals(arrayAdapter<v3f>(dataPtr, count, byteStride));

						for (size_t i = 0; i < count; i++) {
							v3f normal = _normals[i];
							outNormals.emplace_back(normal);
						}
						break;
					}
					case TINYGLTF_COMPONENT_TYPE_DOUBLE: {
						v3dArray _normals(arrayAdapter<v3d>(dataPtr, count, byteStride));

						for (size_t i = 0; i < count; i++) {
							v3f normal = _normals[i];
							outNormals.emplace_back(normal);
						}
						break;
					}
					default:
						throw std::runtime_error("Unrecognized component type for normal");
				}
				break;
			}
			default:
				throw std::runtime_error("Unrecognized vector type for normal");
		}
	}

	inline void fetchPositions(
			const tinygltf::Accessor &attribAccessor,
			const unsigned char *dataPtr,
			size_t count,
			const int byteStride,
			std::vector<Vertex> &vertices
	) {
		LOG_I("Component type is : %d", attribAccessor.componentType);
		switch (attribAccessor.componentType) {
			case TINYGLTF_COMPONENT_TYPE_FLOAT: {
				// 3D vector of float
				v3fArray positions(arrayAdapter<v3f>(dataPtr, count, byteStride));

				for (size_t pos = 0; pos < positions.size(); pos++) {
					Vertex vertex{};
					vertex.position = positions[pos];
					vertices.emplace_back(std::move(vertex));
				}
				break;
			}
			case TINYGLTF_COMPONENT_TYPE_DOUBLE: {
				// 3D vector of double
				v3dArray positions(arrayAdapter<v3d>(dataPtr, count, byteStride));
				for (size_t pos = 0; pos < positions.size(); pos++) {
					Vertex vertex{};
					vertex.position = positions[pos];
					vertices.emplace_back(std::move(vertex));
				}
				break;
			}
			default:
				break;
		}
		LOG_I("Vertices count: %zu", vertices.size());
	}

	inline void fetchPrimitiveTriangles(
			const tinygltf::Model &model,
			const tinygltf::Primitive &meshPrimitive,
			std::vector<uint32_t> &indices,
			std::vector<Vertex> &outVertices,
			std::vector<glm::vec2> &outTexCoords,
			std::vector<glm::vec3> &outNormals
	) {

		for (const auto &attribute: meshPrimitive.attributes) {
			const auto &attribAccessor = model.accessors[attribute.second];
			const auto &bufferView = model.bufferViews[attribAccessor.bufferView];
			const auto &buffer = model.buffers[bufferView.buffer];
			const auto dataPtr = buffer.data.data() +
								 bufferView.byteOffset +
								 attribAccessor.byteOffset;
			const auto byteStride = attribAccessor.ByteStride(bufferView);
			const auto count = attribAccessor.count;

			LOG_I("Current attribute has count %zu and stride %d bytes", count, byteStride);
			LOG_I("Attribute : %s", attribute.first.c_str());
			if (attribute.first == "POSITION") {
				outVertices.reserve(count);
				fetchPositions(attribAccessor, dataPtr, count, byteStride, outVertices);
			}
			if (attribute.first == "NORMAL") {
				outNormals.reserve(count);
				fetchNormals(attribAccessor, dataPtr, count, byteStride, outNormals);
			}

			if (attribute.first == "TEXCOORD_0") {
				outTexCoords.reserve(count);
				fetchTexCoords(attribAccessor, dataPtr, count, byteStride, outTexCoords);
			}
		}
	}

	inline void parseSceneRecursively(
			cookie::SceneObject &obj,
			const std::vector<std::shared_ptr<cookie::Material>> &materials,
			const tinygltf::Model &model,
			size_t nodeIndex
	) {
		const auto &node = model.nodes[nodeIndex];
		obj.setName(node.name);
		LOG_I("Importing node %s", obj.getName().c_str());
		fetchMatrix(obj, node);
		if (node.mesh != -1) {
			auto &mesh = model.meshes[node.mesh];
			std::vector<cookie::Vertex> outVertices;
			std::vector<uint32_t> outIndices;
			std::vector<glm::vec2> outTexCoords;
			std::vector<glm::vec3> outNormals;
			std::shared_ptr<cookie::Material> material;
			std::unique_ptr<cookie::MeshData> loadedMesh;
			Bounds bounds{};

			// For each primitive
			for (const auto &meshPrimitive: mesh.primitives) {

				fetchIndices(model, meshPrimitive, outIndices);
				LOG_I("Primitive mode: %s", std::to_string(meshPrimitive.mode).c_str());
				switch (meshPrimitive.mode) {
					case TINYGLTF_MODE_TRIANGLES: { // this is the simplest case to handle
						fetchPrimitiveTriangles(
								model,
								meshPrimitive,
								outIndices,
								outVertices,
								outTexCoords,
								outNormals
						);
						size_t i = 0;
						bool hasTexCoords = outTexCoords.size() == outVertices.size();
						bool hasNormals = outNormals.size() == outVertices.size();
						for (auto &vertex: outVertices) {
							if (bounds.min.x > vertex.position.x) bounds.min.x = vertex.position.x;
							if (bounds.min.z > vertex.position.z) bounds.min.z = vertex.position.z;
							if (bounds.min.y > vertex.position.y) bounds.min.y = vertex.position.y;
							if (bounds.max.x < vertex.position.x) bounds.max.x = vertex.position.x;
							if (bounds.max.z < vertex.position.z) bounds.max.z = vertex.position.z;
							if (bounds.max.y < vertex.position.y) bounds.max.y = vertex.position.y;
							if (hasTexCoords) {
								vertex.texCoords = outTexCoords[i];
							}
							if (hasNormals) {
								vertex.normal = outNormals[i];
							}
							i++;
						}
						break;
					}
					default:
						continue;
				}
			}

			material = materials[0];
			// Create a mesh object
			loadedMesh = std::make_unique<cookie::MeshData>(
					mesh.name,
					outVertices,
					outIndices,
					material
			);
			bounds.calculatePoints();
			obj.addComponent(std::make_shared<cookie::MeshComponent>(std::move(loadedMesh), bounds));

			// TODO handle textures
		}
		for (size_t child: node.children) {
			auto childObj = std::make_shared<cookie::SceneObject>();
			parseSceneRecursively(*childObj, materials, model, child);
			obj.addChild(childObj);
		}
	}

	inline void parseScene(cookie::SceneObject &root, const tinygltf::Model &model) {

		std::vector<std::shared_ptr<cookie::Material>> materials;
		fetchMaterials(model, materials);

		auto &scene = model.scenes[model.defaultScene];
		LOG_I("Importing scene %s", scene.name.c_str());
		parseSceneRecursively(root, materials, model, 0);

// TODO Iterate through all texture declaration in glTF file
//		for (const auto &gltfTexture: model.textures) {
//			std::cout << "Found texture!";
//			Texture loadedTexture;
//			const auto &image = model.images[gltfTexture.source];
//			loadedTexture.components = image.component;
//			loadedTexture.width = image.width;
//			loadedTexture.height = image.height;
//			const auto size = image.component * image.width * image.height * sizeof(unsigned char);
//			loadedTexture.image = new unsigned char[size];
//			memcpy(loadedTexture.image, image.image.data(), size);
//			textures->emplace_back(loadedTexture);
//		}
	}

	inline tinygltf::Model *readModelFromFile(const std::string &path) {
		auto *model = new tinygltf::Model();
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		if (Utils::endsWith(path, ".glb")) {
			loader.LoadBinaryFromFile(model, &err, &warn, path);
		} else {
			loader.LoadASCIIFromFile(model, &err, &warn, path);
		}
		if (!warn.empty()) {
			LOG_W("%s", warn.c_str());
		}
		if (!err.empty()) {
			throw std::runtime_error(err.c_str());
		}
		return model;
	}

	void AssetImporter::importMesh(SceneObject &root, const std::string &path) {
#ifdef __ANDROID__
		if (!tinygltf::asset_manager) {
			tinygltf::asset_manager = dynamic_cast<const cookie::AndroidFileManager &>(CookieFactory::getManager())
					.getManager();
		}
#endif
		std::unique_ptr<tinygltf::Model> scene(readModelFromFile(path));
		LOG_I("Importing model at: %s", path.c_str());
		parseScene(root, *scene);
	}
}
