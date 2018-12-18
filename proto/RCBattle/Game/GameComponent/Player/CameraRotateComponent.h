#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../Component/Component.h"

class MyCamera;

/// <summary>
/// �����̃R���|�[�l���g�N���X
/// </summary>
class CameraRotateComponent : public Component
{
public:
	enum Type
	{
		Normal,
		Horizon,
		Vertical,
		NONE,

		TYPE_MAX
	};
public:
	CameraRotateComponent(MyCamera* camera, Type type = Type::Normal);
	~CameraRotateComponent();

	// �X�V
	void Update(DX::StepTimer const& timer) override;

private:
	MyCamera* m_camera;
	float m_x;
	float m_y;

	Type m_type;
};