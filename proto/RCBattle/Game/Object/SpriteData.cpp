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
	m_titleBg.Reset();
	m_button.Reset();
	m_titleLogo.Reset();
}

void SpriteData::Create(ID3D11Device * device)
{
	// テクスチャのロード 
	CreateWICTextureFromFile(device, L"Resources\\Textures\\box.png", nullptr, m_texture.GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\bg.png", nullptr, m_titleBg.GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\button.png", nullptr, m_button.GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\title.png", nullptr, m_titleLogo.GetAddressOf());
}
