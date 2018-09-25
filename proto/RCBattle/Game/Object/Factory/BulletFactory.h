/// <summary>
/// BulletFactory.h
/// 
/// 制作日:2018/7/13
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

#include "../../Utility/Utility.h"

/// <summary>
/// 前方宣言
/// </summary>
class Entity;

/// <summary>
/// 弾ファクトリクラス
/// </summary>
class BulletFactory : public SingletonBase<BulletFactory>
{
public:
	// コンストラクタ
	BulletFactory();
	// デストラクタ
	~BulletFactory();

	// 弾の生成
	Entity* CreateBullet();

private:
	//static BulletFactory* sBulletFactory;

	DirectX::Model* m_bulletModel;	// 弾のモデル
};
