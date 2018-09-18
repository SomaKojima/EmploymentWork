/// <summary>
/// Entity.h
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
#include <vector>
#include <map>
#include <typeinfo>
#include "../../StepTimer.h"
#include "../Collision/CCell.h"

#include "Function/FunctionComponent.h"
#include "../Utility/BidirectionalList.h"

/// <summary>
/// クラスの宣言
/// </summary>
class Game;
class Component;
class EntityOfTree;

// 変形の情報
class Transform
{
	friend Entity;
public:
	Transform() :
		m_angle(DirectX::SimpleMath::Vector3::Zero),
		m_dir(DirectX::SimpleMath::Quaternion::Identity),
		m_vel(DirectX::SimpleMath::Vector3::Zero),
		m_trans(DirectX::SimpleMath::Vector3::Zero),
		m_radius(0.0f),
		m_world(DirectX::SimpleMath::Matrix::Identity),
		m_local(DirectX::SimpleMath::Matrix::Identity)
	{};

	~Transform() {};
public:
	void SetDir(DirectX::SimpleMath::Quaternion dir) { m_dir = dir; }
	void SetAngle(DirectX::SimpleMath::Vector3 &angle)
	{
		m_angle = angle;
		m_dir = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_angle.z) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), m_angle.y) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f), m_angle.x);
	}
	void SetVel(DirectX::SimpleMath::Vector3 &vel) { m_vel = vel; }
	void SetTrans(DirectX::SimpleMath::Vector3 trans) { m_trans = trans; }
	void SetRadius(float radius) { m_radius = radius; }
	void SetWorld(DirectX::SimpleMath::Matrix& world) { m_world = world; }
	void SetLocal(DirectX::SimpleMath::Matrix& local) { m_local = local; }

	DirectX::SimpleMath::Quaternion GetDir() { return m_dir; }
	DirectX::SimpleMath::Vector3 GetAngle() { return m_angle; }
	DirectX::SimpleMath::Vector3 GetVel() { return m_vel; }
	DirectX::SimpleMath::Vector3 GetTrans() { return m_trans; }
	float GetRadius() { return m_radius; }
	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }
	DirectX::SimpleMath::Matrix GetLocal() { return m_local; }

private:
	DirectX::SimpleMath::Quaternion m_dir;		// 方向
	DirectX::SimpleMath::Vector3 m_angle;		// 角度				
	DirectX::SimpleMath::Vector3 m_vel;			// 速度
	DirectX::SimpleMath::Vector3 m_trans;		// 移動
	float m_radius;

	DirectX::SimpleMath::Matrix m_world;		// ワールド座標
	DirectX::SimpleMath::Matrix m_local;		// ローカル座標
};

/// <summary>
///オブジェクトクラス 
/// </summary>
class Entity : public FunctionComponent
{
public:
	Entity();
	~Entity();

	// 初期化
	void Initialize();
	// 更新
	bool Update(DX::StepTimer const& timer);
	// 終了
	void Finalize();
	// 消す
	void Destroy();

	// 子の追加
	Entity* AddChild(Entity* entity);
	// 子の削除
	void DeleteChild();

	// マトリクスの更新
	void UpdateMatrix();

	//　プロパティ
	// セッター
	void SetParent(Entity* parent) { m_parent = parent; }

	// ゲッター
	Transform& GetTrans() { return m_transform; }
	Entity& GetParent() { return *m_parent; }
	OBJECT_FOR_TREE* GetOFT() { return m_pOFT; }
	EntityOfTree* GetEOF() { return m_pEOF; }

private:
	Transform m_transform;						// 変形の情報

	Entity* m_parent;							// 親のポインタ

	std::vector<Entity*> m_childVector;			// 子のコンテナ

	OBJECT_FOR_TREE* m_pOFT;					// 当たり判定用
	EntityOfTree* m_pEOF;						// 実体をリストで回す用
};