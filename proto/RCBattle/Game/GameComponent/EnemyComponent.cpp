#include "EnemyComponent.h"
#include "../Scene/SceneManager.h"

EnemeyComponent::EnemeyComponent()
	:
	m_count(3)
{
}

EnemeyComponent::~EnemeyComponent()
{
}

void EnemeyComponent::Update(DX::StepTimer const & timer)
{
}

void EnemeyComponent::OnCollide(Entity & collide, Collision::CollisionData* data)
{
	if (collide.GetName() == "Bullet")
	{
		m_count--;
		if (m_count < 0)
		{
			SceneManager* sceneManager = SceneManager::GetInstance();
			sceneManager->ChangeSceneID(SceneManager::SceneID::Title);
		}
	}
}
