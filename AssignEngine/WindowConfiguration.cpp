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
	name_engine = "Assign Engine";
	name_organization = "CITM - UPC";

	return true;
}

update_status WindowConfiguration::Update(float dt)
{
	if (isActive[0].isActivate) {
		bool* p = &isActive[0].isActivate;
		Draw("Config Window", p);

	}

	return UPDATE_CONTINUE;
}

bool WindowConfiguration::CleanUp()
{
	return true;
}

void WindowConfiguration::Draw(const char* title, bool *p_open)
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

	ImGui::Begin("Configuration Window", p_open);

	if (ImGui::CollapsingHeader("Application")) {
		ImGui::Text("Name Of The Engine: %s", name_engine);
		ImGui::Text("Organization: %s", name_organization);

		//ImGui::Text("Framerate %.1 f", )
	}
	if (ImGui::CollapsingHeader("Window")) {

	}
	if (ImGui::CollapsingHeader("FileSystem")) {

	}
	if (ImGui::CollapsingHeader("Input")) {

	}
	if (ImGui::CollapsingHeader("Hardware")) {

	}
	ImGui::End();

}

