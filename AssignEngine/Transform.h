#pragma once

#include "Component.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include <vector>

class Transform : public Component {
public:
	Transform(Component_Type type);
	~Transform();

	void SetPos(float3 pos);
	void SetRot(float3 rot);
	void SetScale(float3 scale);

private:
	float3 pos = { 0.0f, 0.0f, 0.0f };
	float3 rot = { 0.0f, 0.0f, 0.0f };

};