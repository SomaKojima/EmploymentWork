/// <summary>
/// ShotCommand.h
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
/// 前方宣言
/// </summary>
class BulletFactory;

/// <summary>
/// 前進コマンドクラス
/// </summary>
class ShotCommand : public Command
{
public:
	// コンストラクタ
	ShotCommand();
	// デストラクタ
	~ShotCommand();

	// 実行
	void Excute(Entity& entity) override;

private:

	// 弾のファクトリ
	BulletFactory* m_bulletFactory;
};
