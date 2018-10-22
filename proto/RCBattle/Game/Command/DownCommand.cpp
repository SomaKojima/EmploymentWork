#include "../../pch.h"
#include "DownCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

DownCommand::DownCommand()
{
}

DownCommand::~DownCommand()
{
}

void DownCommand::Excute(Entity & entity)
{
	Vector3 vel = entity.GetTrans().GetVel();
	entity.GetTrans().SetVel(vel);
	vel.y = -0.05f;
	entity.GetTrans().SetVel(vel);
}
