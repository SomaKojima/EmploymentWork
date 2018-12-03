/// <summary>
/// ModelComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
#include "ModelComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ModelComponent::ModelComponent(DirectX::Model* model, Type type) 
	: 
	m_model(model),
	m_type(type)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelComponent::~ModelComponent()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="game">�Q�[��</param>
void ModelComponent::Draw(Game * game)
{
	if (m_type == Type::Sky)
	{
		m_model->UpdateEffects([&](IEffect* effect) {
			IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
			if (lights) {
				// ���C�g�̉e�����Ȃ��� 
				lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
			}
			BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				// �G�~�b�V�����F�𔒂ɐݒ肷�� 
				basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
			}
		});
	}

	if (game)
	{
		m_model->Draw(game->GetContext(), *game->GetStates(), m_me->GetTrans().world.Get(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
void ModelComponent::Finalize()
{
	m_model = nullptr;
}
