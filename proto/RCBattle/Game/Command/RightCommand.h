/// <summary>
/// RightCommand.h
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
#include "Command.h"

/// <summary>
/// 前進コマンドクラス
/// </summary>
class RightCommand : public Command
{
public:
	// コンストラクタ
	RightCommand();
	// デストラクタ
	~RightCommand();

	// 実行
	void Excute(Entity& entity) override;
};
