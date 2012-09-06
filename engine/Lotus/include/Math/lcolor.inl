/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class TColor3:                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class Re> TColor3<Re>::TColor3(Re r, Re g, Re b)
: TTuple3<Re>(r, g, b)
{
}
/* ------------------------------------------------------- */
template <class Re> TColor3<Re>::TColor3(const Re* rgb)
: TTuple3<Re>(rgb)
{
}
/* ------------------------------------------------------- */
template <class Re> TColor3<Re>::TColor3(const TColor3<Re>& color)
: TTuple3<Re>(color)
{
}
/* ------------------------------------------------------- */
template <class Re> Re TColor3<Re>::R() const
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class Re> Re& TColor3<Re>::R()
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class Re> Re TColor3<Re>::G() const
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class Re> Re& TColor3<Re>::G()
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class Re> Re TColor3<Re>::B() const
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class Re> Re& TColor3<Re>::B()
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class Re> TColor3<Re> TColor3<Re>::operator*(const TColor3& color) const
{
	return TColor3( m_tuple[0] * color.m_tuple[0],
					  m_tuple[1] * color.m_tuple[1],
					  m_tuple[2] * color.m_tuple[2] );
}
/* ------------------------------------------------------- */
template <class Re> void TColor3<Re>::clamp()
{
	if (m_tuple[0] < 0)
		m_tuple[0] = 0;
	if (m_tuple[1] < 0)
		m_tuple[1] = 0;
	if (m_tuple[2] < 0)
		m_tuple[2] = 0;
	if (m_tuple[0] > 1)
		m_tuple[0] = 1;
	if (m_tuple[1] > 1)
		m_tuple[1] = 1;
	if (m_tuple[2] > 1)
		m_tuple[2] = 1;
}
/* ------------------------------------------------------- */
template <class Re> void TColor3<Re>::scaleByMax()
{
	Re max = (m_tuple[0] > m_tuple[1]) ? 
		((m_tuple[0] > m_tuple[2]) ? m_tuple[0] : m_tuple[2]) :
		((m_tuple[1] > m_tuple[2]) ? m_tuple[1] : m_tuple[2]);
	operator/=(max);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TColor4:                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class Re> TColor4<Re>::TColor4(Re r, Re g, Re b, Re a)
: TTuple4<Re>(r, g, b, a)
{
}
/* ------------------------------------------------------- */
template <class Re> TColor4<Re>::TColor4(const Re* rgb)
: TTuple4<Re>(rgb)
{
}
/* ------------------------------------------------------- */
template <class Re> TColor4<Re>::TColor4(const TColor4<Re>& color)
: TTuple4<Re>(color)
{
}
/* ------------------------------------------------------- */
template <class Re> Re TColor4<Re>::R() const
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class Re> Re& TColor4<Re>::R()
{
	return m_tuple[0];
}
/* ------------------------------------------------------- */
template <class Re> Re TColor4<Re>::G() const
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class Re> Re& TColor4<Re>::G()
{
	return m_tuple[1];
}
/* ------------------------------------------------------- */
template <class Re> Re TColor4<Re>::B() const
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class Re> Re& TColor4<Re>::B()
{
	return m_tuple[2];
}
/* ------------------------------------------------------- */
template <class Re> Re TColor4<Re>::A() const
{
	return m_tuple[3];
}
/* ------------------------------------------------------- */
template <class Re> Re& TColor4<Re>::A()
{
	return m_tuple[3];
}
/* ------------------------------------------------------- */
template <class Re> TColor4<Re> TColor4<Re>::operator*(const TColor4& color) const
{
	return TColor4(   m_tuple[0] * color.m_tuple[0],
					  m_tuple[1] * color.m_tuple[1],
					  m_tuple[2] * color.m_tuple[2],
					  m_tuple[3] * color.m_tuple[3]);
}
/* ------------------------------------------------------- */
template <class Re> void TColor4<Re>::clamp()
{
	if (m_tuple[0] < 0)
		m_tuple[0] = 0;
	if (m_tuple[1] < 0)
		m_tuple[1] = 0;
	if (m_tuple[2] < 0)
		m_tuple[2] = 0;
	if (m_tuple[3] < 0)
		m_tuple[3] = 0;
	if (m_tuple[0] > 1)
		m_tuple[0] = 1;
	if (m_tuple[1] > 1)
		m_tuple[1] = 1;
	if (m_tuple[2] > 1)
		m_tuple[2] = 1;
	if (m_tuple[3] > 1)
		m_tuple[3] = 1;
}
/* ------------------------------------------------------- */
template <class Re> void TColor4<Re>::scaleByMax()
{
	Re max = (m_tuple[0] > m_tuple[1]) ? 
		((m_tuple[0] > m_tuple[2]) ? m_tuple[0] : m_tuple[2]) :
		((m_tuple[1] > m_tuple[2]) ? m_tuple[1] : m_tuple[2]);
	Re inv = ((Re)1.0)/max;
	m_tuple[0] *= inv;
	m_tuple[1] *= inv;
	m_tuple[2] *= inv;
	if (m_tuple[3] < 0)
		m_tuple[3] = 0;
	if (m_tuple[3] > 1)
		m_tuple[3] = 1;
}
/* ------------------------------------------------------- */