#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class LineOfSightComponent : public Component
{
public:
	LineOfSightComponent(DirectX::SimpleMath::Vector3 end, int time);
	~LineOfSightComponent();


	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;

private:
	DirectX::SimpleMath::Vector3 m_end;
	DirectX::SimpleMath::Vector3 m_dir;
	float m_speed;
	int m_time;
};
