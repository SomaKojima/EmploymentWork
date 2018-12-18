/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include <fstream>

#include "../../../pch.h"
#include "MeshCollisionComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="radius">���a</param>
MeshCollisionComponent::MeshCollisionComponent(wchar_t* file)
	:
	m_file(file)
{
	// obj�`���̃t�@�C���ǂݍ���
	std::vector<Vector3> vertexes;
	std::vector<int> indexes;
	std::ifstream ifs(file);

	std::string str;
	while (getline(ifs, str))
	{
		// ���_
		if (str[0] == 'v')
		{
			Vector3 val;
			sscanf_s(str.data(), "v  %f %f %f", &val.x, &val.y, &val.z);
			vertexes.push_back(val);
		}
		// �C���f�b�N�X
		if (str[0] == 'f')
		{
			int a, b, c;
			sscanf_s(str.data(), "f %d %d %d", &a, &b, &c);
			// �O�p�`�̒��_�C���f�b�N�X�ԍ������������܂ޏꍇ�͖�������
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
/// �f�X�g���N�^
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
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void MeshCollisionComponent::Draw(Game * game)
{
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugMesh>(game->GetDevice(), m_file);
	}
	else
	{
		//m_obj->DrawCollision(game->GetContext(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
/// <param name="entity">����</param>
void MeshCollisionComponent::Finalize()
{
	m_obj.reset();
}