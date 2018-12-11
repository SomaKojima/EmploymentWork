/// <summary>
/// Camera.h
/// 
/// 制作日:2018/12/11
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <list>
#include "../Component.h"

/// <summary>
/// 前方宣言
/// </summary>

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	// 初期化
	void Initialize() override;
	// 更新
	void Update(DX::StepTimer const& timer) override;
	// 遅延更新
	void LateUpdate(DX::StepTimer const& timer) override;
	// 当たり判定の処理
	void OnCollide(Entity& collide, Collision::CollisionData* data) override;

private:
};