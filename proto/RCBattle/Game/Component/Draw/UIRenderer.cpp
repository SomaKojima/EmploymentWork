#include <WICTextureLoader.h> 

#include "../../../pch.h"
#include "UIRenderer.h"

using namespace DirectX::SimpleMath;

UIRenderer::UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
	:
	m_texture(texture),
	m_rect(RECT{0, 0, 0, 0})
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Draw(Entity & entity, Game * game)
{
	Vector3 pos = Vector3::Transform(Vector3::Zero, entity.GetTrans().GetLocal());
	game->GetSpriteBatch()->Draw(m_texture.Get(), Vector2(pos.x, pos.y), &m_rect);
}

