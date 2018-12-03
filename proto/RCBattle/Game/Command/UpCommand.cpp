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
	Vector3 vel = entity.GetTrans().GetLocalVel();
	entity.GetTrans().SetLocalVel(vel);
  	vel.y = 0.05f;
	entity.GetTrans().SetLocalVel(vel);
}
