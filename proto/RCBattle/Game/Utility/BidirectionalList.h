#pragma once

template<class T> class RegisterTo;

template<class T2> class BidirectionalList
{
public:
	BidirectionalList(T2* obj) : m_pPre(nullptr), m_pNext(nullptr), m_pRegisterTo(nullptr) , m_pObj(obj){}
	virtual ~BidirectionalList() { m_pPre = nullptr; m_pNext = nullptr; m_pRegisterTo = nullptr; m_pObj = nullptr; }

	bool Remove();

	// getter
	BidirectionalList<T2>* GetPre() { return m_pPre; }
	BidirectionalList<T2>* GetNext() { return m_pNext; }
	RegisterTo<T2>* GetRegisterTo() { return m_pRegisterTo; }
	T2* GetObj() { return m_pObj; }

	// setter
	void SetPre(BidirectionalList<T2>* bl) { m_pPre = bl; }
	void SetNext(BidirectionalList<T2>* bl) { m_pNext = bl; }
	void SetRegisterTo(RegisterTo<T2>* registerTo) { m_pRegisterTo = registerTo; }

protected:
	BidirectionalList<T2>* m_pPre;
	BidirectionalList<T2>* m_pNext;

	RegisterTo<T2>* m_pRegisterTo;

	T2* m_pObj;
};

template<class T2>
inline bool BidirectionalList<T2>::Remove()
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
}

