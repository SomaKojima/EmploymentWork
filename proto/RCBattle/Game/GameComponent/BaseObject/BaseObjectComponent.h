#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
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
	bool IsSomeDir();

	WallType GetWallType() { return m_wallType; }

private:
	WallType m_wallType;		// ���݂ǂ̕ǂɒ���t���Ă��邩
	DirectX::SimpleMath::Vector3 m_normal;	// �d�͂̌���
	WallComponent* m_currentWall;					// ���݂̏�
	WallComponent* m_lastWall;					// ���݂̏�
	PhysicsComponent* m_physics;
	float m_count;
	DirectX::SimpleMath::Quaternion m_rotate;
};

