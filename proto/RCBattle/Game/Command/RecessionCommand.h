/// <summary>
/// RecessionCommand.h
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
class RecessionCommand : public Command
{
public:
	// コンストラクタ
	RecessionCommand();
	// デストラクタ
	~RecessionCommand();

	// 実行
	void Excute(Entity& entity) override;
};