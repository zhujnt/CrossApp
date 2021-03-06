
#include "CCSTLContainer.h"
#include "basics/CAObject.h"


NS_CC_BEGIN

static std::vector<unsigned __int64> g_AllCCObjectPtrs;

void addToObjPtrSets(void* ptr)
{
	unsigned __int64 v = (unsigned __int64)ptr;
	if ( v == 0)
	{
		return;
	}

	if (!g_AllCCObjectPtrs.empty())
	{
		std::vector<unsigned __int64>::iterator it = std::lower_bound(g_AllCCObjectPtrs.begin(), g_AllCCObjectPtrs.end(), v);
		if (it != g_AllCCObjectPtrs.end())
		{
			g_AllCCObjectPtrs.insert(it, v);
			return;
		}
	}
	g_AllCCObjectPtrs.push_back(v);
}


void delToObjPtrSets(void* ptr)
{
	unsigned __int64 v = (unsigned __int64)ptr;
	if (v == 0)
	{
		return;
	}

	std::vector<unsigned __int64>::iterator it = std::lower_bound(g_AllCCObjectPtrs.begin(), g_AllCCObjectPtrs.end(), v);
	if (it != g_AllCCObjectPtrs.end())
	{
		g_AllCCObjectPtrs.erase(it);
	}
}

bool isCCObjectPtr(void* ptr)
{
	unsigned __int64 v = (unsigned __int64)ptr;
	if (v == 0)
	{
		return false;
	}
	return std::binary_search(g_AllCCObjectPtrs.begin(), g_AllCCObjectPtrs.end(), v);
}

void retainObjPtr(void* ptr)
{
	if (isCCObjectPtr(ptr))
	{
		((CAObject*)ptr)->retain();
	}
}


void releaseObjPtr(void* ptr)
{
	if (isCCObjectPtr(ptr))
	{
		((CAObject*)ptr)->release();
	}
}

NS_CC_END