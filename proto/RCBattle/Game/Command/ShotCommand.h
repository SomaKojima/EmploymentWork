/// <summary>
/// ShotCommand.h
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
/// �O���錾
/// </summary>
class BulletFactory;

/// <summary>
/// �O�i�R�}���h�N���X
/// </summary>
class ShotCommand : public Command
{
public:
	// �R���X�g���N�^
	ShotCommand();
	// �f�X�g���N�^
	~ShotCommand();

	// ���s
	void Excute(Entity& entity) override;

private:

	// �e�̃t�@�N�g��
	BulletFactory* m_bulletFactory;
};
