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

        template<class ComponentType>
        void addComponent(std::unique_ptr<ComponentType> component);

        template<class ComponentType>
        ComponentType &removeComponent();

        template<class ComponentType>
        ComponentType &getComponent();

    };
}


#endif /* SceneObject_hpp */
