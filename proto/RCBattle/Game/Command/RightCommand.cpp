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
	Vector3 angle = entity.GetAngle();
	Vector3 vel = entity.GetVel();
	angle.y -= XMConvertToRadians(1.0f);
	//if (vel.z >= -0.001f)
	//{
	//}
	//else
	//{
	//	angle.y += XMConvertToRadians(1.0f);
	//}

	entity.SetAngle(angle);

	//Vector3 vel = Vector3(-0.1f, entity.GetVel().y, entity.GetVel().z);
	//entity.SetVel(vel);
}
