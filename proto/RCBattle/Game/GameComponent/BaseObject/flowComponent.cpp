#include "../../../pch.h"
#include "flowComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

FlowComponent::FlowComponent()
	:
	m_angle(0.0f),
	m_count(0)
{
}

FlowComponent::~FlowComponent()
{
}

void FlowComponent::Update(DX::StepTimer const & timer)
{
	m_angle+=3;
	if (m_angle > 360.0f)
	{
		m_angle = 0.0f;
	}

	m_count++;
	if (m_count > 10)
	{

		m_count = 0;
	}


	Vector3 accel = m_me->GetTrans().accel.GetLocal();
	accel.y += (abs(cos(XMConvertToRadians(m_angle))) * 0.004f);
	m_me->GetTrans().accel.SetLocal(accel);
}
