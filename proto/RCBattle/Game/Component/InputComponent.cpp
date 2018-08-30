/// <summary>
/// InputComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "InputComponent.h"

/// <summary>
/// コンストラクタ
/// </summary>
InputComponent::InputComponent()
	:
	m_inputHandle()
{
	m_name = "Input";
}

/// <summary>
/// デストラクタ
/// </summary>
InputComponent::~InputComponent()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="entity"></param>
void InputComponent::Initialize(Entity & entity)
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
/// <param name="timer">時間</param>
void InputComponent::Update(Entity& entity, DX::StepTimer const& timer)
{
	std::vector<Command*>& command = m_inputHandle.GetInputHnadle();
	for (auto ite = command.begin(); ite != command.end(); ite++)
	{
		(*ite)->Excute(entity);
	}
}

/// <summary>
/// 遅延更新
/// </summary>
/// <param name="m_entity">実体</param>
/// <param name="timer">時間</param>
void InputComponent::LateUpdate(Entity & m_entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void InputComponent::Draw(Entity & entity, Game * game)
{
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name="entity">実体</param>
void InputComponent::Finalize(Entity & entity)
{
}
