#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class ShotComponent : public Component
{
public:
	ShotComponent(int time);
	~ShotComponent();

	// 更新
	void Update(DX::StepTimer const& timer) override;

private:
	int m_time;
};
