/// <summary>
/// RightCommand.h
/// 
/// �����:2018/7/4
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
class RightCommand : public Command
{
public:
	// �R���X�g���N�^
	RightCommand();
	// �f�X�g���N�^
	~RightCommand();

	// ���s
	void Excute(Entity& entity) override;
};
