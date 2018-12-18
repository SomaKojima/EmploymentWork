#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"

class MyCamera;

/// <summary>
/// 物理のコンポーネントクラス
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

	// 更新
	void Update(DX::StepTimer const& timer) override;

private:
	MyCamera* m_camera;
	float m_x;
	float m_y;

	Type m_type;
};