#include "../../pch.h"
#include "UpCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

UpCommand::UpCommand()
{
}

UpCommand::~UpCommand()
{
}

void UpCommand::Excute(Entity & entity)
{
	Vector3 vel = entity.GetTrans().GetVel();
	entity.GetTrans().SetVel(vel);
	vel.z += 0.1f;
	if (vel.z >= 0.2f)
	{
		vel.z = 0.2f;
	}
	entity.GetTrans().SetVel(vel);
}
