/// <summary>
/// BoxCollisionComponent.h
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
#include "../../DebugCollision/DebugBox.h"

/// <summary>
/// 前方宣言
/// </summary>
class SphereCollisionComponent;

/// <summary>
/// 箱の当たり判定のコンポーネントクラス
/// </summary>
class BoxCollisionComponent : public Component
{
public:
	BoxCollisionComponent(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 radius);
	~BoxCollisionComponent();

	// 描画
	void Draw(Entity & entity, Game* game) override;

	DirectX::SimpleMath::Vector3 GetCenter() { return m_center; }
	DirectX::SimpleMath::Vector3 GetRadius() { return m_radius; }

private:
	DirectX::SimpleMath::Vector3 m_center; // BOXの中心点
	DirectX::SimpleMath::Vector3 m_radius; // 幅の半分の範囲

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugBox> m_obj;
};