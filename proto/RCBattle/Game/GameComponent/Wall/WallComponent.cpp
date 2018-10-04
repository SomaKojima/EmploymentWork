#include "../../../pch.h"
#include "WallComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

WallComponent::WallComponent(WallType wallType)
	:
	m_wallType(wallType),
	m_normal(Vector3::Down),
	m_angle(Vector3::Zero)
{
}

WallComponent::~WallComponent()
{
}

void WallComponent::Initialize()
{
	switch (m_wallType)
	{
	case Bottom:
		m_normal = Vector3::Down;
		m_angle = Vector3::Zero;
		break;
	case Right:
		m_normal = Vector3::Right;
		m_angle = Vector3(0.0f, 0.0f, XMConvertToRadians(90.0f));
		break;
	case Front:
		m_normal = Vector3::Backward;
		m_angle = Vector3(XMConvertToRadians(-90.0f), 0.0f, 0.0f);
		break;
	case Left:
		m_normal = Vector3::Left;
		m_angle = Vector3(0.0f, 0.0f, XMConvertToRadians(-90.0f));
		break;
	case Back:
		m_normal = Vector3::Forward;
		m_angle = Vector3(XMConvertToRadians(90.0f), 0.0f, 0.0f);
		break;
	}
}

void WallComponent::Update(DX::StepTimer const & timer)
{
}

void WallComponent::LateUpdate(DX::StepTimer const & timer)
{
}

void WallComponent::Draw(Game * game)
{
}

void WallComponent::Finalize()
{
}

void WallComponent::OnCollide(Entity & collide, CollisionData * data)
{
}
