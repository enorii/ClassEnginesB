#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	Scene() {}
	virtual ~Scene() {}
	virtual bool onCreate() = 0;
	virtual void update(const float deltaTime_) = 0;
	virtual void render() = 0;
};

#endif //SCENE_H