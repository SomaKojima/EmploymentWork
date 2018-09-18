#include "../../../pch.h"
#include "FunctionComponent.h"
#include "../../Component/Component.h"
#include "../Entity.h"
#include "../../../Game.h"

void FunctionComponent::InitializeComponent()
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Initialize(*m_me);
	}
}

bool FunctionComponent::UpdateComponent(DX::StepTimer const & timer)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Update(*m_me, timer);
	}
	return false;
}

bool FunctionComponent::LateComponentUpdate(DX::StepTimer const & timer)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->LateUpdate(*m_me, timer);
	}
	return false;
}

void FunctionComponent::OnCollideComponent(Entity& entity)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->OnCollide(*m_me, entity);
	}
}

void FunctionComponent::DrawCompoennt(Game* game)
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Draw(*m_me, game);
	}
}

void FunctionComponent::FinalizeComponent()
{
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		(*ite)->Finalize(*m_me);
		delete (*ite);
	}
	m_componentlist.clear();
}

void FunctionComponent::AddComponent(Component * component)
{
	m_componentlist.push_back(component);
}
