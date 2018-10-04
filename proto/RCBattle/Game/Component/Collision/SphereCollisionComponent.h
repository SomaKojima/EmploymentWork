/// <summary>
/// SphereCollisionComponent.h
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
#include "../../DebugCollision/DebugSphere.h"
#include "../../Collision/Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class SphereCollisionComponent : public Component
{
public:
	SphereCollisionComponent(DirectX::SimpleMath::Vector3 center, float radius);
	~SphereCollisionComponent();

	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	void LateUpdate(DX::StepTimer const& timer) override;
	// �`��
	void Draw(Game* game) override;
	// �I��
	void Finalize() override;

	DirectX::SimpleMath::Vector3 HitPlanePosToVec(PlaneCollisionComponent* plane, DirectX::SimpleMath::Vector3& hitPos);

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	float GetRadius() { return m_radius; }
	Collision::Sphere& GetSphere(){ return m_sphere; }
private:
	DirectX::SimpleMath::Vector3 m_center; // ���̒��S
	float m_radius;   // ���̔��a
	Collision::Sphere m_sphere;

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugSphere> m_obj;
};
