#include "../../pch.h"
#include "CCell.h"
#include "../Object/Entity.h"
#include "../../Game.h"
#include "Collision.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CLiner8TreeManager* CLiner8TreeManager::m_singleton = nullptr;


OBJECT_FOR_TREE::OBJECT_FOR_TREE(Entity* pObject)
	:
	BidirectionalList(pObject)
{
}

OBJECT_FOR_TREE::~OBJECT_FOR_TREE()
{
}

CCell::CCell()
{

}

CCell::~CCell()
{
}

CLiner8TreeManager::CLiner8TreeManager()
{

}

CLiner8TreeManager::~CLiner8TreeManager()
{
	for (int i = 0; i < m_dwCellNum; i++)
	{
		delete ppCellAry[i];
	}
	delete[] ppCellAry;
}

bool CLiner8TreeManager::Init(unsigned int Level, float left, float top, float right, float bottom, float front, float back)
{
	// �ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
	if (Level>CLINER8TREEMANAGER_MAXLEVEL)
		return false;

	// �e���x���ł̋�Ԑ����Z�o
	int i;
	m_iPow[0] = 1;
	for (i = 1; i <= CLINER8TREEMANAGER_MAXLEVEL + 1; i++)
	{
		m_iPow[i] = m_iPow[i - 1] * 8;
	}

	// Level���x���i0��_�j�̔z��쐬
	m_dwCellNum = (m_iPow[Level + 1] - 1) / 7;
	ppCellAry = new CCell*[m_dwCellNum];
	ZeroMemory(ppCellAry, sizeof(CCell*) * m_dwCellNum);

	// �L���̈��o�^
	m_fLeft = left;
	m_fBottom = bottom;
	m_fBack = back;
	m_fW = right - left;
	m_fH = top - bottom;
	m_fD = front - back;
	m_fUnit_W = m_fW / (1 << Level);
	m_fUnit_H = m_fH / (1 << Level);
	m_fUnit_D = m_fD / (1 << Level);

	m_level = Level;

	return true;
}

DWORD CLiner8TreeManager::BitSeparateFor3D(BYTE n)
{
	DWORD s = n;
	s = (s | s << 8) & 0x0000f00f;
	s = (s | s << 4) & 0x000c30c3;
	s = (s | s << 2) & 0x00249249;
	return s;
}

DWORD CLiner8TreeManager::Get3DMortonOrder(BYTE x, BYTE y, BYTE z)
{
	return BitSeparateFor3D(x) | BitSeparateFor3D(y) << 1 | BitSeparateFor3D(z) << 2;
}

DWORD CLiner8TreeManager::GetMortonOrderX(float x)
{
	return (DWORD)(x - m_fLeft) / ((int)((m_fLeft + m_fW) - m_fLeft) / (2 << (m_level - 1)));
}

DWORD CLiner8TreeManager::GetMortonOrderY(float y)
{
	return (DWORD)(y - m_fBottom) / ((int)((m_fBottom + m_fH) - m_fBottom) / (2 << (m_level - 1)));
}

DWORD CLiner8TreeManager::GetMortonOrderZ(float z)
{
	return (DWORD)(z - m_fBack) / ((int)((m_fBack + m_fD) - m_fBack) / (2 << (m_level - 1)));
}

DWORD CLiner8TreeManager::GetPosToMortonOrder(DirectX::SimpleMath::Vector3 pos)
{
	DWORD morton = Get3DMortonOrder((BYTE)GetMortonOrderX(pos.x), (BYTE)GetMortonOrderY(pos.y), (BYTE)GetMortonOrderZ(pos.z));
	return morton;
}

DWORD CLiner8TreeManager::Get2PointMortonOrder(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 pos2)
{
	DWORD morton = GetPosToMortonOrder(pos);
	DWORD morton2 = GetPosToMortonOrder(pos2);

	if(morton >= m_dwCellNum ||
		morton2 >= m_dwCellNum)
	{
		return 0;
	}

	DWORD buf = (DWORD)morton ^ (DWORD)morton2;

	for(int i = 0; i <= m_level; i++)
	{
		if (!buf)
		{
			return (morton >> (3 * i)) + ((m_iPow[m_level - (i + 1)] - 1) / 7);
		}
		buf = buf >> 3;
	}

	return 0;
}

