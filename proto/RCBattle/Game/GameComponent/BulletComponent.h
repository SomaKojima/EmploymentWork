#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component/Component.h"

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class BulletComponent : public Component
{
public:
	BulletComponent();
	~BulletComponent();

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

	// 当たり判定の処理
	void OnCollide(Entity& entity, Entity& collide) override;
};