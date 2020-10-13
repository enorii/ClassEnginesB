#include "Engine/Core/Window.h"
#include "Engine/Core/Coreengine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {
	CoreEngine::getInstance()->setGameInterface(new Game1);

	if (!CoreEngine::getInstance()->onCreate("aaaaaaaaa", 800, 600)) {
		std::cout << "Engine failed to be created" << std::endl;
		return 0;
	}
	CoreEngine::getInstance()->run();
	return 0;
}