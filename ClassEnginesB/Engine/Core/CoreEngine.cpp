#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr; //always declare static variables at the top of the cpp


CoreEngine::CoreEngine(){
	window = nullptr;
	isRunning = false;
	fps = 120;
	gameInterface = nullptr;
	currentSceneNum = 0;
	camera = nullptr;
}


CoreEngine::~CoreEngine(){
	onDestroy();
}

CoreEngine* CoreEngine::getInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::onCreate(std::string name_, int width_, int height_) {
	Debug::debugInit();
	Debug::setSeverity(messageType::TYPE_INFO);

	window = new Window();
	if (!window->onCreate(name_, width_, height_)) {
		std::cout << "Window failed to initialize" << std::endl;
		return isRunning = false; //isRunning = false -> idk she skipped thru fast
	}

	SDL_WarpMouseInWindow(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2); //centers the mouse

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl"); //very important ordering or something idk

	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");

	if (gameInterface) { //gameinterface !=nullptr
		if (!gameInterface->onCreate()) {
			Debug::error("Game failed to create", "CoreEngine.cpp", __LINE__); ///debug line or something we had to do 
		}
	}

	timer.start();

	Debug::info("Everything worked.", "CoreEngine.cpp", __LINE__);

	return isRunning = true;
}

void CoreEngine::run() {
	while (isRunning) {
		timer.updateFrameTicks();
		EventListener::Update();
		update(timer.getDeltaTime());
		render();
		SDL_Delay(timer.getSleepTime(fps));
	}
	if (!isRunning) { //redundant, however makes it clear what is going on
		onDestroy();
	}
}

bool CoreEngine::getIsRunning() const {
	return isRunning;
}

void CoreEngine::update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->update(deltaTime_);
	}
}

void CoreEngine::render() {
	glClearColor(0.0f, 0.7f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface) {
		gameInterface->render();
	}
	//Render the game
	SDL_GL_SwapWindow(window->getWindow());
}

void CoreEngine::onDestroy() {

	ShaderHandler::GetInstance()->onDestroy();
	TextureHandler::GetInstance()->onDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();

	delete camera;
	camera = nullptr;

	delete window;
	gameInterface = nullptr;

	window = nullptr;

	SDL_Quit();
	exit();
}

void CoreEngine::setGameInterface(GameInterface* gameInterface_) {
	gameInterface = gameInterface_;
}

int CoreEngine::getCurrentScene() {
	return currentSceneNum;
}
void CoreEngine::setCurrentScene(int sceneNum_) {
	currentSceneNum = sceneNum_;
}

void CoreEngine::exit() {
	isRunning = false;
}

glm::vec2 CoreEngine::GetWindowSize() const {
	return glm::vec2(window->getWidth(), window->getHeight());
}

void CoreEngine::setCamera(Camera* camera_) {
	camera = camera_;
}

Camera* CoreEngine::getCamera() const {
	return camera;
}


void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_) {

}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse_) {
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_) {
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}