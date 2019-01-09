#include "../../../pch.h"
#include "StatusComponent.h"

StatusComponent::StatusComponent()
	:
	m_hp(3)
{
}

StatusComponent::~StatusComponent()
{
}

void StatusComponent::Update(DX::StepTimer const & timer)
{
	if (m_hp <= 0)
	{
		m_me->Destroy();
	}
}

void StatusComponent::OnCollide(Entity & collide, Collision::CollisionData * data)
{
	if (collide.GetName() == "Bullet")
	{
		m_hp--;
	}
}
