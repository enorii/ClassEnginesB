#include "LoadObjModel.h"



LoadObjModel::LoadObjModel() {
	currentMaterial = Material();
	verticies.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);

}


LoadObjModel::~LoadObjModel() {
	onDestroy();
}

void LoadObjModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_) {
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);

}

void LoadObjModel::LoadModel(const std::string& filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			verticies.push_back(glm::vec3(x, y, z));

			glm::vec3 vertex = glm::vec3(x, y, z);

			//minimum values
			if (vertex.x < box.minVert.x) {
				box.minVert.x = vertex.x;
			}
			if (vertex.y < box.minVert.y) {
				box.minVert.y = vertex.y;
			}
			if (vertex.z < box.minVert.z) {
				box.minVert.z = vertex.z;
			}

			//max values
			if (vertex.x > box.maxVert.x) {
				box.maxVert.x = vertex.x;
			}
			if (vertex.y > box.maxVert.y) {
				box.maxVert.y = vertex.y;
			}
			if (vertex.z > box.maxVert.z) {
				box.maxVert.z = vertex.z;
			}
		}

		//HOMEWORK
		//NORMAL DATA (vn)
		if (line.substr(0, 3) == "vn ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXTURE DATA (vt)
		if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(2));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//FACE DATA (this shit is going to be annoying apparently. use breakpoints or whatever) (f) 
		/*
		if (line.substr(0, 2) == "f ") {
			int vert, text, norm;

			// Find first number in cluster of 3 for each vertex, texture, and normal indicies
			std::string data = line.substr(2);
			int space = data.find(" ");
			std::string d1 = data.substr(0, space);
			std::stringstream vertText(d1.substr(0, d1.find("/")));
			vertText >> vert;
			indices.push_back(vert - 1);
			d1 = d1.substr(d1.find("/") + 1);
			std::stringstream texText(d1.substr(0, d1.find("/")));
			texText >> text;
			textureIndices.push_back(text - 1);
			d1 = d1.substr(d1.find("/") + 1);
			std::stringstream normText(d1.substr(0, d1.find("/")));
			normText >> norm;
			normalIndices.push_back(norm - 1);

			space = data.find(" ");

			// Find the second number in the cluster of 3 between the '/'
			data = data.substr(data.find(" ") + 1);
			std::string d2 = data.substr(0, data.find(" "));
			std::stringstream vertText2(d2.substr(0, d2.find("/")));
			vertText2 >> vert;
			indices.push_back(vert - 1);
			d2 = d2.substr(d2.find("/") + 1);
			std::stringstream texText2(d2.substr(0, d2.find("/")));
			texText2 >> text;
			textureIndices.push_back(text - 1);
			d2 = d2.substr(d2.find("/") + 1);
			std::stringstream normText2(d2.substr(0, d2.find("/")));
			normText2 >> norm;
			normalIndices.push_back(norm - 1);

			space = data.find(" ");

			//Find the last number after the 2 '/'
			data = data.substr(data.find(" ") + 1);
			std::string d3 = data.substr(0, data.find(" "));
			std::stringstream vertText3(d3.substr(0, d3.find("/")));
			vertText3 >> vert;
			indices.push_back(vert - 1);
			d3 = d3.substr(d3.find("/") + 1);
			std::stringstream texText3(d3.substr(0, d3.find("/")));
			texText3 >> text;
			textureIndices.push_back(text - 1);
			d3 = d3.substr(d3.find("/") + 1);
			std::stringstream normText3(d3.substr(0, d3.find("/")));
			normText3 >> norm;
			normalIndices.push_back(norm - 1);

		} */

		//face data solution 2, why do neither of these work??
		if (line.substr(0, 2) == "f ") {
			std::stringstream f(line.substr(2));

			//this finds properties in obj file
			int x, y, z;
			char slash;

			for (int i = 0; i < 3; i++) {
				f >> x >> slash >> y >> slash >> z;

				//this sets the values to 0
				indices.push_back(x - 1);
				textureIndices.push_back(y - 1);
				normalIndices.push_back(z - 1);
			}
		}

		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing(); //load any final mesh. make sure it's outside of the while loop
}

std::vector<Vertex> LoadObjModel::GetVerts() {
	return meshVertices;
}

std::vector<int> LoadObjModel::GetIndices() {
	return indices;
}

std::vector<SubMesh> LoadObjModel::GetSubMeshes() {
	return subMeshes;
}

BoundingBox LoadObjModel::GetBoundingBox() {
	return box;
}

void LoadObjModel::onDestroy() { //yes
	verticies.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}


void LoadObjModel::PostProcessing() {
	for (int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = verticies[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.texCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh subMesh;
	subMesh.vertexList = meshVertices;
	subMesh.meshIndicies = indices;
	subMesh.material = currentMaterial;

	subMeshes.push_back(subMesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadObjModel::LoadMaterial(const std::string& matName_) {
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadObjModel::LoadMaterialLibrary(const std::string& matFilePath_) {
	MaterialLoader::LoadMaterial(matFilePath_);
}