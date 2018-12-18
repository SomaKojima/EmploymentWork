
#include "../../pch.h"
#include "RightMoveCommand.h"

using namespace DirectX::SimpleMath;

RightMoveCommand::RightMoveCommand()
{
}

RightMoveCommand::~RightMoveCommand()
{
}

void RightMoveCommand::Excute(Entity & entity)
{

	Vector3 accel = entity.GetTrans().accel.GetLocal();

	accel.x = -0.03f;

	entity.GetTrans().accel.SetLocal(accel);
}
