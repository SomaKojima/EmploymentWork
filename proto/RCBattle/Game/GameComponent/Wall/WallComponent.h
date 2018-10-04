#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"
#include "../../Data/Data.h"

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class WallComponent : public Component
{
public:
	WallComponent(WallType wallType);
	~WallComponent();

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
	void OnCollide(Entity& collide, CollisionData* data) override;

	WallType GetWallType() { return m_wallType; }
	DirectX::SimpleMath::Vector3 GetNomal() { return m_normal; }
	DirectX::SimpleMath::Vector3 GetAngle() { return m_angle; }

private:
	WallType m_wallType;		// ���݂ǂ̕ǂɒ���t���Ă��邩
	DirectX::SimpleMath::Vector3 m_normal;	// �ǂ̖@��
	DirectX::SimpleMath::Vector3 m_angle;
};