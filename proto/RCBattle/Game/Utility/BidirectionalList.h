#pragma once

/// <summary>
/// �g�����̗�
/// </summary>

/// <summary>
/// �o�^�����I�u�W�F�N�g�N���X�i���X�g�̗v�f�ƂȂ�N���X�j
/// </summary>
/*

class EntityOfTree : public BidirectionalList<EntityOfTree, Entity>
{
public:
	EntityOfTree(Entity* obj) : BidirectionalList(obj) {}
	~EntityOfTree() {}

};

*/

/// <summary>
/// �o�^�����̃N���X
/// </summary>
/*

class EntityList : public BidirectionalList<EntityOfTree, Entity>::RegisterTo
{
public:
	EntityList() {}
	~EntityList() {}
};

*/

/// <summary>
/// �o�^�����I�u�W�F�N�g�N���X�i���X�g�̗v�f�ƂȂ�N���X�j
/// </summary>
template<class T,class T2> class BidirectionalList
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="obj"></param>
	BidirectionalList(T2* obj) : m_pPre(nullptr), m_pNext(nullptr), m_pRegisterTo(nullptr), m_pObj(obj) { }

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BidirectionalList() { m_pPre = nullptr; m_pNext = nullptr; m_pRegisterTo = nullptr; m_pObj = nullptr; }

public:
	/// <summary>
	/// �o�^��̃N���X
	/// </summary>
	class RegisterTo
	{
	public:
		RegisterTo() : m_pTop(nullptr) {}
		virtual ~RegisterTo() {}

		bool Add(T* obj);

		void SetTop(T* top) { m_pTop = top; }
		T* GetTop() { return m_pTop; }

	protected:
		T* m_pTop;
	};

public:
	// ���X�g��̃N���X���痣���(���X�g����폜)
	bool Remove();

	// getter
	T* GetPre() { return m_pPre; }
	T* GetNext() { return m_pNext; }
	RegisterTo* GetRegisterTo() { return m_pRegisterTo; }
	T2* GetObj() { return m_pObj; }

private:
	// setter
	void SetPre(T* bl) { m_pPre = bl; }
	void SetNext(T* bl) { m_pNext = bl; }
	void SetRegisterTo(RegisterTo* registerTo) { m_pRegisterTo = registerTo; }

private:
	T* m_pPre;
	T* m_pNext;

	RegisterTo* m_pRegisterTo;

	// �o�^����Ă���I�u�W�F�N�g�̍폜
	T2* m_pObj;
};

template<class T,class T2>
inline bool BidirectionalList<T, T2>::Remove()
{
	// �o�^����Ă��Ȃ��ꍇ
	if (!m_pRegisterTo)
	{
		return false;
	}

	// �O�̃|�C���^�̏���
	if (!m_pPre)
	{
		m_pRegisterTo->SetTop(m_pNext);
	}
	else
	{
		m_pPre->SetNext(m_pNext);
	}

	// ���̃|�C���^�̏���
	if (m_pNext)
	{
		m_pNext->SetPre(m_pPre);
	}

	m_pPre = nullptr;
	m_pNext = nullptr;

	m_pRegisterTo = nullptr;
	return true;
}

template<class T,class T2>
inline bool BidirectionalList<T, T2>::RegisterTo::Add(T* obj)
{
	// ��d�o�^�h�~
	if (obj->GetRegisterTo() == this)
	{
		return false;
	}

	obj->Remove();
	if (!m_pTop)
	{
		obj->SetRegisterTo(this);
		obj->SetPre(nullptr);
		obj->SetNext(nullptr);
		m_pTop = obj;
		return true;
	}

	obj->SetRegisterTo(this);
	obj->SetPre(nullptr);
	obj->SetNext(m_pTop);

	// ���ݐ擪��OFT��ς���
	m_pTop->SetPre(obj);
	m_pTop = obj;

	return true;
}
