#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <list>
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
	//bool IsSomeDir();

private:
	DirectX::SimpleMath::Vector3 m_normal;	// 重力の向き
	std::list<WallComponent*> m_current;
	std::list<WallComponent*> m_last;
	DirectX::SimpleMath::Quaternion m_rotate;
};

