#include "GameScene.h"

GameScene::GameScene() : Scene() /*,shape(nullptr)*/ {

}


GameScene::~GameScene() {
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::onCreate() {
	Debug::info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::getInstance()->setCamera(new Camera);
	CoreEngine::getInstance()->getCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	//CoreEngine::getInstance()->getCamera()->AddLightSource(new LightSource(glm::vec3)) //need this for lighting whenever i actually get it working

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	Model* model = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader") /*glm::vec3(0.0f)*/);

	SceneGraph::GetInstance()->AddModel(model);

	//std::cout << "Min Vert: " << glm::to_string(model->GetBoundingBox().minVert) << std::endl;
	//std::cout << "Max Vert: " << glm::to_string(model->GetBoundingBox().maxVert) << std::endl;


	//model->AddMesh(new Mesh(&vertexList), ShaderHandler::GetInstance()->GetShader("colourShader"))); //usually not okay to do pointers in functions, but it's okay here cuz it gets deleted

	///TextureHandler::GetInstance()->CreateTexture("checkerboard", "Resources/Textures/CheckerboardTexture.png");

	///model->AddMesh(new Mesh(&vertexList, ShaderHandler::GetInstance()->GetShader("basicShader"), TextureHandler::GetInstance()->GetTexture("checkerboard")));


	//shape = new GameObject(model, glm::vec3(0.0f, -1.0f, 0.0f));
	//shape->SetScale(glm::vec3(0.5f)); //u can delete this i think, check recording to also add multiple models

	GameObject* apple = new GameObject(model, glm::vec3(3.0f, -1.0f, 0.0f));
	apple->SetScale(glm::vec3(0.7f));
	SceneGraph::GetInstance()->AddGameObject(apple);

	return true;
}

void GameScene::update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::render() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SceneGraph::GetInstance()->Render(CoreEngine::getInstance()->getCamera());
}