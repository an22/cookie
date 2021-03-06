//
// Created by Antiufieiev Michael on 18.08.2021.
//

#ifndef COOKIE_ENGINE_ASSETIMPORTER_HPP
#define COOKIE_ENGINE_ASSETIMPORTER_HPP

#include <string>
#include <vector>
#include "tinygltf/tiny_gltf.h"
#include <stdexcept>

namespace cookie {

	/// Adapts an array of bytes to an array of T. Will advace of byte_stride each
	/// elements.
	template<typename T>
	struct arrayAdapter {
		/// Pointer to the bytes
		const unsigned char *dataPtr;
		/// Number of elements in the array
		const size_t elemCount;
		/// Stride in bytes between two elements
		const size_t stride;

		/// Construct an array adapter.
		/// \param ptr Pointer to the start of the data, with offset applied
		/// \param count Number of elements in the array
		/// \param byte_stride Stride betweens elements in the array
		arrayAdapter(const unsigned char *ptr, size_t count, size_t byte_stride)
				: dataPtr(ptr), elemCount(count), stride(byte_stride) {
		}

		/// Returns a *copy* of a single element. Can't be used to modify it.
		T operator[](size_t pos) const {
			if (pos >= elemCount) {
				throw std::out_of_range(
						"Tried to access beyond the last element of an array adapter with "
						"count " +
						std::to_string(elemCount) + " while getting elemnet number " +
						std::to_string(pos));
			}
			return *(reinterpret_cast<const T *>(dataPtr + pos * stride));
		}
	};

	/// Interface of any adapted array that returns ingeger data
	struct intArrayBase {
		virtual ~intArrayBase() = default;
		virtual unsigned int operator[](size_t) const = 0;
		[[nodiscard]] virtual size_t size() const = 0;
	};

/// Interface of any adapted array that returns float data
	struct floatArrayBase {
		virtual ~floatArrayBase() = default;
		virtual float operator[](size_t) const = 0;
		[[nodiscard]] virtual size_t size() const = 0;
	};

/// An array that loads interger types, returns them as int
	template<class T>
	struct intArray : public intArrayBase {
		arrayAdapter<T> adapter;

		explicit intArray(const arrayAdapter<T> &a) : adapter(a) {
		}

		unsigned int operator[](size_t position) const override {
			return static_cast<unsigned int>(adapter[position]);
		}

		[[nodiscard]] size_t size() const override {
			return adapter.elemCount;
		}
	};

	template<class T>
	struct floatArray : public floatArrayBase {
		arrayAdapter<T> adapter;

		explicit floatArray(const arrayAdapter<T> &a) : adapter(a) {
		}

		float operator[](size_t position) const override {
			return static_cast<float>(adapter[position]);
		}

		[[nodiscard]] size_t size() const override {
			return adapter.elemCount;
		}
	};

	using v2f = glm::vec2;
	using v3f = glm::vec3;
	using v4f = glm::vec4;
	using v2d = glm::dvec2;
	using v3d = glm::dvec3;
	using v4d = glm::dvec4;

	struct v2fArray {
		arrayAdapter<v2f> adapter;

		explicit v2fArray(const arrayAdapter<v2f> &a) : adapter(a) {
		}

		v2f operator[](size_t position) const {
			return adapter[position];
		}

		[[nodiscard]] size_t size() const {
			return adapter.elemCount;
		}
	};

	struct v3fArray {
		arrayAdapter<v3f> adapter;

		explicit v3fArray(const arrayAdapter<v3f> &a) : adapter(a) {
		}

		v3f operator[](size_t position) const {
			return adapter[position];
		}

		[[nodiscard]] size_t size() const {
			return adapter.elemCount;
		}
	};

	struct v4fArray {
		arrayAdapter<v4f> adapter;

		explicit v4fArray(const arrayAdapter<v4f> &a) : adapter(a) {
		}

		v4f operator[](size_t position) const {
			return adapter[position];
		}

		[[nodiscard]] size_t size() const {
			return adapter.elemCount;
		}
	};

	struct v2dArray {
		arrayAdapter<v2d> adapter;

		explicit v2dArray(const arrayAdapter<v2d> &a) : adapter(a) {
		}

		v2d operator[](size_t position) const {
			return adapter[position];
		}

		[[nodiscard]] size_t size() const {
			return adapter.elemCount;
		}
	};

	struct v3dArray {
		arrayAdapter<v3d> adapter;

		explicit v3dArray(const arrayAdapter<v3d> &a) : adapter(a) {
		}

		v3d operator[](size_t position) const {
			return adapter[position];
		}

		[[nodiscard]] size_t size() const {
			return adapter.elemCount;
		}
	};

	struct v4dArray {
		arrayAdapter<v4d> adapter;

		explicit v4dArray(const arrayAdapter<v4d> &a) : adapter(a) {
		}

		v4d operator[](size_t position) const {
			return adapter[position];
		}

		[[nodiscard]] size_t size() const {
			return adapter.elemCount;
		}
	};

	class SceneObject;

	class AssetImporter {
	public:
		static void importMesh(const std::shared_ptr<SceneObject> &root, const std::string &path);
	};
}

#endif //COOKIE_ENGINE_ASSETIMPORTER_HPP
