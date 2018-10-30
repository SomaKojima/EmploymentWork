/// <summary>
/// PhysicsComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../../pch.h"
#include "PhysicsComponent.h"
#include "../../Collision/Collision.h"

#include "../ComponentLib.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="entityVector">実体のコンテナのポインタ</param>
PhysicsComponent::PhysicsComponent()
	:
	m_gravity(9.8f),
	m_friction(Vector3(0.9f, 1.0f, 0.9f)),
	m_gravityDir(Vector3::Down),
	m_isFriction(true),
	m_isGravity(true)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PhysicsComponent::~PhysicsComponent()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="entity">実体</param>
void PhysicsComponent::Initialize()
{
	m_spherelist = m_me->GetComponentList<SphereCollisionComponent>();
	m_planelist = m_me->GetComponentList<PlaneCollisionComponent>();
	int a = 0;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
/// <param name="timer">時間</param>
void PhysicsComponent::Update(DX::StepTimer const& timer)
{
	Vector3 vel = m_me->GetTrans().GetVel();
	//Vector3 accel = m_me->GetTrans().GetAccel();

	if(m_isFriction)
	{
		vel *= m_friction;
		//accel *= m_friction;
	}
	
	if(m_isGravity)
	{
		//Quaternion inverse;
		//m_me->GetTrans().GetDir().Inverse(inverse);
		Vector3 gravity = (m_gravityDir * (m_gravity / (60 * 60)));
		Quaternion q;
		m_me->GetTrans().GetDir().Conjugate(q);
		gravity = Vector3::Transform(gravity, q);
		//gravity = Vector3::Transform(gravity, inverse);
		vel += gravity;
	}

	m_me->GetTrans().SetVel(vel);
	//_me->GetTrans().SetAccel(accel);
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="m_entity">実体</param>
/// <param name="timer">時間</param>
void PhysicsComponent::LateUpdate(DX::StepTimer const & timer)
{
}

void PhysicsComponent::OnCollide(Entity& collide, CollisionData* data)
{
	// 自分の情報を取得
	list<CollisionComponent*> collisionList1 = m_me->GetComponentList<CollisionComponent>();
	list<CollisionComponent*> collisionList2 = collide.GetComponentList<CollisionComponent>();
	CollisionComponent* collision1 = nullptr;
	CollisionComponent* collision2 = nullptr;
	for (auto ite = collisionList1.begin(); ite != collisionList1.end(); ite++)
	{
		if ((*ite)->IsHit())
		{
			collision1 = (*ite);
		}
	}
	for (auto ite2 = collisionList2.begin(); ite2 != collisionList2.end(); ite2++)
	{
		if ((*ite2)->IsHit())
		{
			collision2 = (*ite2);
		}
	}
	/// //////////////////////////////
	//跳ね返りを計算
	/// //////////////////////////////

	if (collision1 && collision2)
	{
		const Collision::Sphere* sphere;
		const Collision::Plane* plane;
		const Collision::Triangle* triangle;
		const list<Collision::Triangle>* triangleList;
		collision2->GetShape(&sphere, &plane, &triangle, &triangleList);
		collision1->HitBack(sphere, data->hitPos);
		collision1->HitBack(plane, data->hitPos);
		collision1->HitBack(triangle, data->hitPos);
		for (auto ite3 = (*triangleList).begin(); ite3 != (*triangleList).end(); ite3++)
		{
			collision1->HitBack(&(*ite3), data->hitPos);
		}
	}
}
