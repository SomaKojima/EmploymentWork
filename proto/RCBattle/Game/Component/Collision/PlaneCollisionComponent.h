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
#include <list>
#include "CollisionComponent.h"
#include "../../DebugCollision/DebugPlane.h"
#include "../../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class PlaneCollisionComponent : public CollisionComponent
{
public:
	PlaneCollisionComponent(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 angle, float width, float height);
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

	const std::list<Collision::Triangle>* GetTriangleList() override { return &m_triangle; }

	Collision::CollisionType GetShapeType() { return Collision::CollisionType::TRIANGLE; }

private:
	DirectX::SimpleMath::Vector3 m_center;	// 中心
	DirectX::SimpleMath::Vector3 m_angle;	// 角度
	float m_width;							// 横幅
	float m_height;							// 縦幅

	std::list<Collision::Triangle> m_triangle;		// 平面の情報

	// 当たり判定の表示用オブジェクト
	std::unique_ptr<DebugPlane> m_obj;
};
