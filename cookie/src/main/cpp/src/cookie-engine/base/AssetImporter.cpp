//
// Created by Antiufieiev Michael on 18.08.2021.
//
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION

#ifdef __ANDROID__

#include "AndroidFileManager.hpp"

#define TINYGLTF_ANDROID_LOAD_FROM_ASSETS
#endif

#include "AssetImporter.hpp"
#include "CookieFactory.hpp"
#include "MeshStruct.h"
#include "SceneObject.hpp"
#include "Mesh.hpp"
#include <memory>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

using namespace tinygltf;

namespace cookie {

	void fetchMaterials(
			const Model &model,
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
	}

	void AssetImporter::parseSceneRecursively(
			std::shared_ptr<cookie::SceneObject> &obj,
			const std::vector<std::shared_ptr<cookie::Material>> &materials,
			const Model &model,
			size_t nodeIndex
	) {
		auto &node = model.nodes[nodeIndex];
		obj->name = node.name;
		if(!node.matrix.empty()) {
			obj->transform(glm::make_mat4(node.matrix.data()));
		}
		if (node.mesh != -1) {
			auto &mesh = model.meshes[node.mesh];
			std::vector<cookie::Vertex> outVertices;
			std::vector<uint32_t> outIndices;
			std::vector<glm::vec2> outTexCoords;
			std::vector<glm::vec3> outNormals;
			std::shared_ptr<cookie::Material> material;
			std::unique_ptr<cookie::MeshData> loadedMesh;

			// For each primitive
			for (const auto &meshPrimitive : mesh.primitives) {

				fetchIndices(model, meshPrimitive, outIndices);

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
						for (auto &vertex:outVertices) {
							vertex.texCoords = outTexCoords[i];
							vertex.normal = outNormals[i];
							i++;
						}
						material = materials[meshPrimitive.material];
						// Create a mesh object
						loadedMesh = std::make_unique<cookie::MeshData>(
								mesh.name,
								outVertices,
								outIndices,
								material
						);
						obj->addComponent(std::make_shared<cookie::Mesh>(std::move(loadedMesh)));
						break;
					}
					default:
						continue;
				}
			}

