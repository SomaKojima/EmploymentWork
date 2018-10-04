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
	Quaternion dir = Quaternion::CreateFromYawPitchRoll(XMConvertToRadians(-1.0f), 0.0f, 0.0f) * entity.GetTrans().GetDir();
	dir = Quaternion::Slerp(entity.GetTrans().GetDir(), dir, 1.0f);

	entity.GetTrans().SetDir(dir);
}
