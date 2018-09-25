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
#include "../../DebugCollision/DebugPlane.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class PlaneCollisionComponent : public Component
{
public:
	PlaneCollisionComponent(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 angle, float width, float height);
	~PlaneCollisionComponent();

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

private:
	DirectX::SimpleMath::Vector3 m_center;	// ���S
	DirectX::SimpleMath::Vector3 m_angle;	// �p�x
	float m_width;							// ����
	float m_height;							// �c��

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugPlane> m_obj;
};
