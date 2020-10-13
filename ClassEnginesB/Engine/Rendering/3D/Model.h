#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"

class Model
{
public:
	Model(const std::string& objFilePath, const std::string& mtlFilePath_, GLuint shaderProgram_);
	~Model();
	void render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);

	glm::mat4 GetTransform(int index_) const;

	BoundingBox GetBoundingBox();
	GLuint GetShaderProgram() const;
private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram; //also shaders
	std::vector<glm::mat4> modelInstances;
	LoadObjModel* obj;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const;
	void LoadModel();

	BoundingBox box;
};

#endif //MODEL_H