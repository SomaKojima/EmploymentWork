/// <summary>
/// TestComponent.h
/// 
/// 制作日:2018/9/24
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <Model.h>
#include "Component.h"

/// <summary>
/// モデルコンポーネントクラス
/// </summary>
class TestComponent : public Component
{
public:
	TestComponent();
	~TestComponent();

	void Update(DX::StepTimer const& timer) override;
private:
	int count;
};
