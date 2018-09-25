#include "../../pch.h"
#include "TestComponent.h"
#include "../Scene/SceneManager.h"

TestComponent::TestComponent()
	:
	count(0)
{
}

TestComponent::~TestComponent()
{
}

void TestComponent::Update(DX::StepTimer const & timer)
{
	count++;

	if (count >= 60)
	{
		SceneManager* sceneManager = SceneManager::GetInstance();
		sceneManager->ChangeSceneID(SceneManager::SceneID::Play);
	}
}
