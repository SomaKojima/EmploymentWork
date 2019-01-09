#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"

class MyCamera;

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class ResultCameraComponent : public Component
{
public:
	ResultCameraComponent(MyCamera* camera);
	~ResultCameraComponent();

	// 更新
	void Update(DX::StepTimer const& timer) override;

private:
	MyCamera* m_camera;
	float m_angle;
	int m_time;
};