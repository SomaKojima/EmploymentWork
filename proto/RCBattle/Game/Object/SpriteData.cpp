#include "../../pch.h"
#include "SpriteData.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

SpriteData::SpriteData()
{
}

SpriteData::~SpriteData()
{
	m_texture.Reset();
}

void SpriteData::Create(ID3D11Device * device)
{
	// テクスチャのロード 
	CreateWICTextureFromFile(device, L"Resources\\Textures\\box.png", nullptr, m_texture.GetAddressOf());
}
