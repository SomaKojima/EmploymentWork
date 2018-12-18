
#include "../../pch.h"
#include "LeftMoveCommand.h"

using namespace DirectX::SimpleMath;

LeftMoveCommand::LeftMoveCommand()
{
}

LeftMoveCommand::~LeftMoveCommand()
{
}

void LeftMoveCommand::Excute(Entity & entity)
{

	Vector3 accel = entity.GetTrans().accel.GetLocal();

	accel.x = 0.03f;

	entity.GetTrans().accel.SetLocal(accel);
}
