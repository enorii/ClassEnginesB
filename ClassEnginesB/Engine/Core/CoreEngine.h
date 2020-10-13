#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"

#include "../Camera/Camera.h"

#include "../Event/EventListener.h"

#include "../Rendering/SceneGraph.h"

class CoreEngine{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	CoreEngine();
	~CoreEngine();
	bool onCreate(std::string name_, int width_, int height_);
	void run();
	bool getIsRunning() const;
	Camera* getCamera() const;
	
	static CoreEngine* getInstance();
	void setGameInterface(GameInterface* gameInterface_);
	void setCamera(Camera* camera);

	int getCurrentScene();
	void setCurrentScene(int sceneNum_);

	void exit();

	glm::vec2 GetWindowSize() const;

	void NotifyOfMousePressed(glm::vec2 mouse_);
	void NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(glm::vec2 mouse_);
	void NotifyOfMouseScroll(int y_);


	//i think some stuff was supposed to be added here and i missed it
private:
	//CoreEngine();
	//~CoreEngine();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void update(float deltaTime_);
	void render();
	void onDestroy();
	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
	
};

#endif //!COREENGINE