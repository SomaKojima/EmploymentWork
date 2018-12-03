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
	Quaternion dir = Quaternion::Identity;
	float degree = 1.0f;

	Vector3 upDir = Vector3::Transform(Vector3::Up, entity.GetTrans().dir.Get());

	dir = Quaternion::CreateFromAxisAngle(upDir, -XMConvertToRadians(degree));

	entity.GetTrans().dir.Set(entity.GetTrans().dir.Get() * dir);
}
