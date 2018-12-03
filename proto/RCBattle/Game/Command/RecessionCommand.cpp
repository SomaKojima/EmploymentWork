/// <summary>
/// RecessionCommand.cpp
/// 
/// 制作日:2018/7/5
/// 制作日:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "RecessionCommand.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
RecessionCommand::RecessionCommand()
{
}

/// <summary>
/// デストラクタ
/// </summary>
RecessionCommand::~RecessionCommand()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="entity">実体</param>
void RecessionCommand::Excute(Entity & entity)
{
	Vector3 vel = entity.GetTrans().vel.GetLocal();
	vel.z -= 0.1f;
	if (vel.z <= -0.2f)
	{
		vel.z = -0.2f;
	}
	entity.GetTrans().vel.SetLocal(vel);
}
