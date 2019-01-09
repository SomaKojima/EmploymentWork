#include "../../../pch.h"
#include "GameJudgeComponent.h"
#include "../../Object/EntityVector.h"
#include "../../Object/SpriteData.h"
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
	// スプライトデータの読み込み
	SpriteData* spriteData = SpriteData::GetInstance();
	EntityVector* entityVector = EntityVector::GetInstance();
	Entity* winStr = nullptr;

	Entity* player = entityVector->GetEntity("Player"); 
	Entity* enemy = entityVector->GetEntity("Enemy");
	if (player && !enemy)
	{
		player->AddComponent(new ResultCameraComponent(m_camera));

		winStr = new Entity();
		winStr->AddComponent(new UIRenderer(spriteData->GetWinPlayer(), RECT{ 0, 0, 800, 100 }, 0.1f));
		entityVector->Add(winStr);

		m_me->Destroy();
	}
	else if (!player && enemy)
	{
		enemy->AddComponent(new ResultCameraComponent(m_camera));

		winStr = new Entity();
		winStr->AddComponent(new UIRenderer(spriteData->GetWinNPC(), RECT{ 0, 0, 800, 100 }, 0.1f));
		entityVector->Add(winStr);

		m_me->Destroy();
	}
}
