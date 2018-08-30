#pragma once

#include <vector>
#include "../Utility/BidirectionalList.h"
#include "../Utility/RegisterTo.h"

class CCell;
class Entity;

//class OBJECT_FOR_TREE
//{
//public:
//	OBJECT_FOR_TREE(CCell *pCell, Entity* pObject);
//	~OBJECT_FOR_TREE();
//
//	bool Remove();
//
//	CCell* GetCell() { return m_pCell; }
//	Entity* GetEnity() { return m_pObject; }
//	OBJECT_FOR_TREE* GetPre() { return m_pPre; }
//	OBJECT_FOR_TREE* GetNext() { return m_pNext; }
//
//	void SetCell(CCell* cell) { m_pCell = cell; }
//	void SetEntity(Entity* entity) { m_pObject = entity; }
//	void SetPre(OBJECT_FOR_TREE* OFT) { m_pPre = OFT; }
//	void SetNext(OBJECT_FOR_TREE* OFT) { m_pNext = OFT; }
//
//private:
//	CCell *m_pCell;            // 登録されている小空間
//	Entity* m_pObject;         // 任意オブジェクトへのポインタ
//	OBJECT_FOR_TREE *m_pPre;   // 前の構造体へのポインタ
//	OBJECT_FOR_TREE *m_pNext;  // 次の構造体へのポインタ
//};

class OBJECT_FOR_TREE : public BidirectionalList<OBJECT_FOR_TREE>
{
public:
	OBJECT_FOR_TREE(CCell *pCell, Entity* pObject);
	~OBJECT_FOR_TREE();

	Entity* GetEnity() { return m_pObject; }

	void SetEntity(Entity* entity) { m_pObject = entity; }

private:
	Entity* m_pObject;         // 任意オブジェクトへのポインタ
};

//class CCell
//{
//public:
//	CCell();
//	~CCell();
//
//	bool Add(OBJECT_FOR_TREE* OFT);
//
//	OBJECT_FOR_TREE* GetOFT() { return pOFT; }
//
//	void SetOFT(OBJECT_FOR_TREE* OFT) { pOFT = OFT; }
//
//private:
//	OBJECT_FOR_TREE* pOFT;
//};

class CCell : public RegisterTo<OBJECT_FOR_TREE>
{
public:
	CCell();
	~CCell();
};

class CLiner8TreeManager
{
public:
	static const int CLINER8TREEMANAGER_MAXLEVEL = 4;

public:
	CLiner8TreeManager();
	~CLiner8TreeManager();

	bool Init(unsigned int Level, float left, float top, float right, float bottom, float front, float back);

	DWORD BitSeparateFor3D(BYTE n);
	DWORD Get3DMortonOrder(BYTE x, BYTE y, BYTE z);
	DWORD GetMortonOrderX(float x);
	DWORD GetMortonOrderY(float y);
	DWORD GetMortonOrderZ(float z);
	DWORD GetPosToMortonOrder(DirectX::SimpleMath::Vector3 pos);
	DWORD Get2PointMortonOrder(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 pos2);

	bool CreateNewCell(DWORD Elem);
	bool Register(Entity* entity);
	bool HitCheck();
	int  HitCheckRoom(CCell* room, int elem, std::vector<OBJECT_FOR_TREE*>& cStack);

	CCell** GetCCell() { return ppCellAry; }

	static CLiner8TreeManager* GetInstance() 
	{
		if (!m_singleton)
		{
			m_singleton = new CLiner8TreeManager();
		}
		return m_singleton;
	}

	static void Lost() { delete m_singleton; };

private:
	float m_fLeft;
	float m_fBottom;
	float m_fBack;
	float m_fW;
	float m_fH;
	float m_fD;
	float m_fUnit_W;
	float m_fUnit_H;
	float m_fUnit_D;
	int m_level;
	int m_iPow[CLINER8TREEMANAGER_MAXLEVEL];
	int m_dwCellNum;

	CCell** ppCellAry;

	static CLiner8TreeManager* m_singleton;
};