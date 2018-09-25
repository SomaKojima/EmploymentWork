/// <summary>
/// InputComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../../pch.h"
#include "InputComponent.h"

/// <summary>
/// コンストラクタ
/// </summary>
InputComponent::InputComponent()
	:
	m_inputHandle()
{
}

/// <summary>
/// デストラクタ
/// </summary>
InputComponent::~InputComponent()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="entity">実体</param>
/// <param name="timer">時間</param>
void InputComponent::Update(DX::StepTimer const& timer)
{
	std::vector<Command*>& command = m_inputHandle.GetInputHnadle();
	for (auto ite = command.begin(); ite != command.end(); ite++)
	{
		(*ite)->Excute(*m_me);
	}
}
