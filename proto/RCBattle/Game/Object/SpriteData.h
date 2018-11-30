#pragma once

#include <Model.h>
#include "../Utility/Utility.h"

class SpriteData : public SingletonBase<SpriteData>
{
public:
	SpriteData();
	~SpriteData();

	void Create(ID3D11Device* device);

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSprite() { return m_texture; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTitleBG() { return m_titleBg; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetButton() { return m_button; }

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;			// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleBg;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_button;



	/// <summary>
	/// タイトル
	/// </summary>
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTitleLogo() { return m_titleLogo; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTitleCar() { return m_titleCar; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTitleBullet() { return m_titleBullet; }
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleLogo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleCar;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleBullet;

};

