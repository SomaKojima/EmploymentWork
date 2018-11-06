#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Component/Component.h"

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class EnemeyComponent : public Component
{
public:
	EnemeyComponent();
	~EnemeyComponent();

	// �X�V
	void Update(DX::StepTimer const& timer) override;

	// �����蔻��̏���
	void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
	int count;
};
