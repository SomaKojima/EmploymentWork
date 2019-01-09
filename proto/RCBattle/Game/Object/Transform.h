#pragma once

class Entity;

// 変形の情報
class Transform
{
	friend Entity;
public:
	Transform(Entity* _entity);
		
	Transform();

	~Transform();

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
		void Set(DirectX::SimpleMath::Vector3 angle) { direction = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle.y, angle.x, angle.z); }
		DirectX::SimpleMath::Quaternion Get() { return direction; }
		DirectX::SimpleMath::Quaternion GetWorld();
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
		DirectX::SimpleMath::Vector3 Get() { return m_vel; }
		DirectX::SimpleMath::Vector3 GetLocal() {
			DirectX::SimpleMath::Quaternion q;
			trans.dir.Get().Conjugate(q);
			return DirectX::SimpleMath::Vector3::Transform(m_vel, q);
		}

		void Set(DirectX::SimpleMath::Vector3 vel) { m_vel = vel; }
		void SetLocal(DirectX::SimpleMath::Vector3 vel) {
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

		DirectX::SimpleMath::Vector3 Get() { return m_pos; }

		void Set(DirectX::SimpleMath::Vector3 pos) { m_pos = pos; }
		void Set(DirectX::SimpleMath::Vector2 pos) { m_pos = DirectX::SimpleMath::Vector3(pos.x, pos.y, m_pos.z); }
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
		void Set(float radius) { m_radius = radius; }
	};

	/// <summary>
	/// ワールド行列のクラス
	/// </summary>
	class World : public TransBaseData
	{
		friend Transform;
		World(Transform& trans) : TransBaseData(trans) {}
	public:
		DirectX::SimpleMath::Matrix Get();
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
		DirectX::SimpleMath::Matrix Get() { return m_local; }
		void Set(DirectX::SimpleMath::Matrix local) {
			m_local = local;
			trans.pos.Set(m_local.Translation());
		}
	};

public:
	Entity* entity;

	Direction dir;
	Velocity vel;
	Velocity accel;		// 加速度
	Position pos;
	Radius radius;

	World world;
	Local local;
};


