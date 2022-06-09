//
//  BufferStorage.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 01.07.2021.
//

#ifndef BufferStorage_hpp
#define BufferStorage_hpp

#include <memory>
#include <vector>
#include "asset/MeshStruct.h"

namespace cookie {
	class BufferStorage {

	public:
		explicit BufferStorage();
		virtual ~BufferStorage();

		virtual void bind() const = 0;
        virtual void unbind() const =  0;
		virtual void saveToBuffer(
				const MeshData &meshData,
				const std::vector<glm::mat4> &matrices
		) const = 0;
	};
}

#endif /* BufferStorage_hpp */