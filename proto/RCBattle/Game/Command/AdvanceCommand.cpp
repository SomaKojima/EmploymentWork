#include "../../pch.h"
#include "AdvanceCommand.h"
#include "../Utility/Utility.h"
#include "../Component//PhysicsComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
AdvanceCommand::AdvanceCommand()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AdvanceCommand::~AdvanceCommand()
{
}

/// <summary>
/// ���s
/// </summary>
/// <param name="entity">����</param>
void AdvanceCommand::Excute(Entity & entity)
{
	Vector3 vel = Vector3(entity.GetVel().x, entity.GetVel().y, 0.1f);
	entity.SetVel(vel);
}
