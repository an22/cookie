//
// Created by Michael on 6/13/2022.
//

#include "Renderable.hpp"

#include <utility>
#include "BufferStorage.hpp"
#include "CookieFactory.hpp"
#include "Material.h"

namespace cookie {

	Renderable::Renderable(std::shared_ptr<Material> material)
			: bufferStorage(CookieFactory::provideBufferStorage()),
			  material(std::move(material)) {
	}

	Renderable::~Renderable() = default;
}
