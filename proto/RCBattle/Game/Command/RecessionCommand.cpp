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
#include "RecessionCommand.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
RecessionCommand::RecessionCommand()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RecessionCommand::~RecessionCommand()
{
}

/// <summary>
/// ���s
/// </summary>
/// <param name="entity">����</param>
void RecessionCommand::Excute(Entity & entity)
{
	
	Vector3 vel = Vector3(entity.GetTrans().GetVel().x, entity.GetTrans().GetVel().y, -0.1f);
	entity.GetTrans().SetVel(vel);
}
