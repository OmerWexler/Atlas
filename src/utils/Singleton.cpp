#include "Singleton.h"

template <class T>
Singleton* Singleton<T>::Instance = nullptr;

template <class T>
std::once_flag Singleton<T>::initInstanceFlag;