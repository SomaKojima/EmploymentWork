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

void BulletComponent::Initialize(Entity & entity)
{
}

void BulletComponent::Update(Entity & entity, DX::StepTimer const & timer)
{
	// ‰æ–ÊŠOo‚½ê‡Á‚·
	Vector3 pos = Vector3::Transform(Vector3::Zero, entity.GetWorld());
	if(pos.x > 25.0f ||
		pos.x < -25.0f ||
		pos.z > 25.0f ||
		pos.z < -25.0f)
	{
		entity.Destroy();
	}
}

void BulletComponent::LateUpdate(Entity & entity, DX::StepTimer const & timer)
{
}

void BulletComponent::Draw(Entity & entity, Game * game)
{
}

void BulletComponent::Finalize(Entity & entity)
{
}

void BulletComponent::OnCollide(Entity & entity, Entity & collide)
{
	entity.Destroy();
}
