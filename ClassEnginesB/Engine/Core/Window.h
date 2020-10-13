#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <String>
#include <iostream> // make sure header files are always in this order or stuff will break

class Window
{
public:
	Window();
	~Window();
	bool onCreate(std::string name_, int width_, int height_);
	void onDestroy();
	int getWidth();
	int getHeight();
	SDL_Window* getWindow() const;
private:
	void setPreAttributes();
	void setPostAttributes();
	int width, height;
	SDL_Window* window;
	SDL_GLContext context;
};

#endif // !WINDOW_H