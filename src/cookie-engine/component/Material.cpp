//
// Created by Antiufieiev Michael on 12.08.2021.
//

#include "Material.h"

cookie::Material::Material(std::unique_ptr<Shader> &shader) : shader(std::move(shader)) {

}

void cookie::Material::onPreDraw() {
    shader->use();
}
