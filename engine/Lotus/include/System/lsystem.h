/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSYSTEM_H
#define _HDR_LSYSTEM_H

#include <cassert>
#include <cctype>
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <string>

using namespace std;

namespace Lotus
{
	/* class Exception:
	 * Basic Exception for all LotusEngine Exceptions. May be
	 * derived by more specific exceptions. */
	class Exception
	{
	private:
		const char* m_errorMsg;
	public:
		Exception(const char* errorMsg) : m_errorMsg(errorMsg)
		{}

		Exception(const string& errorMsg) : m_errorMsg(errorMsg.c_str())
		{}

		const char* getMsg()
		{
			return m_errorMsg;
		}
	};

	class VertexDataImmutableException : public Exception
	{
	public:
		VertexDataImmutableException(const char* errorMsg) : Exception(errorMsg)
		{}

		VertexDataImmutableException(const string& errorMsg) : Exception(errorMsg)
		{}
	};

	class ElementNotFoundException : public Exception
	{
	public:
		ElementNotFoundException(const char* errorMsg) : Exception(errorMsg)
		{}

		ElementNotFoundException(const string& errorMsg) : Exception(errorMsg)
		{}
	};

	class IOException : public Exception
	{
	public:
		IOException(const char* errorMsg) : Exception(errorMsg)
		{}

		IOException(const string& errorMsg) : Exception(errorMsg)
		{}
	};

	class ClassNotFoundException : public Exception
	{
	public:
		ClassNotFoundException(const char* errorMsg) : Exception(errorMsg)
		{}

		ClassNotFoundException(const string& errorMsg) : Exception(errorMsg)
		{}
	};

	class IncompatibleTypesException : public Exception
	{
	public:
		IncompatibleTypesException(const char* errorMsg) : Exception(errorMsg)
		{}

		IncompatibleTypesException(const string& errorMsg) : Exception(errorMsg)
		{}
	};

	class IllegalArgumentException : public Exception
	{
	public:
		IllegalArgumentException(const char* errorMsg) : Exception(errorMsg)
		{}

		IllegalArgumentException(const string& errorMsg) : Exception(errorMsg)
		{}
	};
}

#endif

