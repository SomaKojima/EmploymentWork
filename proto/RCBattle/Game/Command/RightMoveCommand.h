/// <summary>
/// RightMoveCommand.h
/// 
/// �����:2018/12/8
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "Command.h"

/// <summary>
/// �O�i�R�}���h�N���X
/// </summary>
class RightMoveCommand : public Command
{
public:
	// �R���X�g���N�^
	RightMoveCommand();
	// �f�X�g���N�^
	~RightMoveCommand();

	// ���s
	void Excute(Entity& entity) override;
};
