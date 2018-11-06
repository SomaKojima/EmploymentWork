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
	void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
	DirectX::SimpleMath::Vector3 m_normal;	// �d�͂̌���
	std::list<DirectX::SimpleMath::Vector3> m_current;
};

