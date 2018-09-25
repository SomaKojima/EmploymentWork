#include "../../../pch.h"
#include "StartButtonComponent.h"
#include "../../Scene/SceneManager.h"
#include "../../Object/EntityVector.h"

StartButtonComponent::StartButtonComponent()
{
}

StartButtonComponent::~StartButtonComponent()
{
}

void StartButtonComponent::Press()
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->ChangeSceneID(SceneManager::SceneID::Play);
}
