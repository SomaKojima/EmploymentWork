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
	UIRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, RECT rect);
	~UIRenderer();

	// �`��
	void Draw(Game* game) override;

	void SetRECT(RECT rect) { m_rect = rect; }
	RECT GetRECT() { return m_rect; }

private:
	RECT m_rect;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;			// �e�N�X�`���n���h��
};