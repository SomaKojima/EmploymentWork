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
#include "RightCommand.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
RightCommand::RightCommand()
{
}

/// <summary>
/// デストラクタ
/// </summary>
RightCommand::~RightCommand()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="entity">実体</param>
void RightCommand::Excute(Entity & entity)
{
	Quaternion dir = Quaternion::CreateFromYawPitchRoll(XMConvertToRadians(-1.0f), 0.0f, 0.0f) * entity.GetTrans().GetDir();
	dir = Quaternion::Slerp(entity.GetTrans().GetDir(), dir, 1.0f);

	entity.GetTrans().SetDir(dir);
}
