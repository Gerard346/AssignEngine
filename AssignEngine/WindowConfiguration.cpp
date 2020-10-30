#include "Application.h"
#include "WindowConfiguration.h"

WindowConfiguration::WindowConfiguration() :ModuleUIManager()
{
	isActive.push_back(Activate());
}

WindowConfiguration::~WindowConfiguration()
{
	isActive.clear();
}

bool WindowConfiguration::Start()
{
	return true;
}

update_status WindowConfiguration::Update(float dt)
{
	if (isActive[0].isActive()) {

	}
	return UPDATE_CONTINUE;
}

bool WindowConfiguration::CleanUp()
{
	return true;
}
