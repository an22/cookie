//
//  SceneObject_hpp
//  lighting-test
//
//  Created by Antiufieiev Michael on 06.07.2021.
//

#ifndef SceneObject_hpp
#define SceneObject_hpp

#include <glm/glm.hpp>
#endif /* SceneObject_hpp */

class SceneObject {
private:
	glm::vec3 position;
	glm::mat4 modelMat;
public:
	
	SceneObject(glm::vec3 pos) {
		setPosition(pos);
	}
	
	virtual void transform(const glm::mat4 &transformation) {
		modelMat = transformation * modelMat;
	}
	
	virtual void setPosition(const glm::vec3 &position) {
		this->position = position;
		modelMat = glm::translate(glm::mat4(1.0f), position);
	}
	
	virtual void setPosition(float x, float y, float z) {
		this->position = glm::vec3(x, y, z);
		modelMat = glm::translate(glm::mat4(1.0f), position);
	}
	const glm::mat4& getModelMat() {
		return modelMat;
	}
	virtual ~SceneObject() {}
};
