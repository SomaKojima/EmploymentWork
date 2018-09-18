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
	Vector3 vel = Vector3(entity.GetTrans().GetVel().x, -0.1f, entity.GetTrans().GetVel().z);
	entity.GetTrans().SetVel(vel);
}
