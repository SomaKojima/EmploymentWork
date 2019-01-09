#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"

class MyCamera;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class ResultCameraComponent : public Component
{
public:
	ResultCameraComponent(MyCamera* camera);
	~ResultCameraComponent();

	// �X�V
	void Update(DX::StepTimer const& timer) override;

private:
	MyCamera* m_camera;
	float m_angle;
	int m_time;
};