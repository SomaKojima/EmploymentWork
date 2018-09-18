/// <summary>
/// ModelComponent.h
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component.h"
#include "SpriteBatch.h"

/// <summary>
/// モデルコンポーネントクラス
/// </summary>
class UIRenderer : public Component
{
public:
	UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture);
	~UIRenderer();

	// 描画
	void Draw(Entity & entity, Game* game) override;

	void SetRECT(RECT rect) { m_rect = rect; }
	RECT GetRECT() { return m_rect; }

private:
	RECT m_rect;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;			// テクスチャハンドル
};