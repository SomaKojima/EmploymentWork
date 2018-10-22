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
	float degree = 1.0f;

	Vector3 upDir = Vector3::Transform(Vector3::Up, entity.GetTrans().GetDir());

	Vector3 forward = Vector3::Forward;
	Vector3 entityForward = Vector3::Transform(forward, entity.GetTrans().GetDir());
	float cos_ = forward.Dot(entityForward);
	float currentRot = acos(cos_);

	Vector3 right = Vector3::Right;
	float rightFlag = right.Dot(entityForward);
	Quaternion dir = Quaternion::Identity;
	if (rightFlag <= 0)
	{
		dir = Quaternion::CreateFromAxisAngle(upDir, currentRot - XMConvertToRadians(degree));
	}
	else
	{
		dir = Quaternion::CreateFromAxisAngle(upDir, -currentRot - XMConvertToRadians(degree));
	}

	entity.GetTrans().SetDir(dir);
}
