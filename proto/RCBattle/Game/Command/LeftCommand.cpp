/// <summary>
/// LeftCommand.cpp
/// 
/// �����:2018/7/5
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "LeftCommand.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
LeftCommand::LeftCommand()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LeftCommand::~LeftCommand()
{
}

/// <summary>
/// ���s
/// </summary>
/// <param name="entity">����</param>
void LeftCommand::Excute(Entity & entity)
{
	Vector3 angle = entity.GetAngle();
	angle.y += XMConvertToRadians(1.0f);

	entity.SetAngle(angle);

	//Vector3 vel = Vector3(0.1f, entity.GetVel().y, entity.GetVel().z);
	//entity.SetVel(vel);
}
