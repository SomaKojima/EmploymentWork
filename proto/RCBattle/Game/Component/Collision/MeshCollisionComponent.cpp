/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// 制作日:2018/7/4
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <fstream>

#include "../../../pch.h"
#include "MeshCollisionComponent.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="center">中心座標</param>
/// <param name="radius">半径</param>
MeshCollisionComponent::MeshCollisionComponent(wchar_t* file)
	:
	m_file(file)
{
	// obj形式のファイル読み込み
	std::vector<Vector3> vertexes;
	std::vector<int> indexes;
	std::ifstream ifs(file);

	std::string str;
	while (getline(ifs, str))
	{
		// 頂点
		if (str[0] == 'v')
		{
			Vector3 val;
			sscanf_s(str.data(), "v  %f %f %f", &val.x, &val.y, &val.z);
			vertexes.push_back(val);
		}
		// インデックス
		if (str[0] == 'f')
		{
			int a, b, c;
			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);
			// 三角形の頂点インデックス番号が同じ物を含む場合は無視する
			if (a != b && a != c && b != c)
			{
				indexes.push_back(a - 1);
				indexes.push_back(c - 1);
				indexes.push_back(b - 1);
			}
		}
	}
	ifs.close();

	for (size_t i = 0; i < indexes.size() / 3; i++)
	{
		Collision::Triangle triangle;
		triangle.Set_Triangle(vertexes[indexes[i * 3 + 2]], vertexes[indexes[i * 3 + 1]], vertexes[indexes[i * 3]]);
		m_triangles.push_back(Collision::Triangle(triangle));
	}
}

/// <summary>
/// デストラクタ
/// </summary>
MeshCollisionComponent::~MeshCollisionComponent()
{
}

void MeshCollisionComponent::Update(DX::StepTimer const & timer)
{
	CollisionComponent::Update(timer);
	/*for (auto ite = m_triangles.begin(); ite != m_triangles.end(); ite++)
	{
		Quaternion dir = m_me->GetTrans().dir.Get() * ;
		Vector3 pos = m_me->GetTrans().pos.Get();

		Matrix world = Matrix::CreateFromQuaternion(dir) * Matrix::CreateTranslation(pos);

		(*ite).Set_Triangle(world, dir);
	}*/
}

void MeshCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="entity">実体</param>
/// <param name="game">ゲーム</param>
void MeshCollisionComponent::Draw(Game * game)
{
	if (m_obj == nullptr)
	{
		// デバッグ用当たり判定モデルの作成
		m_obj = std::make_unique<DebugMesh>(game->GetDevice(), m_file);
	}
	else
	{
		//m_obj->DrawCollision(game->GetContext(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// 終了
/// </summary>
/// <param name="entity">実体</param>
void MeshCollisionComponent::Finalize()
{
	m_obj.reset();
}