//
//  OpenGLTime.hpp
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef OpenGLTime_hpp
#define OpenGLTime_hpp

#include <stdio.h>
#include "Time.hpp"

class OpenGLTime : public cookie::Time {

public:
    virtual double getProgramTime() override;
    virtual double getFrameTime() override;

    ~OpenGLTime() override = default;
};

#endif /* OpenGLTime_hpp */