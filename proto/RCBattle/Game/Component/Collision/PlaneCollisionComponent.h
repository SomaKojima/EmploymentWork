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

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class PlaneCollisionComponent : public Component
{
public:
	PlaneCollisionComponent();
	~PlaneCollisionComponent();

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

private:
};
