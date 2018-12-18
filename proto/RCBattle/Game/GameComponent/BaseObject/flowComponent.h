#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include <list>
#include "../../Component/Component.h"
#include "../../Data/Data.h"

class Entity;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class FlowComponent : public Component
{
public:
	FlowComponent();
	~FlowComponent();

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
	//void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
	float m_angle;
	int m_count;
};

