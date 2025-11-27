#include "StageNumber.h"
#include "../ImGui/imgui.h"

StageNumber::StageNumber()
{
	DontDestroyOnSceneChange();
	stagenum = -1;
	noDeath = false;
}

void StageNumber::Draw()
{
	ImGui::Begin("StageNumber");
	ImGui::InputInt("StageNumber", &stagenum);
	ImGui::Checkbox("NoDeath", &noDeath);
	ImGui::End();
}