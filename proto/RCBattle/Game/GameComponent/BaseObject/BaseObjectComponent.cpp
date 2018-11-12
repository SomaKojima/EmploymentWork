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
		                                        
		// p¨‚ğ‡‚í‚¹
		Vector3 upDir = Vector3::Transform(Vector3::Up, m_me->GetTrans().GetDir());

		// ‰ñ“]²ŒvZ
		Vector3 axis = upDir.Cross(-m_normal);
		if (axis != Vector3::Zero)
		{
			// Šp“x‚ğ‹‚ß‚é
			float rot = acos(upDir.Dot(-m_normal));
			Quaternion Q1 = Quaternion::CreateFromAxisAngle(axis, rot);

			Quaternion Q2 = m_me->GetTrans().GetDir() * Q1;

			m_me->GetTrans().SetDir(m_me->GetTrans().GetDir() * Q1);
		}

		//// p¨‚ğ‡‚í‚¹
		//Vector3 upDir = Vector3::Transform(Vector3::Up, m_me->GetTrans().GetDir());
		//// ‰ñ“]²ŒvZ
		//Vector3 axis = upDir.Cross(-m_normal);
		//if (axis != Vector3::Zero)
		//{
		//	// Šp“x‚ğ‹‚ß‚é
		//	float rot = acos(upDir.Dot(-m_normal));
		//	Quaternion Q1 = Quaternion::CreateFromAxisAngle(axis, rot);

		//	Quaternion Q2 = m_me->GetTrans().GetDir() * Q1;

		//	m_me->GetTrans().SetDir(m_me->GetTrans().GetDir() * Q1);
		//}
	}
	// ‘¬“x‚ğæ“¾
	Vector3 vel = m_me->GetTrans().GetVel();

	// –€C‚ÌŒvZ
	vel *= Vector3(0.9f, 1.0f, 0.9f);

	// d—Í‚ÌŒvZ
	Vector3 gravity = (m_normal * (9.8f / (60 * 60)));
	Quaternion q;
	m_me->GetTrans().GetDir().Conjugate(q);
	gravity = Vector3::Transform(gravity, q);
	vel += gravity;

	//m_me->GetTrans().SetAccel(accel);
	m_me->GetTrans().SetVel(vel);

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
	if (collide.GetName() == "Wall")
	{
		for (auto ite = data->triangleList.begin(); ite != data->triangleList.end(); ite++)
		{
			m_current.push_back(-Vector3((*ite)->plane.a, (*ite)->plane.b, (*ite)->plane.c));
		}
		if (data->triangle) m_current.push_back(Vector3(data->triangle->plane.a, data->triangle->plane.b, data->triangle->plane.c));
	}
}
