/// <summary>
/// CarFactory.h
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
/// 車ファクトリクラス
/// </summary>
class CarFactory : public SingletonBase<CarFactory>
{
public:
	// コンストラクタ
	CarFactory();
	// デストラクタ
	~CarFactory();

	// 車の生成
	Entity* CreateCar();

private:
	DirectX::Model* m_carBodyModel;	// 車のモデル
	DirectX::Model* m_carCannonModel;	// 車のモデル
};