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

	/*PlaneCollisionComponent* plane = m_me->GetComponent<PlaneCollisionComponent>();
	if (plane)
	{
		m_normal = Vector3(plane->GetTriangle()->plane.a, plane->GetTriangle()->plane.b, plane->GetTriangle()->plane.c);
	}*/
}

void WallComponent::Update(DX::StepTimer const & timer)
{
	PlaneCollisionComponent* plane = m_me->GetComponent<PlaneCollisionComponent>();
	if (plane)
	{
		Collision::Plane plane2 = (*plane->GetTriangleList().begin()).plane;
		m_normal = -Vector3(plane2.a, plane2.b, plane2.c);
	}
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
