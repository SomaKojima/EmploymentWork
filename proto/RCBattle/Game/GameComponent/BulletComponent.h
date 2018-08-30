#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Component/Component.h"

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class BulletComponent : public Component
{
public:
	BulletComponent();
	~BulletComponent();

	// ������
	void Initialize(Entity & entity) override;
	// �X�V
	void Update(Entity& entity, DX::StepTimer const& timer) override;
	// �x���X�V
	void LateUpdate(Entity& entity, DX::StepTimer const& timer) override;
	// �`��
	void Draw(Entity & entity, Game* game) override;
	// �I��
	void Finalize(Entity & entity) override;

	// �����蔻��̏���
	void OnCollide(Entity& entity, Entity& collide) override;
};