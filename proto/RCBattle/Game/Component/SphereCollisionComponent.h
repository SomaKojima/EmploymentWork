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
#include "Component.h"
#include "../DebugCollision/DebugSphere.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class SphereCollisionComponent : public Component
{
public:
	SphereCollisionComponent(DirectX::SimpleMath::Vector3 center, float radius);
	~SphereCollisionComponent();

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

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	float GetRadius() { return m_radius; }
private:
	DirectX::SimpleMath::Vector3 m_center; // ���̒��S
	float m_radius;   // ���̔��a

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugSphere> m_obj;
};
