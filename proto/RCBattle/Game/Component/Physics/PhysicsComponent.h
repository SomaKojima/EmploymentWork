/// <summary>
/// InputComponent.h
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
#include "../Component.h"

/// <summary>
/// �O���錾
/// </summary>
class SphereCollisionComponent;
class BoxCollisionComponent;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	void LateUpdate(DX::StepTimer const& timer) override;
	// �����蔻��̏���
	void OnCollide(Entity& collide, CollisionData& data) override;

	SphereCollisionComponent* GetSphereCollision() { return sphere; }
	BoxCollisionComponent* GetBoxCollision() { return box; }

	void SetIsFriction(bool isFriction) { m_isFriction = isFriction; }
	void SetIsGravity(bool isGravity) { m_isGravity = isGravity; }

private:
	float m_gravity;	// �d��
	bool m_isFriction;	// ���C
	bool m_isGravity;	// �d�͂̃t���O
	DirectX::SimpleMath::Vector3 m_repulsionVel;	// �������x

	SphereCollisionComponent* sphere;
	BoxCollisionComponent* box;
};