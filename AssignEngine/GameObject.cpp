#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	Enable();
}

GameObject::~GameObject()
{
}

void GameObject::Enable()
{
	active = true;
}

void GameObject::Update()
{
}

void GameObject::Disable()
{
	active = false;
}

Component* GameObject::CreateComponent(Component_Type type)
{
	Component* new_component = nullptr;

	return new_component;
}
