#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../Component/Component.h"
#include "../../Data/Data.h"

class Entity;
class PhysicsComponent;
class WallComponent;

/// <summary>
/// 物理のコンポーネントクラス
/// </summary>
class BaseObjectComponent : public Component
{
public:
	BaseObjectComponent();
	~BaseObjectComponent();

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

	// 当たり判定の処理
	void OnCollide(Entity& collide, CollisionData* data) override;

	// 角度を回転させる関数
	DirectX::SimpleMath::Quaternion GetRotateDir();
	bool IsSomeDir();

	WallType GetWallType() { return m_wallType; }

private:
	WallType m_wallType;		// 現在どの壁に張り付いているか
	DirectX::SimpleMath::Vector3 m_normal;	// 重力の向き
	WallComponent* m_currentWall;					// 現在の床
	WallComponent* m_lastWall;					// 現在の床
	PhysicsComponent* m_physics;
	float m_count;
	DirectX::SimpleMath::Quaternion m_rotate;
};

