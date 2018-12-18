/// <summary>
/// LeftMoveCommand.h
/// 
/// 制作日:2018/12/8
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
class LeftMoveCommand : public Command
{
public:
	// コンストラクタ
	LeftMoveCommand();
	// デストラクタ
	~LeftMoveCommand();

	// 実行
	void Excute(Entity& entity) override;
};
