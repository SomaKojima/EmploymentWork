/// <summary>
/// SphereCollisionComponent.h
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
#include "../../DebugCollision/DebugSphere.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class PlaneCollisionComponent : public Component
{
public:
	PlaneCollisionComponent();
	~PlaneCollisionComponent();

	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(DX::StepTimer const& timer) override;
	// 描画
	void Draw(Game* game) override;
	// 終了
	void Finalize() override;

private:
};
