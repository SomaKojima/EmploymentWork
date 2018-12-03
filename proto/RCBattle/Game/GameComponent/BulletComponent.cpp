#include "../../pch.h"
#include "BulletComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

BulletComponent::BulletComponent()
{
}

BulletComponent::~BulletComponent()
{
}

void BulletComponent::Initialize()
{
}

void BulletComponent::Update(DX::StepTimer const & timer)
{
	// 画面外出た場合消す
	Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().world.Get());
	if(pos.x > 25.0f ||
		pos.x < -25.0f ||
		pos.z > 25.0f ||
		pos.z < -25.0f)
	{
		m_me->Destroy();
	}
}

void BulletComponent::LateUpdate(DX::StepTimer const & timer)
{
}

void BulletComponent::Draw(Game * game)
{
}

void BulletComponent::Finalize()
{
}

void BulletComponent::OnCollide(Entity & collide, Collision::CollisionData* data)
{
	m_me->Destroy();
}