			// TODO bounding box
			// TODO handle textures
		}
		for (size_t child : node.children) {
			auto childObj = std::make_shared<cookie::SceneObject>();
			parseSceneRecursively(childObj,materials,model, child);
			obj->addChild(childObj);
		}
	}

	void AssetImporter::parseScene(cookie::SceneObject &root, const Model &model) {

		std::vector<std::shared_ptr<cookie::Material>> materials;
		fetchMaterials(model, materials);

		auto &scene = model.scenes[0];
		root.name = model.scenes[0].name;
		for (size_t nodeIndex:scene.nodes) {
			auto ptr = std::make_shared<cookie::SceneObject>();
			parseSceneRecursively(ptr, materials, model, nodeIndex);
			root.addChild(ptr);
		}

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

	void AssetImporter::fetchIndices(
			const Model &model,
			const Primitive &meshPrimitive,
			std::vector<uint32_t> &outIndices
	) {
		auto indices = defineIndicesArray(model, meshPrimitive);
		std::cout << "indices: ";
		for (size_t i = 0; i < indices->size(); ++i) {
			std::cout << (*indices)[i] << " ";
			outIndices.emplace_back((*indices)[i]);
		}
		std::cout << '\n';
	}

	void AssetImporter::fetchPrimitiveTriangles(
			const Model &model,
			const Primitive &meshPrimitive,
			std::vector<uint32_t> &indices,
			std::vector<Vertex> &outVertices,
			std::vector<glm::vec2> &outTexCoords,
			std::vector<glm::vec3> &outNormals
	) {
		std::cout << "TRIANGLES\n";

		for (const auto &attribute : meshPrimitive.attributes) {
			const auto &attribAccessor = model.accessors[attribute.second];
			const auto &bufferView = model.bufferViews[attribAccessor.bufferView];
			const auto &buffer = model.buffers[bufferView.buffer];
			const auto dataPtr = buffer.data
									   .data() +
								 bufferView.byteOffset +
								 attribAccessor.byteOffset;
			const auto byteStride = attribAccessor.ByteStride(bufferView);
			const auto count = attribAccessor.count;

			std::cout << "current attribute has count " << count << " and stride "
					  << byteStride << " bytes\n";

			std::cout << "attribute string is : " << attribute.first << '\n';
			if (attribute.first == "POSITION") {
				outVertices.reserve(count);
				fetchPositions(attribAccessor, dataPtr, count, byteStride, outVertices);
			}
			if (attribute.first == "NORMAL") {
				outNormals.reserve(count);
				fetchNormals(attribAccessor, dataPtr, count, byteStride, indices, outNormals);
			}

			if (attribute.first == "TEXCOORD_0") {
				outTexCoords.reserve(count);
				fetchTexCoords(attribAccessor, dataPtr, count, byteStride, indices, outTexCoords);
			}
		}
	}

	void AssetImporter::fetchTexCoords(
			const Accessor &attribAccessor,
			const unsigned char *dataPtr,
			size_t count,
			const int byteStride,
			std::vector<uint32_t> &indices,
			std::vector<glm::vec2> &texCoords
	) {
		std::cout << "Found texture coordinates\n";

		switch (attribAccessor.type) {
			case TINYGLTF_TYPE_VEC2: {
				std::cout << "TEXTCOORD is VEC2\n";
				switch (attribAccessor.componentType) {
					case TINYGLTF_COMPONENT_TYPE_FLOAT: {
						std::cout << "TEXTCOORD is FLOAT\n";
						v2fArray uvs(arrayAdapter<v2f>(dataPtr, count, byteStride));

						for (unsigned int f0 : indices) {
							texCoords.emplace_back(uvs[f0]);
						}
						break;
					}
					case TINYGLTF_COMPONENT_TYPE_DOUBLE: {
						std::cout << "TEXTCOORD is DOUBLE\n";
						v2dArray uvs(arrayAdapter<v2d>(dataPtr, count, byteStride));

						for (unsigned int f0 : indices) {
							texCoords.emplace_back(uvs[f0]);
						}
						break;
					}
					default:
						throw std::runtime_error("unrecognized vector type for UV");
				}
			}
				break;
			default:
				throw std::runtime_error("unreconized componant type for UV");
		}
	}

	void AssetImporter::fetchNormals(
			const Accessor &attribAccessor,
			const unsigned char *dataPtr,
			size_t count,
			const int byteStride,
			std::vector<uint32_t> &indices,
			std::vector<glm::vec3> &outNormals
	) {
		std::cout << "found normal attribute\n";

		switch (attribAccessor.type) {
			case TINYGLTF_TYPE_VEC3: {
				std::cout << "Normal is VEC3\n";
				switch (attribAccessor.componentType) {
					case TINYGLTF_COMPONENT_TYPE_FLOAT: {
						std::cout << "Normal is FLOAT\n";
						v3fArray _normals(arrayAdapter<v3f>(dataPtr, count, byteStride));

						for (size_t i = 0; i < count; i++) {
							v3f normal = _normals[i];
							outNormals.emplace_back(normal);
						}
						break;
					}
					case TINYGLTF_COMPONENT_TYPE_DOUBLE: {
						std::cout << "Normal is DOUBLE\n";
						v3dArray _normals(arrayAdapter<v3d>(dataPtr, count, byteStride));

						for (size_t i = 0; i < count; i++) {
							v3f normal = _normals[i];
							outNormals.emplace_back(normal);
						}
						break;
					}
					default:
						throw std::runtime_error("Unhandeled componant type for normal\n");
				}
				break;
			}
			default:
				throw std::runtime_error("Unhandeled vector type for normal\n");
		}
	}

	void AssetImporter::fetchPositions(
			const Accessor &attribAccessor,
			const unsigned char *dataPtr,
			size_t count,
			const int byteStride,
			std::vector<Vertex> &vertices
	) {
		std::cout << "found position attribute\n";

		switch (attribAccessor.componentType) {
			case TINYGLTF_COMPONENT_TYPE_FLOAT: {
				std::cout << "Type is FLOAT\n";
				// 3D vector of float
				v3fArray positions(arrayAdapter<v3f>(dataPtr, count, byteStride));

				std::cout << "positions's size : "
						  << positions.size()
						  << '\n';
				for (size_t pos = 0; pos < positions.size(); pos++) {
					Vertex vertex{};
					vertex.position = positions[pos];
					vertices.emplace_back(std::move(vertex));
				}
				break;
			}
			case TINYGLTF_COMPONENT_TYPE_DOUBLE: {
				std::cout << "Type is DOUBLE\n";
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
	}

	std::unique_ptr<intArrayBase> AssetImporter::defineIndicesArray(
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
				"Unsupported GLTF component type, expected: TINYGLTF_COMPONENT_TYPE_INT, TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT, TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, TINYGLTF_COMPONENT_TYPE_SHORT"
		);
	}

	void AssetImporter::importMesh(SceneObject &root, const std::string &path) {
#ifdef __ANDROID__
		tinygltf::asset_manager = dynamic_cast<const cookie::AndroidFileManager &>(CookieFactory::getManager())
				.getManager();
#endif
		std::unique_ptr<tinygltf::Model> scene(readModelFromFile(path));
		parseScene(root, *scene);
	}

	tinygltf::Model *AssetImporter::readModelFromFile(const std::string &path) {
		auto *model = new tinygltf::Model();
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;
		loader.LoadBinaryFromFile(model, &err, &warn, path);
		if (!warn.empty()) {
			printf("Warn: %s\n", warn.c_str());
		}

		if (!err.empty()) {
			printf("Err: %s\n", err.c_str());
		}
		SceneObject so;

		parseScene(so, *model);

		return model;
	}
}
