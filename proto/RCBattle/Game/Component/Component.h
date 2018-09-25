/// <summary>
/// Component.h
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
#include "../../StepTimer.h"
#include "../Object/Entity.h"
#include "../../Game.h"

/// <summary>
/// �R���|�[�l���g�N���X
/// </summary>
class Component
{
protected:
	// �R���X�g���N�^
	Component() {};

public:
	// ���z�f�X�g���N�^
	virtual ~Component() {};

	// ������
	virtual void Initialize() {};
	// �X�V
	virtual void Update(DX::StepTimer const& timer) {};
	// �x���X�V
	virtual void LateUpdate(DX::StepTimer const& timer) {}
	// �`��
	virtual void Draw(Game* game) {};
	// �I��
	virtual void Finalize() {};

	// �����蔻��̏���
	virtual void OnCollide(Entity& collide) {}

	void SetEntity(Entity* me) { m_me = me; }
protected:
	Entity* m_me;
};