#pragma once
#include "Globals.h"
#include "Component.h"
#include <string>
#include <vector>

class GameObject {
public:
	GameObject();
	~GameObject();

	void Enable();
	void Update();
	void Disable();

	Component* CreateComponent(Component_Type type);

private:
	bool active = false;

	std::string name;
	
	std::vector<Component*> components;

	GameObject* parent = nullptr;
	std::vector<GameObject*>  childs;
};