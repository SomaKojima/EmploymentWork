#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"

class MyCamera;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class PlayerCannonComponent : public Component
{
public:
	PlayerCannonComponent(MyCamera* camera);
	~PlayerCannonComponent();

	// ������
	//void Initialize() override;
	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	//void LateUpdate(DX::StepTimer const& timer) override;
	// �`��
	//void Draw(Game* game) override;
	// �I��
	//void Finalize() override;

	// �����蔻��̏���
	//void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
	MyCamera* m_camera;
};