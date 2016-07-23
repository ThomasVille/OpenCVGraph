#ifndef _DATA_H_
#define _DATA_H_
#include "BaseData.h"

template<typename T>
class Data : public BaseData
{
public:
 	Data(std::shared_ptr<T> t) : BaseData(), m_t(t) {

	}
	void Set(std::shared_ptr<T> t) {
		m_t = t;
	}
	std::shared_ptr<T> Get() {
		return m_t;
	}

protected:
	std::shared_ptr<T> m_t;
};

#endif