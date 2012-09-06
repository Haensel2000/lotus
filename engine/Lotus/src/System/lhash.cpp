 /****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <system\lhash.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* The predefined HashFunctions:                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
unsigned int HashFunction<char*>::operator()(const char* key)
{
	unsigned int hash = 5381;
    int c;
    while (c = *key++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}
/* ------------------------------------------------------- */
unsigned int HashFunction<string>::operator()(const string& key)
{
	return HashFunction<char*>::operator()(key.c_str());
}
/* ------------------------------------------------------- */
unsigned int HashFunction<String>::operator()(const String& key)
{
	return HashFunction<char*>::operator()(key.toCharArray());
}
/* ------------------------------------------------------- */
unsigned int HashFunction<int>::operator()(const int& key)
{
	return (unsigned int(key) >> 3) * 2654435761;
}
/* ------------------------------------------------------- */