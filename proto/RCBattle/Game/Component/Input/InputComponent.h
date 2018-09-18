/// <summary>
/// InputComponent.h
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component.h"
#include "../../Command/InputHandler.h"
#include "../../Command/Command.h"

class BulletFactory;

/// <summary>
/// 入力のコンポーネントクラス
/// </summary>
class InputComponent : public Component
{
public:
	InputComponent();
	~InputComponent();

	// 更新
	void Update(Entity& entity, DX::StepTimer const& timer) override;

private:
	InputHandler m_inputHandle;
};

