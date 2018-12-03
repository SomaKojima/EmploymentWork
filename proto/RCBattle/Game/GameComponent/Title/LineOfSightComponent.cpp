#include "../../../pch.h"
#include "LineOfSightComponent.h"
#include "../../Object/EntityVector.h"
#include "../../Object/SpriteData.h"
#include "../../GameComponent/Title/LineOfSightComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

LineOfSightComponent::LineOfSightComponent(DirectX::SimpleMath::Vector3 end, int time)
	:
	m_end(end),
	m_speed(0.0f),
	m_time(time),
	m_dir(Vector3::Zero)
{
}

LineOfSightComponent::~LineOfSightComponent()
{
}

void LineOfSightComponent::Initialize()
{
	Vector3 pos = m_me->GetTrans().GetPos();
	Vector3 vec = m_end - pos;
	float length = vec.Length();
	m_speed = length / m_time;
	vec.Normalize();
	m_dir = vec;

	// 速度を設定する
	m_me->GetTrans().SetLocalVel(m_dir * m_speed);
}

void LineOfSightComponent::Update(DX::StepTimer const & timer)
{
	// 処理が終わった時
	if (m_time == 0)
	{
		Vector3 vel = Vector3::Zero;
		m_me->GetTrans().SetLocalVel(vel);
	}

	if(m_time >= 0)
	{
		m_time--;
	}
}
