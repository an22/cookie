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
#include <atomic>
#include <memory>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <glm/detail/type_quat.hpp>

namespace cookie {

	class DrawUtils;
	class SceneObject;
	class Transformation;
	class Component;

	class SceneObject {
		typedef std::vector<std::shared_ptr<SceneObject>> PtrSceneObjVector;
		typedef std::unordered_map<std::type_index, std::shared_ptr<Component>> ComponentMap;
	protected:
		static std::atomic_uint32_t current_id;
		uint32_t id;
		std::string name;
		bool is_static;

		ComponentMap components;
		PtrSceneObjVector children;

		std::shared_ptr<Transformation> transformation;
	public:

		SceneObject();
		virtual ~SceneObject();
		static std::shared_ptr<SceneObject> fromPath(const std::string& path);

		[[nodiscard]] const std::shared_ptr<Transformation> &getTransformation() const;
		[[nodiscard]] const std::string &getName() const;
		[[nodiscard]] uint32_t getId() const;
		[[nodiscard]] const glm::mat4 &getModelMat() const;
		[[nodiscard]] bool isStatic() const;

		void setStatic(bool isStatic);
		void setName(const std::string &name);

		void addChild(const std::shared_ptr<SceneObject> &child);
		std::shared_ptr<SceneObject> getChildAt(unsigned int position);
		void removeChild(const std::shared_ptr<SceneObject> &child);

		PtrSceneObjVector::iterator childrenBegin() noexcept;
		PtrSceneObjVector::iterator childrenEnd() noexcept;

		//Lifecycle
		virtual void onCreate();
		virtual void onUpdate();//TODO timestamp
		virtual void onPostUpdate();


		//Templates
		template<class ComponentType>
		void addComponent(std::shared_ptr<ComponentType> component) {
			static_assert(
					std::is_base_of<Component, ComponentType>::value,
					"type parameter of this class must derive from Component class"
			);
			components[typeid(ComponentType)] = std::move(component);
		}

		template<class ComponentType>
		ComponentType &removeComponent() {
			static_assert(
					std::is_base_of<Component, ComponentType>::value,
					"type parameter of this class must derive from Component class"
			);
			auto component = std::move(components[typeid(ComponentType)]);
			components.erase(typeid(ComponentType));
			return dynamic_cast<ComponentType>(component);
		}

		template<class ComponentType>
		std::shared_ptr<ComponentType> getComponent() {
			static_assert(
					std::is_base_of<Component, ComponentType>::value,
					"type parameter of this class must derive from Component class"
			);
			auto item = components.find(typeid(ComponentType));
			if (item != components.end()) {
				return std::dynamic_pointer_cast<ComponentType>(item->second);
			}
			return nullptr;
		}
	};
}

#endif /* SceneObject_hpp */
