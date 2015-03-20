#include <assert.h>

class CRefShared
{
public:

	CRefShared();
	CRefShared(const CRefShared&);

	virtual ~CRefShared()
	{
	}

	CRefShared& operator=(const CRefShared&)
	{
		return *this;
	}

	void incRef()
	{
		assert(_ref >= 0);
		++_ref;
	}

	void decRef()
	{
		assert(_ref > 0);
		if (--_ref == 0)
		{
			if (!_noDelete)
			{
				_noDelete = true;
				delete this;
			}
		}
	}

	int getRef() const
	{
		return _ref;
	}

	void setNoDelete(bool b)
	{
		_noDelete = b;
	}

private:

	int _ref;
	bool _noDelete;
};