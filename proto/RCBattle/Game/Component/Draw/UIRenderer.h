/// <summary>
/// ModelComponent.h
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Component.h"
#include "SpriteBatch.h"

/// <summary>
/// ���f���R���|�[�l���g�N���X
/// </summary>
class UIRenderer : public Component
{
public:
	UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, RECT rect, 
		float depth = 0.0f, DirectX::XMVECTOR color = DirectX::Colors::White);
	~UIRenderer();

	// �`��
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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;			// �e�N�X�`���n���h��
	DirectX::XMVECTOR m_color;	// �F
	float m_depth;				// �[�x
};