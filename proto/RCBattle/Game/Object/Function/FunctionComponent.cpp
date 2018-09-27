#include "../../../pch.h"
#include "FunctionComponent.h"
#include "../../Collision/Collision.h"
#include "../../Component/Component.h"
#include "../Entity.h"
#include "../../../Game.h"

using namespace DirectX::SimpleMath;

void FunctionComponent::InitializeComponent()
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Initialize();
	}
}

bool FunctionComponent::UpdateComponent(DX::StepTimer const & timer)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Update(timer);
	}
	return false;
}

bool FunctionComponent::LateComponentUpdate(DX::StepTimer const & timer)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->LateUpdate(timer);
	}
	return false;
}

void FunctionComponent::OnCollideComponent(Entity& entity, CollisionData* data)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->OnCollide(entity, data);
	}
}

void FunctionComponent::DrawCompoennt(Game* game)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Draw(game);
	}
}

void FunctionComponent::FinalizeComponent()
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Finalize();
		delete (*ite);
	}
	m_componentlist.clear();
}

void FunctionComponent::AddComponent(Component * component)
{
	m_componentlist.push_back(component);
	component->SetEntity(m_me);
}
