#include "StageNumber.h"
#include "../ImGui/imgui.h"
#include "Screen.h"

StageNumber::StageNumber()
{
	DontDestroyOnSceneChange();
	stagenum = -1;
	noDeath = false;
	Clear = false;
	noSound = false;
}

void StageNumber::Draw()
{
	if (Screen::DEVELOPER_MODE == TRUE) {
		ImGui::Begin("StageNumber");
		ImGui::InputInt("StageNumber", &stagenum);
		ImGui::Checkbox("NoDeath", &noDeath);
		ImGui::Checkbox("Clear", &Clear);
		ImGui::Checkbox("NoSound", &noSound);
		ImGui::End();
	}
}