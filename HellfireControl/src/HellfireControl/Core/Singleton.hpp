#pragma once

#include <HellfireControl/Core/Common.hpp>

template<typename T>
class Singleton {
protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	static T* m_pInstance;
public:
	static T* GetInstance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new T();
		}

		return m_pInstance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

protected:
	static void DestroyInstance() {
		delete m_pInstance;
	}
};

template<typename T>
T* Singleton<T>::m_pInstance = nullptr;