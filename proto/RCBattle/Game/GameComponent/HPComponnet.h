#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Component/Component.h"

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class HPComponent : public Component
{
public:
	HPComponent();
	~HPComponent();

	// �X�V
	void Update(Entity& entity, DX::StepTimer const& timer) override;

	// �����蔻��̏���
	void OnCollide(Entity& entity, Entity& collide) override;

	void sethp(int hP) { hp = hP; }
	int GetHp() { return hp; }
private:
	int hp;
	int atk;
};