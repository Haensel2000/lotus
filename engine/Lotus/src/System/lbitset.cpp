/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <system\lbitset.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class BitsSet :                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
BitSet::BitSet(unsigned int data)
: m_data(data)
{
}
/* ------------------------------------------------------- */
BitSet::BitSet(const BitSet& bset)
: m_data(bset.m_data)
{
}
/* ------------------------------------------------------- */
BitSet& BitSet::operator=(const BitSet& bset)
{
	m_data = bset.m_data;
	return *this;
}
/* ------------------------------------------------------- */
BitSet::operator unsigned int()
{
	return m_data;
}
/* ------------------------------------------------------- */
bool BitSet::contains(unsigned int bit) const
{
	assert(bit <= 32);
	return ((m_data & (1<<bit)) != 0);
}
/* ------------------------------------------------------- */
void BitSet::set(unsigned int bit)
{
	assert(bit <= 32);
	m_data |= (1<<bit);
}
/* ------------------------------------------------------- */
void BitSet::flip(unsigned int bit)
{
	assert(bit <= 32);
	m_data ^= (1<<bit);
}
/* ------------------------------------------------------- */
void BitSet::clear(unsigned int bit)
{
	assert(bit <= 32);
	m_data &= (0xFFFFFFFE<<bit);
}
/* ------------------------------------------------------- */
void BitSet::clear()
{
	m_data = 0;
}
/* ------------------------------------------------------- */