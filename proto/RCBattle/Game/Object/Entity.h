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
#include <list>
#include "../../StepTimer.h"
#include "../Collision/CCell.h"

#include "Function/FunctionComponent.h"
#include "../Utility/BidirectionalList.h"

#include "../Data/Data.h"

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
		m_dir(DirectX::SimpleMath::Quaternion::Identity),
		m_vel(DirectX::SimpleMath::Vector3::Zero),
		m_accel(DirectX::SimpleMath::Vector3::Zero),
		m_pos(DirectX::SimpleMath::Vector3::Zero),
		m_radius(0.0f),
		m_world(DirectX::SimpleMath::Matrix::Identity),
		m_local(DirectX::SimpleMath::Matrix::Identity)
	{};

	~Transform() {};
public:
	// setter
	void SetDir(DirectX::SimpleMath::Quaternion dir) { m_dir = dir; }
	void SetAngle(DirectX::SimpleMath::Vector3 &angle) 
	{ 
		m_dir = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle.y, angle.x, angle.z); 
	}
	//void SetVel(DirectX::SimpleMath::Vector3 &vel) { m_vel = vel; }
	void SetLocalVel(DirectX::SimpleMath::Vector3 &vel) { 
		m_vel = DirectX::SimpleMath::Vector3::Transform(vel, m_dir); 
	}
	void SetAccel(DirectX::SimpleMath::Vector3 &accel) { m_accel = accel; }
	void SetPos(DirectX::SimpleMath::Vector3 pos) { m_pos = pos; }
	void SetRadius(float radius) { m_radius = radius; }
	void SetWorld(DirectX::SimpleMath::Matrix& world) {
		m_world = world;
		m_pos = m_world.Translation();
	}
	void SetLocal(DirectX::SimpleMath::Matrix& local) { m_local = local; }

	// getter
	DirectX::SimpleMath::Quaternion& GetDir() { return m_dir; }
	//DirectX::SimpleMath::Vector3& GetVel() { return m_vel; }
	DirectX::SimpleMath::Vector3& GetLocalVel() { 
		DirectX::SimpleMath::Quaternion q;
		m_dir.Conjugate(q);
		return DirectX::SimpleMath::Vector3::Transform(m_vel, q); 
	}
	DirectX::SimpleMath::Vector3& GetAccel() { return m_accel; }
	DirectX::SimpleMath::Vector3& GetPos() { return m_pos; }
	float& GetRadius() { return m_radius; }
	DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	DirectX::SimpleMath::Matrix& GetLocal() { return m_local; }

private:
	DirectX::SimpleMath::Quaternion m_dir;		// 方向			
	DirectX::SimpleMath::Vector3 m_vel;			// 速度
	DirectX::SimpleMath::Vector3 m_accel;		// 加速度
	DirectX::SimpleMath::Vector3 m_pos;			// 座標
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
	void SetName(char* name) { m_name = name; }
	void SetTag(Tag tag) { m_tag = tag; }
	void SetParent(Entity* parent) { m_parent = parent; }

	// ゲッター
	char* GetName() { return m_name; }
	Tag GetTag() { return m_tag; }
	Transform& GetTrans() { return m_transform; }
	Entity& GetParent() { return *m_parent; }
	std::list<Entity*>* GetChildList() { return &m_childlist; }
	OBJECT_FOR_TREE* GetOFT() { return m_pOFT; }
	EntityOfTree* GetEOF() { return m_pEOF; }

private:
	char* m_name;								// 名前
	Tag m_tag;									// タグ
	Transform m_transform;						// 変形の情報

	Entity* m_parent;							// 親のポインタ

	std::list<Entity*> m_childlist;				// 子のコンテナ

	OBJECT_FOR_TREE* m_pOFT;					// 当たり判定用
	EntityOfTree* m_pEOF;						// 実体をリストで回す用
};