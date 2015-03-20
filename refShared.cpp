#include "refShared.h"

CRefShared::CRefShared() :
_ref(0),
_noDelete(false)
{
}

CRefShared::CRefShared(const CRefShared&) :
_ref(0),
_noDelete(false)
{
}
