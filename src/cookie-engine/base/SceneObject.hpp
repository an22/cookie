//
//  SceneObject_hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <glm/glm.hpp>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <DrawUtils.h>
#include "Component.hpp"

namespace cookie {
    class SceneObject {
    private:
        bool is_static = true;

        std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

        glm::vec3 position{};
        glm::mat4 modelMat{};
    public:

        explicit SceneObject(glm::vec3 pos);
        SceneObject();
        SceneObject(float x, float y, float z);
        virtual ~SceneObject() = 0;

        const glm::mat4 &getModelMat();

        [[nodiscard]] bool isStatic() const;

        virtual void transform(const glm::mat4 &transformation);
        virtual void setStatic(bool isStatic);
        virtual void setPosition(const glm::vec3 &position);
        virtual void setPosition(float x, float y, float z);

        virtual void draw(DrawUtils &utils, glm::mat4 &viewMatrix, glm::mat4 &projMatrix) = 0;

        template<class ComponentType>
        void addComponent(std::unique_ptr<ComponentType> component) {
            static_assert(std::is_base_of<Component, ComponentType>::value,
                          "type parameter of this class must derive from Component class");
            components[typeid(ComponentType)] = std::move(component);
        }

        template<class ComponentType>
        ComponentType &removeComponent() {
            auto component = std::move(components[typeid(ComponentType)]);
            components.erase(typeid(ComponentType));
            return dynamic_cast<ComponentType>(component);
        }

        template<class ComponentType>
        ComponentType &getComponent() {
            return dynamic_cast<ComponentType&>(*components[typeid(ComponentType)]);
        }

    };
}


#endif /* SceneObject_hpp */
