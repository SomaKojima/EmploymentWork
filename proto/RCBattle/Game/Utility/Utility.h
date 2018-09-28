#pragma once

namespace Utility
{
	template<class T> void Climp(T& value, T min, T max)
	{
		if (value < min)
		{
			value = min;
		}
		else if (value > max)
		{
			value = max;
		}
	}
}

template<class T> class SingletonBase
{
protected:
	SingletonBase() {}
	virtual ~SingletonBase() {}

public:
	static T* GetInstance()
	{
		static T singleton;
		return &singleton;
	}
};

void A(int value)
{
	static int a = value;
}
