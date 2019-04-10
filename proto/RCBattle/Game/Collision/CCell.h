#pragma once

#include <vector>
#include "../Utility/BidirectionalList.h"
#include "../Utility/Utility.h"
#include "../Data/Data.h"

class CCell;
class Entity;

class OBJECT_FOR_TREE
{
public:
	OBJECT_FOR_TREE(Entity* pObject);
	~OBJECT_FOR_TREE();

public:
	// リスト先のクラスから離れる(リストから削除)
	bool Remove();

	// getter
	OBJECT_FOR_TREE* GetPre() { return m_pPre; }
	OBJECT_FOR_TREE* GetNext() { return m_pNext; }
	CCell* GetRegisterTo() { return m_pRegisterTo; }
	OBJECT_FOR_TREE* GetObj() { return m_pObj; }
};

class CCell : public BidirectionalList<OBJECT_FOR_TREE, Entity>::RegisterTo
{
public:
	CCell();
	~CCell();
};

class CLiner8TreeManager : public SingletonBase<CLiner8TreeManager>
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
	void  HitCheckRoom(CCell* room, int elem, std::vector<OBJECT_FOR_TREE*>& cStack);

	CCell** GetCCell() { return ppCellAry; }


	void InitCollisionMatrix();
	bool GetCollisionMatrix(Tag tag1, Tag tag2);
	void SetCollisionMatrix(Tag tag1, Tag tag2, bool flag);
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

	std::vector<std::vector<bool>> m_collisionMatrix;

	//bool m_collisionMatrix[Tag::Max][Tag::Max];
};