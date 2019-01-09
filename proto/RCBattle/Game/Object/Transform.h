#pragma once

class Entity;

// �ό`�̏��
class Transform
{
	friend Entity;
public:
	Transform(Entity* _entity);
		
	Transform();

	~Transform();

private:
	/// <summary>
	/// �f�[�^�̌��ɂȂ�N���X
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
	/// �����̃N���X
	/// </summary>
	class Direction : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Quaternion direction;		// ����		
														// �R���X�g���N�^
		Direction(Transform& trans) :direction(DirectX::SimpleMath::Quaternion::Identity), TransBaseData(trans) {}
	public:

		// �A�N�Z�T��
		void Set(DirectX::SimpleMath::Quaternion dir) { direction = dir; }
		void Set(DirectX::SimpleMath::Vector3 angle) { direction = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle.y, angle.x, angle.z); }
		DirectX::SimpleMath::Quaternion Get() { return direction; }
		DirectX::SimpleMath::Quaternion GetWorld();
	};


	/// <summary>
	/// ���x�̃N���X
	/// </summary>
	class Velocity : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Vector3 m_vel;			// ���x
													// �R���X�g���N�^
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
	/// ���W�̃N���X
	/// </summary>
	class Position : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Vector3 m_pos;			// ���W
													// �R���X�g���N�^
		Position(Transform& trans) : m_pos(DirectX::SimpleMath::Vector3::Zero), TransBaseData(trans) {}
	public:

		DirectX::SimpleMath::Vector3 Get() { return m_pos; }

		void Set(DirectX::SimpleMath::Vector3 pos) { m_pos = pos; }
		void Set(DirectX::SimpleMath::Vector2 pos) { m_pos = DirectX::SimpleMath::Vector3(pos.x, pos.y, m_pos.z); }
	};

	/// <summary>
	/// ���a�̃N���X
	/// </summary>
	class Radius : public TransBaseData
	{
		friend Transform;
		float m_radius;
		// �R���X�g���N�^
		Radius(Transform& trans) : m_radius(0.0f), TransBaseData(trans) {}
	public:

		float Get() { return m_radius; }
		void Set(float radius) { m_radius = radius; }
	};

	/// <summary>
	/// ���[���h�s��̃N���X
	/// </summary>
	class World : public TransBaseData
	{
		friend Transform;
		World(Transform& trans) : TransBaseData(trans) {}
	public:
		DirectX::SimpleMath::Matrix Get();
	};

	/// <summary>
	/// ���[�J���s��̃N���X
	/// </summary>
	class Local : public TransBaseData
	{
		friend Transform;
		DirectX::SimpleMath::Matrix m_local;		// ���[���h���W
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
	Velocity accel;		// �����x
	Position pos;
	Radius radius;

	World world;
	Local local;
};


