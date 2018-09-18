/// <summary>
/// BoxCollisionComponent.h
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
#include "../../DebugCollision/DebugBox.h"

/// <summary>
/// �O���錾
/// </summary>
class SphereCollisionComponent;

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class BoxCollisionComponent : public Component
{
public:
	BoxCollisionComponent(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 radius);
	~BoxCollisionComponent();

	// �`��
	void Draw(Entity & entity, Game* game) override;

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	DirectX::SimpleMath::Vector3 GetRadius() { return m_radius; }

private:
	DirectX::SimpleMath::Vector3 m_center; // BOX�̒��S�_
	DirectX::SimpleMath::Vector3 m_radius; // ���̔����͈̔�

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugBox> m_obj;
};