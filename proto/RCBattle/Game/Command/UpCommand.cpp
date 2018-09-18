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
	Vector3 vel = Vector3(entity.GetTrans().GetVel().x, 0.1f, entity.GetTrans().GetVel().z);
	entity.GetTrans().SetVel(vel);
}
