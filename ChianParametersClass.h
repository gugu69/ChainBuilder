#pragma once
#include <memory>

using namespace std;

#define REQUIRED_PARAMETER(ValueType,ValueName)\
protected:\
ValueType m_##ValueName; \
template<typename T1,typename T2 = __CLASS_NAME__ > class _##ValueName \
{\
	std::shared_ptr<T1> next;\
	std::shared_ptr<T2> last;\
public:\
	_##ValueName ( shared_ptr<T2> plast = nullptr )\
    {\
		if ( plast == nullptr )\
			plast.reset ( new T2 );\
		last = plast;\
    }\
	[[nodiscard]]\
	T1& ValueName ( ValueType value )\
	{\
		last->m_##ValueName = value;\
		if ( is_same<T1,T2>::value )\
			return (T1&)*last;\
		next.reset ( new T1 ( last ) ); \
		return *next; \
	}\
};\

#define OPTIONAL_PARAMETER(ValueType,ValueName,DefaultValue)\
protected: \
ValueType m_##ValueName = DefaultValue; \
public: \
[[nodiscard]] \
__CLASS_NAME__& ValueName ( ValueType t##ValueName) { m_##ValueName = t##ValueName; return *this; }

#define PREPARE_CLASS \
protected: \
__CLASS_NAME__ ( shared_ptr <__CLASS_NAME__> ) {} \
__CLASS_NAME__ () = default; \

