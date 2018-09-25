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
}

void PlaneCollisionComponent::Update(DX::StepTimer const & timer)
{
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
