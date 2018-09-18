/// <summary>
/// Component.h
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
#include "../../StepTimer.h"
#include "../Object/Entity.h"
#include "../../Game.h"

/// <summary>
/// コンポーネントクラス
/// </summary>
class Component
{
protected:
	// コンストラクタ
	Component() {};

public:
	// 仮想デストラクタ
	virtual ~Component() {};

	// 初期化
	virtual void Initialize(Entity & entity) {};
	// 更新
	virtual void Update(Entity& m_entity, DX::StepTimer const& timer) {};
	// 遅延更新
	virtual void LateUpdate(Entity& m_entity, DX::StepTimer const& timer) {}
	// 描画
	virtual void Draw(Entity & entity, Game* game) {};
	// 終了
	virtual void Finalize(Entity & entity) {};

	// 当たり判定の処理
	virtual void OnCollide(Entity& entity, Entity& collide) {}
};