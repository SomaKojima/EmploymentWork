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

private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;			// テクスチャハンドル
};

