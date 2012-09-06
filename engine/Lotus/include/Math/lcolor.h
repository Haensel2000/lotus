/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LCOLOR_H
#define _HDR_LCOLOR_H

#include "math\lvector.h"

namespace Lotus
{
	template <class Re> class TColor3 : public TTuple3<Re>
	{
	public:
		TColor3(Re r = 0, Re g = 0, Re b = 0);
		TColor3(const Re* rgb);
		TColor3(const TColor3& color);

		Re R() const;
		Re& R();
		Re G() const;
		Re& G();
		Re B() const;
		Re& B();

		TColor3 operator*(const TColor3& color) const;

		void clamp();
		void scaleByMax();

		DLL_ITEM static const TColor3 BLACK;
		DLL_ITEM static const TColor3 WHITE;
		DLL_ITEM static const TColor3 RED;
		DLL_ITEM static const TColor3 GREEN;
		DLL_ITEM static const TColor3 BLUE;
	};

	template <class Re> class TColor4 : public TTuple4<Re>
	{
	public:
		TColor4(Re r = 0, Re g = 0, Re b = 0, Re a = 0);
		TColor4(const Re* rgb);
		TColor4(const TColor4& color);

		Re R() const;
		Re& R();
		Re G() const;
		Re& G();
		Re B() const;
		Re& B();
		Re A() const;
		Re& A();

		TColor4 operator*(const TColor4& color) const;

		void clamp();
		void scaleByMax();

		DLL_ITEM static const TColor4 BLACK;
		DLL_ITEM static const TColor4 WHITE;
		DLL_ITEM static const TColor4 RED;
		DLL_ITEM static const TColor4 GREEN;
		DLL_ITEM static const TColor4 BLUE;
	};

#include "lcolor.inl"

	typedef TColor3<float> Color3f;
	typedef Color3f Color3;
	typedef TColor3<double> Color3d;

	typedef TColor4<float> Color4f;
	typedef Color4f Color4;
	typedef TColor4<double> Color4d;
}

#endif