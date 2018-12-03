#include "../../../pch.h"
#include "ShotComponent.h"
#include "../../Object/EntityVector.h"
#include "../../Object/SpriteData.h"
#include "../../GameComponent/Title/LineOfSightComponent.h"
#include "../../GameComponent/Title/AppearTitleComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ShotComponent::ShotComponent(int time)
	:
	m_time(time)
{
}

ShotComponent::~ShotComponent()
{
}

void ShotComponent::Update(DX::StepTimer const & timer)
{
	// 処理が終わった時
	if (m_time == 0)
	{
		Entity* entity = new Entity();
		// スプライトデータの読み込み
		SpriteData* spriteData = SpriteData::GetInstance();
		UIRenderer* UICom = new UIRenderer(spriteData->GetTitleBullet(), RECT{ 0,0,50,50}, 0.2f);
		entity->AddComponent(UICom);
		entity->AddComponent(new LineOfSightComponent(Vector3(300.0f, 100.0f, 0.0f), 60));
		entity->AddComponent(new AppearTitleComponent(60));
		entity->GetTrans().SetPos(m_me->GetTrans().GetPos() + Vector3(0.0f, 80.0f, 0.0f));
		EntityVector::GetInstance()->Add(entity);
	}

	if (m_time >= 0)
	{
		m_time--;
	}
}
