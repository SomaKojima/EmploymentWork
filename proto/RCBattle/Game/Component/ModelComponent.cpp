/// <summary>
/// ModelComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
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
	m_name = "Model";
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelComponent::~ModelComponent()
{
}

/// <summary>
/// ������
/// </summary>
void ModelComponent::Initialize(Entity & entity)
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="entity">����</param>
void ModelComponent::Update(Entity & entity, DX::StepTimer const& timer)
{
}

/// <summary>
/// �x���X�V
/// </summary>
/// <param name="m_entity">����</param>
/// <param name="timer">����</param>
void ModelComponent::LateUpdate(Entity & entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="game">�Q�[��</param>
void ModelComponent::Draw(Entity & entity, Game * game)
{
	if (game)
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

		m_model->Draw(game->GetContext(), *game->GetStates(), entity.GetWorld(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
void ModelComponent::Finalize(Entity & entity)
{
	m_model = nullptr;
}
