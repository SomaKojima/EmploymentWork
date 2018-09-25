/// <summary>
/// RecessionCommand.cpp
/// 
/// �����:2018/7/5
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "RightCommand.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
RightCommand::RightCommand()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RightCommand::~RightCommand()
{
}

/// <summary>
/// ���s
/// </summary>
/// <param name="entity">����</param>
void RightCommand::Excute(Entity & entity)
{
	Vector3 angle = entity.GetTrans().GetAngle();

	if (entity.GetTrans().GetVel().z >= 0.0f)
	{
		angle.y += XMConvertToRadians(-1.0f);
	}
	else if (entity.GetTrans().GetVel().z < 0.0f)
	{
		angle.y += XMConvertToRadians(1.0f);
	}

	entity.GetTrans().SetAngle(angle);
}
