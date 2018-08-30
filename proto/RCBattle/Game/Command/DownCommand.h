/// <summary>
/// DownCommand.h
/// 
/// 制作日:2018/7/11
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
class DownCommand : public Command
{
public:
	// コンストラクタ
	DownCommand();
	// デストラクタ
	~DownCommand();

	// 実行
	void Excute(Entity& entity) override;
};
