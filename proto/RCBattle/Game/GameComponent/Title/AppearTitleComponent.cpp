#include "../../../pch.h"
#include "AppearTitleComponent.h"
#include "../../Object/EntityVector.h"
#include "../../Object/SpriteData.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

AppearTitleComponent::AppearTitleComponent(int time)
	:
	m_time(time)
{
}

AppearTitleComponent::~AppearTitleComponent()
{
}

void AppearTitleComponent::Initialize()
{
}

void AppearTitleComponent::Update(DX::StepTimer const & timer)
{
	// 処理が終わった時
	if (m_time == 0)
	{
		// タイトルロゴ
		Entity* entity = new Entity();
		entity->AddComponent(new UIRenderer(SpriteData::GetInstance()->GetTitleLogo(), RECT{ 0, 0, 500, 300 }, 0.3f));
		entity->GetTrans().pos.Set(Vector3(150.0f, 50.0f, 0.0f));
		EntityVector::GetInstance()->Add(entity);
	}

	if (m_time >= 0)
	{
		m_time--;
	}
}
