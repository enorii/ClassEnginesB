#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glew.h>
#include <glm/glm.hpp>

class LightSource {

public:

	LightSource(glm::vec3 position_, float ambientVal_, float diffuseVal_, glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 GetPosition() const;
	float GetAmbientVal() const;
	float GetDiffuseVal() const;
	glm::vec3 GetLightColour() const;

	void SetPosition(glm::vec3 position_);
	void SetAmbientVal(float ambientVal_);
	void SetDiffuseVal(float diffuseVal_);
	void SetLightColour(glm::vec3 lightColour_);

private:
	glm::vec3 position;
	float ambientVal;
	float diffuseVal;
	glm::vec3 lightColour;
};

#endif //LightSource