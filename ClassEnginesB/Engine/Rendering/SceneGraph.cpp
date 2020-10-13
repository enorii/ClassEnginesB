#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();

SceneGraph::SceneGraph() {

}

SceneGraph::~SceneGraph() {
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance() {
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy() {
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_) {
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) { //checks to see if shaderprogram does not exist as a key
		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp)); //insert into model map (it had to be a pair, what kind? who objects or two items but they have to be the same type)
	}
	else {
		sceneModels[model_-> GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* go_, std::string tag_) {
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		go_->SetTag(tag_); //redundant, but just to make sure nothing messes up
		sceneGameObjects[tag_] = go_;
	}
	else {
		Debug::error("Trying to add a GameObject with a tag" + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);
}

GameObject* SceneGraph::GetGameObject(std::string tag_) {
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];
	}
	return nullptr;
}


void SceneGraph::Update(const float deltaTime_) {
	for (auto go : sceneGameObjects) {
		go.second->update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_) {
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			m->render(camera_);
		}
	}
}
