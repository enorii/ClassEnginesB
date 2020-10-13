#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../../Engine/Core/CoreEngine.h"
class StartScene : public Scene {
public:
	StartScene();
	virtual ~StartScene();
	virtual bool onCreate();
	virtual void update(const float deltaTime_);
	virtual void render();
};

#endif //!STARTSCENE_H