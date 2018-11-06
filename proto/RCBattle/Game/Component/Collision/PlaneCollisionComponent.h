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
#include <list>
#include "CollisionComponent.h"
#include "../../DebugCollision/DebugPlane.h"
#include "../../Collision/Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class PlaneCollisionComponent : public CollisionComponent
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

	const std::list<Collision::Triangle>* GetTriangleList() override { return &m_triangle; }

	Collision::CollisionType GetShapeType() { return Collision::CollisionType::TRIANGLE; }

private:
	DirectX::SimpleMath::Vector3 m_center;	// ���S
	DirectX::SimpleMath::Vector3 m_angle;	// �p�x
	float m_width;							// ����
	float m_height;							// �c��

	std::list<Collision::Triangle> m_triangle;		// ���ʂ̏��

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugPlane> m_obj;
};
