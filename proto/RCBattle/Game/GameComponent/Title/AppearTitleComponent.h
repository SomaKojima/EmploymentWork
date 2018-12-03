#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class AppearTitleComponent : public Component
{
public:
	AppearTitleComponent(int time);
	~AppearTitleComponent();


	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;

private:
	int m_time;
};
