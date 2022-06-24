//
//  Component.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 03.08.2021.
//

#ifndef Component_hpp
#define Component_hpp

#include <memory>

namespace cookie {
	class SceneObject;

	class Component {
	protected:
		std::weak_ptr<SceneObject> owner;
	public:
		explicit Component(const std::shared_ptr<SceneObject> &objPtr);
		virtual ~Component() = default;
	};
}

#endif /* Component_hpp */
