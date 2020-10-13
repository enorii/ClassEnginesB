#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/CoreEngine.h"
#include "Scenes/GameScene.h"
#include "Scenes/StartScene.h"

class Game1 : public GameInterface {
public:
	Game1();
	virtual ~Game1();

	virtual bool onCreate();
	virtual void update(const float deltaTime_);
	virtual void render();
private:
	int currentSceneNum;
	Scene* currentScene;
	void buildScene();

};
#endif //GAME1_H