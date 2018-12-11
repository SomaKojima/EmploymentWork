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
	const float accelerator = 1.0f;
	const float InitialVelocity = 1.0f;
	Vector3 accel = entity.GetTrans().accel.Get();

	

	accel.z = 0.0f;

	entity.GetTrans().accel.Set(accel);
}
