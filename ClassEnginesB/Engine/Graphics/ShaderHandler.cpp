#include "ShaderHandler.h"



ShaderHandler::ShaderHandler()
{
}


ShaderHandler::~ShaderHandler() {
	onDestroy();
}

std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr; //yes
std::map<std::string, GLuint> ShaderHandler::programs = std::map<std::string, GLuint>(); //yes

//static std::unique_ptr<ShaderHandler> shaderInstance;
//friend std::default_delete<ShaderHandler>;

ShaderHandler* ShaderHandler::GetInstance() {
	if (shaderInstance.get() == nullptr) {
		shaderInstance.reset(new ShaderHandler);
	}
	return shaderInstance.get();
}

std::string ShaderHandler::ReadShader(const std::string& filePath_) {
	std::string shaderCode = "";
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try { //testbed
		file.open(filePath_);
		std::stringstream tmpStream;
		tmpStream << file.rdbuf();
		file.close();
		shaderCode = tmpStream.str();
	}
	catch (std::ifstream::failure error_) { //it doesn't throw exceptions and stuff i guess
		Debug::error("Could not read the sahder: " + filePath_, "ShaderHandler.cpp", __LINE__);
		return "";
	}
	return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_) {
	GLint compileResult = 0;
	GLuint shader = glCreateShader(shaderType_);
	const char* shaderCodePtr = source_.c_str(); //this is very important. aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa something convert strings to char*
	const int shaderCodeSize = source_.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (!compileResult) {
		GLint infoLogLength = 0; 
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::string shaderString(shaderLog.begin(), shaderLog.end());
		Debug::error("Error Compiling Shader " + shaderName_ + ". Error: \n" + shaderString, "ShaderHandler.cpp", __LINE__);
		return 0;
	}
	return shader;
}

void ShaderHandler::CreateProgram(const std::string& shaderName_, const std::string& vertexShaderFileName_, const std::string& fragmentShaderFileName_) {
	std::string vertexShaderCode = ReadShader(vertexShaderFileName_);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFileName_);

	if (vertexShaderCode == "" || fragmentShaderCode == "") {
		return; //tells the compiler to fuck off from this shit since we already did it somewhere else (error checking or whatever)
	}

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);

	if (vertexShader == 0 || fragmentShader == 0) {
		return; //usually u write a debug line and shit but again we already did it.
	}
	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (!linkResult) { //checking value
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::string programString(programLog.begin(), programLog.end());
		Debug::error("Failed to link shader " + shaderName_ + ". Error: " + programString, "ShaderHandler.cpp", __LINE__);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(program);
		return;
	}
	programs[shaderName_] = program; //dont name ur program thingies program 1, 2, 3 etc idk
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint ShaderHandler::GetShader(const std::string& shaderName_) {
	if (programs.find(shaderName_) != programs.end()) {
		return programs[shaderName_];
	}
	return 0;
}

void ShaderHandler::onDestroy() {
	for (auto p : programs) {
		glDeleteProgram(p.second);

	}
	programs.clear();
}