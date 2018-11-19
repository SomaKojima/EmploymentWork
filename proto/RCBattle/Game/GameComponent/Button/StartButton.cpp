#include "../../../pch.h"
#include "StartButton.h"
#include "../../Scene/SceneManager.h"
#include "../../Object/EntityVector.h"

StartButton::StartButton()
{
}

StartButton::~StartButton()
{
}

void StartButton::Press()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->ChangeSceneID(SceneManager::SceneID::Play);
}
