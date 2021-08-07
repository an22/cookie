//
//  Shader.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 28.07.2021.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace cookie {

    class Shader {
    public:

        virtual ~Shader() = default;
        // use/activate the shader
        virtual void use() = 0;
        // utility uniform functions
        virtual void setBool(const std::string &name, bool value) const = 0;
        virtual void setInt(const std::string &name, int32_t value) const = 0;
        virtual void setFloat(const std::string &name, float value) const = 0;
        //TODO add more utility functions
    };
}
#endif /* Shader_hpp */
