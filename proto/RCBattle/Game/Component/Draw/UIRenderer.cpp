#include <WICTextureLoader.h> 

#include "../../../pch.h"
#include "UIRenderer.h"

using namespace DirectX::SimpleMath;

UIRenderer::UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, RECT rect, float depth, DirectX::XMVECTOR color)
	:
	m_texture(texture),
	m_rect(rect),
	m_color(color),
	m_depth(depth)
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Draw(Game * game)
{
	Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().local.Get());

	game->GetSpriteBatch()->Draw(m_texture.Get(), Vector2(pos.x, pos.y), &m_rect, m_color,
		0.0f, Vector2::Zero, 1.0f, DirectX::SpriteEffects_None, m_depth);
}

