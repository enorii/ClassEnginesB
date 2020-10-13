#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Core/Component.h"

class GameObject {
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void render(Camera* camera_);
	void update(const float deltaTime_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	std::string GetTag() const;

	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	BoundingBox GetBoundingBox();

	template <typename T>
	void AddComponent(T& parent_) {
		parent = parent_
	}

	template <typename T>
	void GetComponent(T& parent_) {
		//parent = parent_
		//return parent;
	}

	template <typename T>
	void RemoveComponent(T& parent_) {
		delete parent;
		parent = nullptr;
	}

private:

	Model* model;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	int modelInstance;
	BoundingBox box;

	std::string tag;

	bool hit;
};

#endif //GAMEOBJECT_H