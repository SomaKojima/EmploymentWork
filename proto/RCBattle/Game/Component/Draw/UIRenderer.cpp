#include <WICTextureLoader.h> 

#include "../../../pch.h"
#include "UIRenderer.h"

using namespace DirectX::SimpleMath;

UIRenderer::UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, RECT rect)
	:
	m_texture(texture),
	m_rect(rect)
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Draw(Game * game)
{
	Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().GetLocal());
	game->GetSpriteBatch()->Draw(m_texture.Get(), Vector2(pos.x, pos.y), &m_rect, Color(1.0f, 1.0f, 1.0f, 1.0f));
}

