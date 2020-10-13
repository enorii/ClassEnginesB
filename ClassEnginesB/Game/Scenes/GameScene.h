#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual bool onCreate();
	virtual void update(const float deltaTime_);
	virtual void render();

private:
};

#endif //!GAMESCENE_H