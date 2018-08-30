/// <summary>
/// ModelComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "ModelComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
ModelComponent::ModelComponent(DirectX::Model* model, Type type) 
	: 
	m_model(model),
	m_type(type)
{
	m_name = "Model";
}

/// <summary>
/// デストラクタ
/// </summary>
ModelComponent::~ModelComponent()
{
}

/// <summary>
/// 初期化
/// </summary>
void ModelComponent::Initialize(Entity & entity)
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
void ModelComponent::Update(Entity & entity, DX::StepTimer const& timer)
{
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="m_entity">実体</param>
/// <param name="timer">時間</param>
void ModelComponent::LateUpdate(Entity & entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="game">ゲーム</param>
void ModelComponent::Draw(Entity & entity, Game * game)
{
	if (game)
	{
		if (m_type == Type::Sky)
		{
			m_model->UpdateEffects([&](IEffect* effect) {
				IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
				if (lights) {
					// ライトの影響をなくす 
					lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
					lights->SetLightEnabled(0, false);
					lights->SetLightEnabled(1, false);
					lights->SetLightEnabled(2, false);
				}
				BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
				if (basicEffect)
				{
					// エミッション色を白に設定する 
					basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
				}
			});
		}

		m_model->Draw(game->GetContext(), *game->GetStates(), entity.GetWorld(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// 終了
/// </summary>
void ModelComponent::Finalize(Entity & entity)
{
	m_model = nullptr;
}
