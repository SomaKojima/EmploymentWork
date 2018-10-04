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
	Quaternion dir = Quaternion::CreateFromYawPitchRoll(XMConvertToRadians(1.0f), 0.0f, 0.0f) * entity.GetTrans().GetDir();
	dir = Quaternion::Slerp(entity.GetTrans().GetDir(), dir, 1.0f);
	Vector3 angle = Vector3::Transform(angle, entity.GetTrans().GetDir());

	entity.GetTrans().SetDir(dir);
}
