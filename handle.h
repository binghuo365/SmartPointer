#ifndef _GC_HANDLE_H_
#define _GC_HANDLE_H_

/**
* this soruce and things is from ice
*/


template<typename T>
class CHandleBase
{
public:
	typedef T element_type;

	T* get() const
	{
		return _ptr;
	}

	T* operator->() const
	{
		if (!_ptr)
		{
			//throw Exception(__FILE__, __LINE__);
		}

		return _ptr;
	}

	T& operator*() const
	{
		if (!_ptr)
		{
			//throw Exception(__FILE__, __LINE__);
		}

		return *_ptr;
	}

	operator bool() const
	{
		return _ptr ? true : false;
	}

	void swap(CHandleBase& other)
	{
		std::swap(_ptr, other._ptr);
	}

	T* _ptr;
};

template<typename T, typename U>
inline bool operator==(const CHandleBase<T>& lhs, const CHandleBase<U>& rhs)
{
	T* l = lhs.get();
	U* r = rhs.get();
	if (l && r)
	{
		return *l == *r;
	}
	else
	{
		return !l && !r;
	}
}

template<typename T, typename U>
inline bool operator!=(const CHandleBase<T>& lhs, const CHandleBase<U>& rhs)
{
	T* l = lhs.get();
	U* r = rhs.get();
	if (l && r)
	{
		return *l != *r;
	}
	else
	{
		return l || r;
	}
}

template<typename T, typename U>
inline bool operator<(const CHandleBase<T>& lhs, const CHandleBase<U>& rhs)
{
	T* l = lhs.get();
	U* r = rhs.get();
	if (l && r)
	{
		return *l < *r;
	}
	else
	{
		return !l && r;
	}
}

template<typename T, typename U>
inline bool operator>(const CHandleBase<T>& lhs, const CHandleBase<U>& rhs)
{
	T* l = lhs.get();
	U* r = rhs.get();
	if (l && r)
	{
		return *l > *r;
	}
	else
	{
		return l && !r;
	}
}

template<typename T>
class CHandle : public CHandleBase<T>
{
public:

	CHandle(T* p = 0)
	{
		this->_ptr = p;

		if (this->_ptr)
		{
			this->_ptr->incRef();
		}
	}

	template<typename Y>
	CHandle(const CHandle<Y>& r)
	{
		this->_ptr = r._ptr;

		if (this->_ptr)
		{
			this->_ptr->incRef();
		}
	}

	CHandle(const CHandle& r)
	{
		this->_ptr = r._ptr;

		if (this->_ptr)
		{
			this->_ptr->incRef();
		}
	}

	~CHandle()
	{
		if (this->_ptr)
		{
			this->_ptr->decRef();
		}
	}

	CHandle& operator=(T* p)
	{
		if (this->_ptr != p)
		{
			if (p)
			{
				p->incRef();
			}

			T* ptr = this->_ptr;
			this->_ptr = p;

			if (ptr)
			{
				ptr->decRef();
			}
		}
		return *this;
	}

	template<typename Y>
	CHandle& operator=(const CHandle<Y>& r)
	{
		if (this->_ptr != r._ptr)
		{
			if (r._ptr)
			{
				r._ptr->incRef();
			}

			T* ptr = this->_ptr;
			this->_ptr = r._ptr;

			if (ptr)
			{
				ptr->decRef();
			}
		}
		return *this;
	}

	CHandle& operator=(const CHandle& r)
	{
		if (this->_ptr != r._ptr)
		{
			if (r._ptr)
			{
				r._ptr->incRef();
			}

			T* ptr = this->_ptr;
			this->_ptr = r._ptr;

			if (ptr)
			{
				ptr->decRef();
			}
		}
		return *this;
	}

	template<class Y>
	static CHandle dynamicCast(const CHandleBase<Y>& r)
	{
		return CHandle(dynamic_cast<T*>(r._ptr));
	}

	template<class Y>
	static CHandle dynamicCast(Y* p)
	{
		return CHandle(dynamic_cast<T*>(p));
	}
};
#endif