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
	Component() : m_name(nullptr){};

public:
	// ���z�f�X�g���N�^
	virtual ~Component() {};

	// ������
	virtual void Initialize(Entity & entity) = 0;
	// �X�V
	virtual void Update(Entity& m_entity, DX::StepTimer const& timer) = 0;
	// �x���X�V
	virtual void LateUpdate(Entity& m_entity, DX::StepTimer const& timer) = 0;
	// �`��
	virtual void Draw(Entity & entity, Game* game) = 0;
	// �I��
	virtual void Finalize(Entity & entity) = 0;

	// �����蔻��̏���
	virtual void OnCollide(Entity& entity, Entity& collide) {};

	char* GetName() { return m_name; }

protected:
	char* m_name;
};