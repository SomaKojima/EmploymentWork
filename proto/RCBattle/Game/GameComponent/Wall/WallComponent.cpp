#include "../../../pch.h"
#include "WallComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

WallComponent::WallComponent(WallType wallType)
	:
	m_wallType(wallType),
	m_normal(Vector3::Down)
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
		break;
	case Right:
		m_normal = Vector3::Right;
		break;
	case Front:
		m_normal = Vector3::Backward;
		break;
	case Left:
		m_normal = Vector3::Left;
		break;
	case Back:
		m_normal = Vector3::Forward;
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
