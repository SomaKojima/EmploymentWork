#include "../../pch.h"
#include "AdvanceCommand.h"
#include "../Utility/Utility.h"

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
	Vector3 accel = entity.GetTrans().accel.GetLocal();
	
	accel.z = 0.03f;

	entity.GetTrans().accel.SetLocal(accel);
}
