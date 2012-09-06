/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSTRING_H
#define _HDR_LSTRING_H

#include "lsystem.h"
#include "lpointer.h"

#include <string>

namespace Lotus
{
	
	/* class String:
	 * Implements a very simple String implementation for the
	 * purpose of file streaming. If more functionality is needed
	 * use the std::string class of the standard library. */
	class String
	{
	private:
		ArrayPtr<char> m_data;
	public:
		String(); // empty string
		String(const char* a_data);
		String(const String& a_string);
		void operator=(const String& a_string);
		bool operator==(const String& a_string) const;
		bool operator!=(const String& a_string) const;

		const char* toCharArray() const;

		int length() const;
		
		int getMemoryUsed() const;
		int getDiskUsed() const;

		string& toString() const;
	};
}

#endif