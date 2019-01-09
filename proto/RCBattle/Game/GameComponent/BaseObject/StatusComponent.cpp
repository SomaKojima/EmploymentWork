#include "../../../pch.h"
#include "StatusComponent.h"

#include "../../../Game.h"

StatusComponent::StatusComponent()
	:
	m_hp(300)
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
		Game::AddText(L"Hit_Bullet");
		m_hp--;
	}
}
