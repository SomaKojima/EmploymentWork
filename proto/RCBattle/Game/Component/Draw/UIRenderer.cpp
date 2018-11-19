#include <WICTextureLoader.h> 

#include "../../../pch.h"
#include "UIRenderer.h"

using namespace DirectX::SimpleMath;

UIRenderer::UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, RECT rect, DirectX::XMVECTOR color)
	:
	m_texture(texture),
	m_rect(rect),
	m_color(color)
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Draw(Game * game)
{
	Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().GetLocal());
	game->GetSpriteBatch()->Draw(m_texture.Get(), Vector2(pos.x, pos.y), &m_rect, m_color);
}

