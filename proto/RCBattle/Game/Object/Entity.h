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

//#include "Transform.h"

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
	Transform(Entity* _entity) :
		entity(_entity),
		dir(*this),
		vel(*this),
		accel(*this),
		pos(*this),
		radius(*this),
		world(*this),
		local(*this)
	{};
	Transform() :
		entity(nullptr),
		dir(*this),
		vel(*this),
		accel(*this),
		pos(*this),
		radius(*this),
		world(*this),
		local(*this)
	{};

	~Transform() {};

private:
	/// <summary>
	/// データの元になるクラス
	/// </summary>
	class TransBaseData
	{
	protected:
		Transform& trans;
		TransBaseData(Transform& _trans) :trans(_trans) {}
	public:
		virtual ~TransBaseData() { }
	};

	/// <summary>
	/// 向きのクラス
	/// </summary>
	class Direction : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Quaternion direction;		// 方向		
														// コンストラクタ
		Direction(Transform& trans) :direction(DirectX::SimpleMath::Quaternion::Identity), TransBaseData(trans) {}
	public:

		// アクセサリ
		void Set(DirectX::SimpleMath::Quaternion dir) { direction = dir; }
		void Set(DirectX::SimpleMath::Vector3 &angle) { direction = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle.y, angle.x, angle.z); }
		DirectX::SimpleMath::Quaternion& Get() { return direction; }
	};


	/// <summary>
	/// 速度のクラス
	/// </summary>
	class Velocity : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Vector3 m_vel;			// 速度
													// コンストラクタ
		Velocity(Transform& trans) :m_vel(DirectX::SimpleMath::Vector3::Zero), TransBaseData(trans) {}
	public:
		DirectX::SimpleMath::Vector3& Get() { return m_vel; }
		DirectX::SimpleMath::Vector3& GetLocal() {
			DirectX::SimpleMath::Quaternion q;
			trans.dir.Get().Conjugate(q);
			return DirectX::SimpleMath::Vector3::Transform(m_vel, q);
		}

		void Set(DirectX::SimpleMath::Vector3 &vel) { m_vel = vel; }
		void SetLocal(DirectX::SimpleMath::Vector3 &vel) {
			m_vel = DirectX::SimpleMath::Vector3::Transform(vel, trans.dir.Get());
		}
	};

	/// <summary>
	/// 座標のクラス
	/// </summary>
	class Position : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Vector3 m_pos;			// 座標
													// コンストラクタ
		Position(Transform& trans) : m_pos(DirectX::SimpleMath::Vector3::Zero), TransBaseData(trans) {}
	public:

		DirectX::SimpleMath::Vector3& Get() { return m_pos; }

		void Set(DirectX::SimpleMath::Vector3& pos) { m_pos = pos; }
	};

	/// <summary>
	/// 半径のクラス
	/// </summary>
	class Radius : public TransBaseData
	{
		friend Transform;
		float m_radius;
		// コンストラクタ
		Radius(Transform& trans) : m_radius(0.0f), TransBaseData(trans) {}
	public:

		float Get() { return m_radius; }
		void Set(float& radius) { m_radius = radius; }
	};

	/// <summary>
	/// ワールド行列のクラス
	/// </summary>
	class World : public TransBaseData
	{
		friend Transform;
		World(Transform& trans) : TransBaseData(trans) {}
	public:
		DirectX::SimpleMath::Matrix& Get() {
			if (trans.entity)
			{
				if (&trans.entity->GetParent())
				{
					return trans.local.Get() * trans.entity->GetParent().GetTrans().world.Get();
				}
			}
			return trans.local.Get();
		}
	};

	/// <summary>
	/// ローカル行列のクラス
	/// </summary>
	class Local : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Matrix m_local;		// ワールド座標
		Local(Transform& trans) : m_local(DirectX::SimpleMath::Matrix::Identity), TransBaseData(trans) {}
	public:
		DirectX::SimpleMath::Matrix& Get() { return m_local; }
		void Set(DirectX::SimpleMath::Matrix& local) {
			m_local = local;
			trans.pos.Set(m_local.Translation());
		}
	};

private:
	Entity* entity;

public:
	Direction dir;
	Velocity vel;
	Velocity accel;		// 加速度
	Position pos;
	Radius radius;

	World world;
	Local local;	
};

/// <summary>
///オブジェクトクラス 
/// </summary>
class Entity : public FunctionComponent
{
	friend Transform;
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