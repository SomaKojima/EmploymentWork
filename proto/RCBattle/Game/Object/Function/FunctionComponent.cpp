#include "../../../pch.h"
#include "FunctionComponent.h"
#include "../../Component/Component.h"
#include "../Entity.h"

bool FunctionComponent::UpdateComponent(Entity& entity, DX::StepTimer const & timer)
{
	for (auto ite = m_componentMap.begin(); ite != m_componentMap.end(); ite++)
	{
		ite->second->Update(entity, timer);
	}
	return false;
}

bool FunctionComponent::LateComponentUpdate(Entity& entity, DX::StepTimer const & timer)
{
	for (auto ite = m_componentMap.begin(); ite != m_componentMap.end(); ite++)
	{
		ite->second->LateUpdate(entity, timer);
	}
	return false;
}
