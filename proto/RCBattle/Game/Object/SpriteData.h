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





	/// <summary>
	/// プレイ
	/// </summary>
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetMark() { return m_mark; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetLifeOne() { return m_lifeOne; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetLifeTwo() { return m_lifeTwo; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetLifeThree() { return m_lifeThree; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetLifeBone() { return m_lifeBone; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetWinPlayer() { return m_winPlayer; }
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetWinNPC() { return m_winNPC; }


private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_mark;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_lifeOne;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_lifeTwo;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_lifeThree;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_lifeBone;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_winPlayer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_winNPC;
};

