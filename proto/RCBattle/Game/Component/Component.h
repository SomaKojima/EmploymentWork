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
	virtual void Initialize(Entity & entity) {};
	// �X�V
	virtual void Update(Entity& m_entity, DX::StepTimer const& timer) {};
	// �x���X�V
	virtual void LateUpdate(Entity& m_entity, DX::StepTimer const& timer) {}
	// �`��
	virtual void Draw(Entity & entity, Game* game) {};
	// �I��
	virtual void Finalize(Entity & entity) {};

	// �����蔻��̏���
	virtual void OnCollide(Entity& entity, Entity& collide) {}
};