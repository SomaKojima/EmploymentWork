#include "EnemyComponent.h"
#include "../Scene/SceneManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

EnemeyComponent::EnemeyComponent()
	:
	m_count(3),
	m_target(nullptr)
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

	if (m_target)
	{
		Vector3 targetVec = m_target->GetTrans().pos.Get() - m_me->GetTrans().pos.Get();


	}
}
