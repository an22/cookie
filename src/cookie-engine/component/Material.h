//
// Created by Antiufieiev Michael on 12.08.2021.
//

#ifndef COOKIE_ENGINE_MATERIAL_H
#define COOKIE_ENGINE_MATERIAL_H

#include <Shader.hpp>
#include <memory>

namespace cookie {
    class Material {
    private:
        std::unique_ptr<Shader> shader;
    public:
        explicit Material(std::unique_ptr<Shader>& shader);
        virtual ~Material() = default;
        void onPreDraw();
    };
}

#endif //COOKIE_ENGINE_MATERIAL_H
