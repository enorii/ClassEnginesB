#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader() {

}

void MaterialLoader::LoadMaterial(std::string filePath_) {
	std::ifstream in(filePath_.c_str(), std::ios::in); //c_srt to convert to char star
	if (!in) {
		Debug::error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		//homework here! complete reading in all the parts of the material (ns, d, ka, kd, ks) think objloader
		else if (line.substr(0, 4) == "\tNs") {
			std::istringstream v(line.substr(4));
			v >> m.shininess;
		}

		else if (line.substr(0, 3) == "\td") {
			std::istringstream v(line.substr(3));
			v >> m.transparency;
		}

		else if (line.substr(0, 4) == "\tKa") {
			std::istringstream v(line.substr(4));
			glm::vec3 temp = glm::vec3();
			v >> temp.x >> temp.y >> temp.z;
			m.ambient = temp;
		}

		else if (line.substr(0, 4) == "\tKd") {
			std::istringstream v(line.substr(4));
			glm::vec3 temp = glm::vec3();
			v >> temp.x >> temp.y >> temp.z;
			m.diffuse = temp;
		}

		else if (line.substr(0, 4) == "\tKs") {
			std::istringstream v(line.substr(4));
			glm::vec3 temp = glm::vec3();
			v >> temp.x >> temp.y >> temp.z;
			m.specular = temp;
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_) {
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}