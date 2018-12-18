#include "../../../pch.h"
#include "EnemyCannonComponent.h"
#include "../../Object/EntityVector.h"
#include "../../Object/Factory/BulletFactory.h"

using namespace DirectX::SimpleMath;

EnemyCannonComponent::EnemyCannonComponent()
	:
	m_count(0)
{
}

EnemyCannonComponent::~EnemyCannonComponent()
{
}

void EnemyCannonComponent::Update(DX::StepTimer const & timer)
{
	m_count++;
	if (m_count > 30)
	{
		m_count = 0;
		EntityVector* entityVector = EntityVector::GetInstance();
		// ’e‚Ìì¬
		BulletFactory* bulletFactory = BulletFactory::GetInstance();
		Entity* entity = bulletFactory->CreateBullet();

		entity->GetTrans().dir.Set(m_me->GetTrans().dir.GetWorld());
		entity->GetTrans().vel.SetLocal(Vector3(0.0f, 0.0f, 0.5f));

		Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().world.Get());
		pos += Vector3::Transform(Vector3(0.0f, -0.1f, 2.0f), m_me->GetTrans().dir.GetWorld());
		entity->GetTrans().pos.Set(pos);

		entity->SetName("Bullet");

		// ƒvƒŒƒCƒ„[‚Ì’e‚ÌÝ’è
		entity->SetTag(Tag::Player2);

		entityVector->Add(entity);
	}
}
