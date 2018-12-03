#include "../../pch.h"
#include "Transform.h"
#include "Entity.h"

Transform::Transform(Entity * _entity)
	:
entity(_entity),
dir(*this),
vel(*this),
accel(*this),
pos(*this),
radius(*this),
world(*this),
local(*this)
{
}

Transform::Transform() 
	:
	entity(nullptr),
	dir(*this),
	vel(*this),
	accel(*this),
	pos(*this),
	radius(*this),
	world(*this),
	local(*this)
{
}

Transform::~Transform()
{
}

DirectX::SimpleMath::Matrix & Transform::World::Get()
{
	// TODO: return ステートメントをここに挿入します
	if (trans.entity)
	{
		if (trans.entity->GetParent())
		{
			return trans.local.Get() * trans.entity->GetParent()->GetTrans().world.Get();
		}
	}
	return trans.local.Get();
}
