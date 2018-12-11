/// <summary>
/// Camera.h
/// 
/// �����:2018/12/11
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

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	// ������
	void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	void LateUpdate(DX::StepTimer const& timer) override;
	// �����蔻��̏���
	void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
};