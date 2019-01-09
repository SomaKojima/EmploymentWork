#include "../../../pch.h"
#include "GameJudgeComponent.h"
#include "../../Object/EntityVector.h"
#include "ResultCameraComponent.h"

GameJudgeComponent::GameJudgeComponent(MyCamera* camera)
	:
	m_camera(camera)
{
}

GameJudgeComponent::~GameJudgeComponent()
{
}

void GameJudgeComponent::Update(DX::StepTimer const & timer)
{
	EntityVector* entityVector = EntityVector::GetInstance();

	Entity* player = entityVector->GetEntity("Player"); 
	Entity* enemy = entityVector->GetEntity("Enemy");
	if (player && !enemy)
	{
		player->AddComponent(new ResultCameraComponent(m_camera));
		m_me->Destroy();
	}
	else if (!player && enemy)
	{
		enemy->AddComponent(new ResultCameraComponent(m_camera));
		m_me->Destroy();
	}
}
