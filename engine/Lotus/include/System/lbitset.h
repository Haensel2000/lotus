/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LBITSET_H
#define _HDR_LBITSET_H

#include <system\lsystem.h>

namespace Lotus
{
	class BitSet
	{
	private:
		unsigned int m_data;
	public:
		BitSet(unsigned int data = 0);
		BitSet(const BitSet& bset);
		BitSet& operator=(const BitSet& bset);
		operator unsigned int();
	
		bool contains(unsigned int bit) const;
		void set(unsigned int bit);
		void flip(unsigned int bit);
		void clear(unsigned int bit);
		void clear();
	};

}

#endif