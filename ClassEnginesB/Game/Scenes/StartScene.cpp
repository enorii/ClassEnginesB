#include "StartScene.h"

StartScene::StartScene() : Scene() {
}


StartScene::~StartScene() {
}

bool StartScene::onCreate() {
	Debug::info("Creating Start Scene", "StartScene.cpp", __LINE__);
	CoreEngine::getInstance()->setCurrentScene(1);
	return true;
}

void StartScene::update(const float deltaTime_) {

}

void StartScene::render() {

}