bool CLiner8TreeManager::CreateNewCell(DWORD Elem)
{
	// �����̗v�f�ԍ�
	while (!ppCellAry[Elem])
	{
		// �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
		ppCellAry[Elem] = new CCell();

		ppCellAry[Elem];

		// �e��ԂɃW�����v
		Elem = (Elem - 1) >> 3;
		if (Elem >= m_dwCellNum) break;
	}
	return true;
}

bool CLiner8TreeManager::Register(Entity* entity)
{
	if (!entity)
	{
		return false;
	}
	Vector3 b = Vector3::Transform(Vector3::Zero, entity->GetTrans().GetWorld());
	Vector3 c = b;
	float radius = entity->GetTrans().GetRadius();
	b += Vector3(radius, radius * 2, radius);
	c += Vector3(-radius, 0.0f, -radius);
	DWORD elem = Get2PointMortonOrder(b, c);
/*
	Game::SetNumText(elem);
	Game::SetPosText(Vector3::Transform(Vector3::Zero, entity->GetWorld()));*/

	entity->GetOFT()->Remove();
	if (!ppCellAry[elem])
	{
		CreateNewCell(elem);
	}
	ppCellAry[elem]->Add(entity->GetOFT());

	return true;
}

bool CLiner8TreeManager::HitCheck()
{
	// ���[�g��Ԃ�������ΏI��
	if (!ppCellAry[0])
	{
		return false;
	}

	int elem = 0;
	// �����蔻��X�^�b�N���쐬
	vector<OBJECT_FOR_TREE*> cStack;

	// ���[�g��Ԃ̓����蔻��
	int a = 0;
	a = HitCheckRoom(ppCellAry[elem], elem, cStack);

	return false;
}

int CLiner8TreeManager::HitCheckRoom(CCell* room, int elem, std::vector<OBJECT_FOR_TREE*>& cStack)
{
	if (!room)
	{
		return 0;
	}
	int o = 0;

	OBJECT_FOR_TREE* pOFT = room->GetTop();
	OBJECT_FOR_TREE* pNextOFT = nullptr;
	int pushCount = 0;

	while (pOFT)
	{
		// �X�^�b�N���̃I�u�W�F�N�g�Ɠ����蔻������
		for (auto ite = cStack.begin(); ite != cStack.end(); ite++)
		{
			o++;
			if (Collision::HitCheck(pOFT->GetObj() , (*ite)->GetObj()))
			{
				pOFT->GetObj()->OnCollideComponent(*(*ite)->GetObj());
				(*ite)->GetObj()->OnCollideComponent(*pOFT->GetObj());
			}
		}
		// ������ԓ��̃I�u�W�F�N�g�Ɠ����蔻������
		// �X�^�b�N�ɒǉ�
		cStack.push_back(pOFT);
		pushCount++;

		pNextOFT = pOFT->GetNext();

		while (pNextOFT)
		{
			o++;
			if (Collision::HitCheck(pOFT->GetObj(), pNextOFT->GetObj()))
			{
				pOFT->GetObj()->OnCollideComponent(*pNextOFT->GetObj());
				pNextOFT->GetObj()->OnCollideComponent(*pOFT->GetObj());
			}
			pNextOFT = pNextOFT->GetNext();
		}
		pOFT = pOFT->GetNext();
	}

	// �q��ԂɈړ�
	elem = (elem * 8) + 1;

	// �q��Ԃ̊m�F
	for (int i = 0; i < 8; i++)
	{
		if (elem < m_dwCellNum)
		{
			if (ppCellAry[(elem + i)])
			{
				o += HitCheckRoom(ppCellAry[(elem + i)], (elem + i), cStack);
			}
		}
	}

	// �X�^�b�N����폜
	for (int i = 0; i < pushCount; i++)
	{
		cStack.pop_back();
	}

	return o;
}
