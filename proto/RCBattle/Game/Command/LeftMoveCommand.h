/// <summary>
/// LeftMoveCommand.h
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
class LeftMoveCommand : public Command
{
public:
	// �R���X�g���N�^
	LeftMoveCommand();
	// �f�X�g���N�^
	~LeftMoveCommand();

	// ���s
	void Excute(Entity& entity) override;
};
