#pragma once

enum Component_Type {
	COMPONENT_UNKNOWN,
	COMPONENT_TRANSFORM,
	COMPONENT_MESH,
	COMPONENT_MATERIAL
};

class Component {
public:
	Component(Component_Type type);
	virtual ~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

	bool isActive() const;

private:
	Component_Type comp_type = COMPONENT_UNKNOWN;
	bool active = false;
};