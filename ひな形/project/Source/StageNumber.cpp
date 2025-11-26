#include "StageNumber.h"
#include "../ImGui/imgui.h"

StageNumber::StageNumber()
{
	DontDestroyOnSceneChange();
	stagenum = -1;
}

void StageNumber::Draw()
{
	ImGui::Begin("StageNumber");
	ImGui::InputInt("StageNumber", &stagenum);
	ImGui::End();
}