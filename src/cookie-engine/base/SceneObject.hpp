//
//  SceneObject_hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <DrawUtils.h>
#include <Time.hpp>
#include "Component.hpp"

namespace cookie {

	class SceneObject {
		typedef std::vector<std::shared_ptr<SceneObject>> PtrSceneObjVector;
		typedef std::unordered_map<std::type_index, std::shared_ptr<Component>> ComponentMap;
	private:
		static int objCount;
	protected:
		bool is_static = false;
		glm::vec3 position{};
		glm::mat4 modelMat{};
		ComponentMap components;
		PtrSceneObjVector children;
	public:
		std::string name;

		explicit SceneObject(glm::vec3 pos);
		SceneObject(const std::string &path, glm::vec3 pos);
		SceneObject();
		SceneObject(const std::string &path, float x, float y, float z);
		virtual ~SceneObject();

		const glm::mat4 &getModelMat();

		[[nodiscard]] bool isStatic() const;

		virtual void transform(const glm::mat4 &transformation);
		virtual void setStatic(bool isStatic);
		virtual void setPosition(const glm::vec3 &position);
		virtual void setPosition(float x, float y, float z);

		virtual void draw(const DrawUtils &utils, const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix);

		virtual void addChild(const std::shared_ptr<SceneObject> &child);
		virtual std::shared_ptr<SceneObject> getChildAt(unsigned int position);
		virtual void removeChild(const std::shared_ptr<SceneObject> &child);
		PtrSceneObjVector::iterator childrenBegin() noexcept;
		PtrSceneObjVector::iterator childrenEnd() noexcept;


		//Templates
		template<class ComponentType>
		void addComponent(std::shared_ptr<ComponentType> component) {
			static_assert(std::is_base_of<Component, ComponentType>::value,
						  "type parameter of this class must derive from Component class");
			components[typeid(ComponentType)] = std::shared_ptr(component);
		}

		template<class ComponentType>
		ComponentType &removeComponent() {
			auto component = std::move(components[typeid(ComponentType)]);
			components.erase(typeid(ComponentType));
			return dynamic_cast<ComponentType>(component);
		}

		template<class ComponentType>
		std::shared_ptr<ComponentType> getComponent() {
			auto item = components.find(typeid(ComponentType));
			if (item != components.end()) {
				return std::dynamic_pointer_cast<ComponentType>(item->second);
			}
			return nullptr;
		}
	};
}


#endif /* SceneObject_hpp */
