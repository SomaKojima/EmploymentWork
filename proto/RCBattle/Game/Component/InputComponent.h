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
#include "Component.h"
#include "../Command/InputHandler.h"
#include "../Command/Command.h"

class BulletFactory;

/// <summary>
/// 入力のコンポーネントクラス
/// </summary>
class InputComponent : public Component
{
public:
	InputComponent();
	~InputComponent();

	// 初期化
	void Initialize(Entity & entity) override;
	// 更新
	void Update(Entity& entity, DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(Entity& entity, DX::StepTimer const& timer) override;
	// 描画
	void Draw(Entity & entity, Game* game) override;
	// 終了
	void Finalize(Entity & entity) override;

private:
	InputHandler m_inputHandle;
};

