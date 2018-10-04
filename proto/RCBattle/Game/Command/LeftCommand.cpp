/// <summary>
/// LeftCommand.cpp
/// 
/// 制作日:2018/7/5
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "LeftCommand.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
LeftCommand::LeftCommand()
{
}

/// <summary>
/// デストラクタ
/// </summary>
LeftCommand::~LeftCommand()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="entity">実体</param>
void LeftCommand::Excute(Entity & entity)
{
	Quaternion dir = Quaternion::CreateFromYawPitchRoll(XMConvertToRadians(1.0f), 0.0f, 0.0f) * entity.GetTrans().GetDir();
	dir = Quaternion::Slerp(entity.GetTrans().GetDir(), dir, 1.0f);
	Vector3 angle = Vector3::Transform(angle, entity.GetTrans().GetDir());

	entity.GetTrans().SetDir(dir);
}
