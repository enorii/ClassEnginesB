#include "Game1.h"

Game1::Game1() : GameInterface() {
	currentSceneNum = 0;
	currentScene = nullptr;

}


Game1::~Game1() {
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::onCreate() {
	if (CoreEngine::getInstance()->getCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->onCreate();

	}
	Debug::fatalError("Engine's scene is not initialized to 0", "Game1.cpp", __LINE__);
	return false;
}

void Game1::update(const float deltaTime_) {
	if (currentSceneNum != CoreEngine::getInstance()->getCurrentScene()) {
		buildScene();
	}
	currentScene->update(deltaTime_);
}

void Game1::render() {
	currentScene->render();
}

void Game1::buildScene() {
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::getInstance()->getCurrentScene()) {
		case 1:
			currentScene = new GameScene();
			break;
		default: //case 0:
			currentScene = new StartScene();
			break;
	}

	currentSceneNum = CoreEngine::getInstance()->getCurrentScene();
	if (!currentScene->onCreate()) {
		CoreEngine::getInstance()->exit();
	}
}