#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {
public:
	GameInterface() {

	}
	virtual ~GameInterface() {

	}
	virtual bool onCreate() = 0;
	virtual void update(const float deltaTime_) = 0;
	virtual void render() = 0;
};

#endif // GAMEINTERFACE_H
