#include "../../pch.h"
#include "DriftCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

DriftCommand::DriftCommand()
{
}

DriftCommand::~DriftCommand()
{
}

void DriftCommand::Excute(Entity & entity)
{
	Vector3 vel = entity.GetTrans().GetVel();
	entity.GetTrans().SetVel(vel);
	vel.y = 0.055f;
	entity.GetTrans().SetVel(vel);
}
