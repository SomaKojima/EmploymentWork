/// <summary>
/// DriftCommand.h
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
class DriftCommand : public Command
{
public:
	// �R���X�g���N�^
	DriftCommand();
	// �f�X�g���N�^
	~DriftCommand();

	// ���s
	void Excute(Entity& entity) override;
};
