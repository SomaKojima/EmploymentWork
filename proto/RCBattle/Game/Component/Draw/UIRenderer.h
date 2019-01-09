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
	UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, RECT rect, 
		float depth = 0.0f, DirectX::XMVECTOR color = DirectX::Colors::White);
	~UIRenderer();

	// 描画
	void Draw(Game* game) override;

	void SetRECT(RECT rect) { m_rect = rect; }
	void SetDepth(float depth) { m_depth = depth; }

	void SetTexture(ID3D11ShaderResourceView* texture) { m_texture = texture; }

	RECT GetRECT() { return m_rect; }
	float GetDepth() { return m_depth; }

	bool GetVisible() { return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

private:
	bool m_visible;
	RECT m_rect;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;			// テクスチャハンドル
	DirectX::XMVECTOR m_color;	// 色
	float m_depth;				// 深度
};