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
	Vector3 vel = entity.GetTrans().GetVel();
	// ��ނ��Ă����ꍇ
	if (vel.z <= 0.1f)
	{
		vel.z = 0.1f;
	}
	else
	{
		int a = 0;
	}
	vel.z += (vel.z / 60.0f);

	entity.GetTrans().SetVel(vel);
}
