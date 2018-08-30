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
	Component() : m_name(nullptr){};

public:
	// 仮想デストラクタ
	virtual ~Component() {};

	// 初期化
	virtual void Initialize(Entity & entity) = 0;
	// 更新
	virtual void Update(Entity& m_entity, DX::StepTimer const& timer) = 0;
	// 遅延更新
	virtual void LateUpdate(Entity& m_entity, DX::StepTimer const& timer) = 0;
	// 描画
	virtual void Draw(Entity & entity, Game* game) = 0;
	// 終了
	virtual void Finalize(Entity & entity) = 0;

	// 当たり判定の処理
	virtual void OnCollide(Entity& entity, Entity& collide) {};

	char* GetName() { return m_name; }

protected:
	char* m_name;
};