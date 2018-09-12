#pragma once

#include "BidirectionalList.h";

//template<class T2> class RegisterTo
//{
//public:
//	RegisterTo() : m_pTop(nullptr) {}
//	virtual ~RegisterTo() {}
//
//	bool Add(BidirectionalList<T2>* obj);
//
//	void SetTop(BidirectionalList<T2>* top) { m_pTop = top; }
//	BidirectionalList<T2>* GetTop() { return m_pTop; }
//
//protected:
//	BidirectionalList<T2>* m_pTop;
//};
//
//template<class T2>
//inline bool RegisterTo<T2>::Add(BidirectionalList<T2>* obj)
//{
//	// “ñd“o˜^–hŽ~
//	if (obj->GetRegisterTo() == this)
//	{
//		return false;
//	}
//
//	if (!m_pTop)
//	{
//		obj->SetRegisterTo(this);
//		obj->SetPre(nullptr);
//		obj->SetNext(nullptr);
//		m_pTop = obj;
//		return true;
//	}
//
//	obj->SetRegisterTo(this);
//	obj->SetPre(nullptr);
//	obj->SetNext(m_pTop);
//
//	// Œ»Ýæ“ª‚ÌOFT‚ð•Ï‚¦‚é
//	m_pTop->SetPre(obj);
//	m_pTop = obj;
//
//	return true;
//}
