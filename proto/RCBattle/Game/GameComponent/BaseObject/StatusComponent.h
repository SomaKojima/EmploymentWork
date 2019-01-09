#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class StatusComponent : public Component
{
public:
	StatusComponent();
	~StatusComponent();

	// ������
	//void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	//void LateUpdate(DX::StepTimer const& timer) override;
	// �`��
	//void Draw(Game* game) override;
	// �I��
	//void Finalize() override;

	// �����蔻��̏���
	void OnCollide(Entity& collide, Collision::CollisionData* data) override;

	int GetHP() { return m_hp; }

private:
	int m_hp;
};

