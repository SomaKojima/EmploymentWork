/// <summary>
/// UpCommand.h
/// 
/// �����:2018/7/11
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
class UpCommand : public Command
{
public:
	// �R���X�g���N�^
	UpCommand();
	// �f�X�g���N�^
	~UpCommand();

	// ���s
	void Excute(Entity& entity) override;
};
