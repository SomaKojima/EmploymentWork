#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include <list>
#include "../../Component/Component.h"
#include "../../Data/Data.h"

class Entity;
class PhysicsComponent;
class WallComponent;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class BaseObjectComponent : public Component
{
public:
	BaseObjectComponent();
	~BaseObjectComponent();

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	void LateUpdate(DX::StepTimer const& timer) override;
	// �`��
	void Draw(Game* game) override;
	// �I��
	void Finalize() override;

	// �����蔻��̏���
	void OnCollide(Entity& collide, CollisionData* data) override;

	// �p�x����]������֐�
	DirectX::SimpleMath::Quaternion GetRotateDir();
	//bool IsSomeDir();

private:
	DirectX::SimpleMath::Vector3 m_normal;	// �d�͂̌���
	std::list<WallComponent*> m_current;
	std::list<WallComponent*> m_last;
	DirectX::SimpleMath::Quaternion m_rotate;
};

