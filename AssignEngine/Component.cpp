#include "Component.h"

Component::Component(Component_Type type)
{
}

Component::~Component()
{
}

void Component::Enable()
{
	active = true;
}

void Component::Update()
{
}

void Component::Disable()
{
	active = false;
}

bool Component::isActive() const
{
	return active;
}
