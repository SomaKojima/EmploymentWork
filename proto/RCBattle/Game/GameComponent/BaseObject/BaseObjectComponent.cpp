#include "../../../pch.h"
#include "BaseObjectComponent.h"
#include "../GameComponentLib.h"
#include "../../Object/EntityVector.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

BaseObjectComponent::BaseObjectComponent()
	:
	m_normal(Vector3::Down)
{
}

BaseObjectComponent::~BaseObjectComponent()
{
}

void BaseObjectComponent::Initialize()
{
}

void BaseObjectComponent::Update(DX::StepTimer const & timer)
{
	
}

void BaseObjectComponent::LateUpdate(DX::StepTimer const & timer)
{

	if (m_current.size() != 0)
	{
		m_normal = Vector3::Zero;
		for (auto ite = m_current.begin(); ite != m_current.end(); ite++)
		{
			m_normal += (*ite);
		}
		m_normal.Normalize();
	}

	// 姿勢を合わせ
	Vector3 upDir = Vector3::Transform(Vector3::Up, m_me->GetTrans().dir.Get());
	// 回転軸計算
	Vector3 axis = upDir.Cross(-m_normal);
	if (axis != Vector3::Zero)
	{
		// 角度を求める
		float cosine = upDir.Dot(-m_normal);
		if (cosine > 1.0f)
		{
			cosine = 1.0f;
		}
		float rot = acos(cosine);
		Quaternion  Q1 = Quaternion::CreateFromAxisAngle(axis, rot);
		Quaternion r = Quaternion::Slerp(m_me->GetTrans().dir.Get(), m_me->GetTrans().dir.Get() * Q1, 0.1f);

		m_me->GetTrans().dir.Set(r);//m_me->GetTrans().GetDir() * Q1);
	}

	// 速度を取得
	Vector3 vel = m_me->GetTrans().vel.GetLocal();

	// 摩擦の計算
	float s = 0.9f;
	/*float gra = gravity.Length();
	if (2 * gra * 0.9f != 0.0f)
	{
		vel = vel / (2 * gra * 0.9f);
	}*/
	vel *= Vector3(s, 1.0f, s);

	// 重力の計算
	float grav = 9.8f;
	grav = 10.0f;
	Vector3 gravity = (m_normal * (grav / (60 * 60)));
	// 重力をプレイヤーの向きに合わせる
	Quaternion q;
	m_me->GetTrans().dir.Get().Conjugate(q);
	gravity = Vector3::Transform(gravity, q);
	// 重力を加算
	vel += gravity;


	/*if (m_me->GetTrans().GetPos().y <= 0.0f)
	{
		m_me->GetTrans().SetPos(Vector3(m_me->GetTrans().GetPos().x, 0.0f, m_me->GetTrans().GetPos().z));
		vel.y = 0.0f;
	}*/

	//m_me->GetTrans().SetAccel(accel);
	m_me->GetTrans().vel.SetLocal(vel);

	m_current.clear();
}

void BaseObjectComponent::Draw(Game * game)
{
}

void BaseObjectComponent::Finalize()
{
}

void BaseObjectComponent::OnCollide(Entity & collide, Collision::CollisionData * data)
{
	/*if (collide.GetName() == "Bullet")
	{
		m_count--;
		if (m_count < 0)
		{
			SceneManager* sceneManager = SceneManager::GetInstance();
			sceneManager->ChangeSceneID(SceneManager::SceneID::Title);
		}
	}*/
	if (collide.GetName() == "Wall")
	{
		for (auto ite = data->triangleList.begin(); ite != data->triangleList.end(); ite++)
		{
			m_current.push_back(-Vector3((*ite)->plane.a, (*ite)->plane.b, (*ite)->plane.c));
		}
		if (data->triangle) m_current.push_back(Vector3(data->triangle->plane.a, data->triangle->plane.b, data->triangle->plane.c));
	}
}
