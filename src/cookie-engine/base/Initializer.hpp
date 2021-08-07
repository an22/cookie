//
//  Initializer.h
//  cookie-engine
//
//  Created by Antiufieiev Michael on 05.08.2021.
//

#ifndef Initializer_h
#define Initializer_h

namespace cookie {
class Initializer {
public:
	Initializer() {
	}
	virtual void initGraphicsAPIResources() const = 0;
	virtual void destroyGraphicsAPIResources() const = 0;
	
	virtual ~Initializer() {
	}
};
}
#endif /* Initializer_h */
