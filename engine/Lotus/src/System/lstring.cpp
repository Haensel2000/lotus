/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <system\lstring.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class String:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
String::String() : m_data(1)
{
	m_data[0] = '\0';
}
/* ------------------------------------------------------- */
String::String(const char* a_data)
{
	int len = strlen(a_data)+1;
	char* ch = new char[len];
	memcpy(ch, a_data, sizeof(char)*len);
	m_data = ArrayPtr<char>(ch, len);
}
/* ------------------------------------------------------- */
String::String(const String& a_string) : m_data(a_string.m_data)
{
}
/* ------------------------------------------------------- */
void String::operator=(const String& a_string)
{
	m_data = a_string.m_data;
}
/* ------------------------------------------------------- */
bool String::operator==(const String& a_string) const
{
	return (strcmp(m_data.toInternal(), a_string.m_data.toInternal()) == 0);
}
/* ------------------------------------------------------- */
bool String::operator!=(const String& a_string) const
{
	return !operator==(a_string);
}
/* ------------------------------------------------------- */
const char* String::toCharArray() const
{
	return m_data.toInternal();
}
/* ------------------------------------------------------- */
int String::length() const
{
	return m_data.size()-1;
}
/* ------------------------------------------------------- */
int String::getMemoryUsed() const
{
	return m_data.size();
}
/* ------------------------------------------------------- */
int String::getDiskUsed() const
{
	return length()+sizeof(int);
}
/* ------------------------------------------------------- */
string& String::toString() const
{
	return string(toCharArray());
}