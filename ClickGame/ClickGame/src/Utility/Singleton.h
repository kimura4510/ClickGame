/**
* @file Singleton.h
* @brief シングルトンテンプレート
* @author 木村哲也
* @data 2020/11/11
*/

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <cassert>
#include <mutex>

template<class T>
class Singleton final
{
public:
	static T& GetInstance()
	{
		std::call_once(IsInitFlag, Create);
		assert(Instance);
		return *Instance;
	}

private:
	static void Create()
	{
		Instance = new T;
	}

	static void Destroy()
	{
		delete Instance;
		Instance = nullptr;
	}

private:
	static std::once_flag IsInitFlag;
	static T* Instance;
};

template <class T> std::once_flag Singleton<T>::IsInitFlag;
template <class T> T* Singleton<T>::Instance = nullptr;

#endif // !SINGLETON_H_
