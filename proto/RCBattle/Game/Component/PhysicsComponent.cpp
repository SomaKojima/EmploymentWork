/// <summary>
/// PhysicsComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "PhysicsComponent.h"
#include "../Collision/Collision.h"
#include "../Collision/CCell.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Component/BoxCollisionComponent.h"

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
	m_isFriction(true),
	m_isGravity(true),
	sphere(nullptr),
	box(nullptr)
{
	m_name = "Physics";
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
void PhysicsComponent::Initialize(Entity & entity)
{
	SphereCollisionComponent* buffSphere = entity.GetComponent<SphereCollisionComponent>();
	BoxCollisionComponent* buffBox = entity.GetComponent<BoxCollisionComponent>();
	if (buffSphere)
	{
		sphere = buffSphere;
	}
	if (buffBox)
	{
		box = buffBox;
	}
}

/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
/// <param name="timer">時間</param>
void PhysicsComponent::Update(Entity & entity, DX::StepTimer const& timer)
{
	Vector3 vel = entity.GetTrans().GetVel();

	if(m_isFriction)
	{
		vel.x *= 0.9f;
		vel.z *= 0.9f;
	}
	if(m_isGravity)
	{
		vel.y -= (m_gravity / (60 * 60));
	}


	Vector3 pos = Vector3::Transform(Vector3::Zero, entity.GetTrans().GetWorld()) + vel;
	if (pos.y <= 1.5f)
	{
		entity.GetTrans().SetWorld(entity.GetTrans().GetWorld() * Matrix::CreateTranslation(Vector3(0.0f, -pos.y + 1.5f, 0.0f)));
		vel.y = 0.0f;
	}

	entity.GetTrans().SetVel(vel);
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="m_entity">実体</param>
/// <param name="timer">時間</param>
void PhysicsComponent::LateUpdate(Entity & entity, DX::StepTimer const & timer)
{
	Vector3 trans = entity.GetTrans().GetTrans();

	trans += m_repulsionVel;
	entity.GetTrans().SetTrans(trans);
	m_repulsionVel = Vector3::Zero;
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void PhysicsComponent::Draw(Entity & entity, Game * game)
{
}

/// <summary>
/// 終了
/// </summary>
/// <param name="entity">実体</param>
void PhysicsComponent::Finalize(Entity & entity)
{
}

void PhysicsComponent::OnCollide(Entity& entity, Entity& collide)
{
	Collision::HitCheck(&entity, &collide, &m_repulsionVel);
}