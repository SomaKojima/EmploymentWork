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
	CameraRotateComponent(MyCamera* camera);
	~CameraRotateComponent();

	// 更新
	void Update(DX::StepTimer const& timer) override;

private:
	MyCamera* m_camera;
	float m_x;
	float m_y;
};