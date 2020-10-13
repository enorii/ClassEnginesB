#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 colour;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<int> meshIndicies;
	Material material;
};

class Mesh {
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_); //passing Vertex in by reference with *
	~Mesh();
	void render(Camera* camera, std::vector<glm::mat4> instances_);
private:
	void generateBuffers();

	SubMesh subMesh;

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, projLoc;
	GLuint textureLoc;
};

#endif //MESH_H