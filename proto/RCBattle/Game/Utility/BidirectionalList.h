#pragma once

//template<class T> class RegisterTo;

template<class T,class T2> class BidirectionalList
{
public:
	BidirectionalList(T2* obj) : m_pPre(nullptr), m_pNext(nullptr), m_pRegisterTo(nullptr), m_pObj(obj) {}
	virtual ~BidirectionalList() { m_pPre = nullptr; m_pNext = nullptr; m_pRegisterTo = nullptr; m_pObj = nullptr; }

public:
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
	bool Remove();

	// getter
	T* GetPre() { return m_pPre; }
	T* GetNext() { return m_pNext; }
	RegisterTo* GetRegisterTo() { return m_pRegisterTo; }
	T2* GetObj() { return m_pObj; }

	// setter
	void SetPre(T* bl) { m_pPre = bl; }
	void SetNext(T* bl) { m_pNext = bl; }
	void SetRegisterTo(RegisterTo* registerTo) { m_pRegisterTo = registerTo; }

protected:
	T* m_pPre;
	T* m_pNext;

	RegisterTo* m_pRegisterTo;

	T2* m_pObj;
};

template<class T,class T2>
inline bool BidirectionalList<T, T2>::Remove()
{
	// “o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡
	if (!m_pRegisterTo)
	{
		return false;
	}

	if (!m_pPre)
	{
		m_pRegisterTo->SetTop(m_pNext);
	}
	else
	{
		m_pPre->SetNext(m_pNext);
	}
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
	// “ñd“o˜^–hŽ~
	if (obj->GetRegisterTo() == this)
	{
		return false;
	}

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

	// Œ»Ýæ“ª‚ÌOFT‚ð•Ï‚¦‚é
	m_pTop->SetPre(obj);
	m_pTop = obj;

	return true;
}
