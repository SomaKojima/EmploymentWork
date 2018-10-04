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
#include <list>
#include "../Component.h"

/// <summary>
/// �O���錾
/// </summary>
class SphereCollisionComponent;
class BoxCollisionComponent;
class PlaneCollisionComponent;

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
	void OnCollide(Entity& collide, CollisionData* data) override;

	void SetGravityDir(DirectX::SimpleMath::Vector3 dir) { m_gravityDir = dir; }
	void SetFriction(DirectX::SimpleMath::Vector3 friction) { m_friction = friction; }
	void SetIsFriction(bool isFriction) { m_isFriction = isFriction; }
	void SetIsGravity(bool isGravity) { m_isGravity = isGravity; }

	DirectX::SimpleMath::Vector3 GetGravityDir() { return m_gravityDir; }
	DirectX::SimpleMath::Vector3 GetFriction() { return m_friction; }

private:
	SphereCollisionComponent* CheckSphereList(Entity* entity, CollisionData* data);
	PlaneCollisionComponent* CheckPlaneList(Entity* entity, CollisionData* data);

private:
	float m_gravity;	// �d��
	DirectX::SimpleMath::Vector3 m_gravityDir;	// ���C�̌���

	DirectX::SimpleMath::Vector3 m_friction;	// ���C
	bool m_isFriction;	// ���C
	bool m_isGravity;	// �d�͂̃t���O

	std::list<SphereCollisionComponent*> m_spherelist;
	std::list<PlaneCollisionComponent*> m_planelist;
};