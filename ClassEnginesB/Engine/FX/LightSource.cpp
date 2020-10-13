#include "LightSource.h"


LightSource::LightSource(glm::vec3 position_, float ambientVal_, float diffuseVal_, glm::vec3 lightColour_) {
	position = position_;
	ambientVal = ambientVal_;
	diffuseVal = diffuseVal_;
	lightColour = lightColour_;
}

LightSource::~LightSource() { //i have no idea if im supposed to be deleting anything

}

//getters
glm::vec3 LightSource::GetPosition() const {
	return position;
}

float LightSource::GetAmbientVal() const {
	return ambientVal;
}

float LightSource::GetDiffuseVal() const {
	return diffuseVal;
}

glm::vec3 LightSource::GetLightColour() const {
	return lightColour;
}

//setters
void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::SetAmbientVal(float ambientVal_) {
	ambientVal = ambientVal_;
}

void LightSource::SetDiffuseVal(float diffuseVal_) {
	diffuseVal = diffuseVal_;
}

void LightSource::SetLightColour(glm::vec3 lightColour_) {
	lightColour = lightColour_;
}