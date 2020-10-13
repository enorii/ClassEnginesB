#include "Window.h"



Window::Window(){
	width = 0;
	height = 0;
	window = nullptr;
}


Window::~Window(){
	onDestroy();
}

bool Window::onCreate(std::string name_, int width_, int height_) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL" << std::endl;
		return false;
	}
	width = width_;
	height = height_;

	setPreAttributes();

	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	if (!window) { //window == nullptr
		std::cout << "Failed to create window" << std::endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);
	std::cout << "Graphics card: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	setPostAttributes();
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST); //if not enabled, opengl renders on first come first server basis, if enabled, renders based on z value

	glViewport(0, 0, width, height);

	std::cout << "Graphics card: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

void Window::onDestroy() {
	SDL_GL_DeleteContext(context); //delete the pointer
	SDL_DestroyWindow(window);
	window = nullptr; //then set it to nullptr to avoid memory leaks
}

int Window::getWidth() {
	return width;
}

int Window::getHeight() {
	return height;
}

SDL_Window* Window::getWindow() const {
	return window;
}

void Window::setPreAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::setPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}