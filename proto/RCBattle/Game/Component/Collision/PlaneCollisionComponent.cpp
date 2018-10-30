#include "../../../pch.h"
#include "PlaneCollisionComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;


PlaneCollisionComponent::PlaneCollisionComponent(Vector3 center, Vector3 angle, float width, float height)
	:
	m_center(center),
	m_angle(angle),
	m_width(width),
	m_height(height),
	m_obj(nullptr)
{
	
}

PlaneCollisionComponent::~PlaneCollisionComponent()
{
}

void PlaneCollisionComponent::Initialize()
{
	// 左上
	Vector3 pos1 = m_center;
	pos1.x -= (m_width / 2.0f);
	pos1.y += (m_height / 2.0f);

	// 右上
	Vector3 pos2 = m_center;
	pos2.x += (m_width / 2.0f);
	pos2.y += (m_height / 2.0f);

	// 左下
	Vector3 pos3 = m_center;
	pos3.x -= (m_width / 2.0f);
	pos3.y -= (m_height / 2.0f);

	// 右下
	Vector3 pos4 = m_center;
	pos4.x += (m_width / 2.0f);
	pos4.y -= (m_height / 2.0f);

	Collision::Triangle triangle;
	triangle.Set_Triangle(pos1, pos2, pos3);
	m_triangle.push_back(triangle);
	triangle.Set_Triangle(pos2, pos4, pos3);
	m_triangle.push_back(triangle);
}

void PlaneCollisionComponent::Update(DX::StepTimer const & timer)
{
	CollisionComponent::Update(timer);
	Quaternion dir = Quaternion::CreateFromYawPitchRoll(m_angle.y, m_angle.x, m_angle.z);

	dir *= m_me->GetTrans().GetDir();
	Vector3 pos = m_me->GetTrans().GetPos() + m_center;

	Matrix world = Matrix::CreateFromQuaternion(dir) * Matrix::CreateTranslation(pos);

	for (auto ite = m_triangle.begin(); ite != m_triangle.end(); ite++)
	{
		(*ite).Set_Triangle(world, dir);
	}
}

void PlaneCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
}

void PlaneCollisionComponent::Draw(Game * game)
{
	Matrix world = m_me->GetTrans().GetWorld() * Matrix::CreateTranslation(m_center);

	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugPlane>(game->GetDevice(), m_center, m_angle, m_width, m_height);
	}
	else
	{
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

void PlaneCollisionComponent::Finalize()
{
	m_obj.reset();
}
