/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LEFFECT_H
#define _HDR_LEFFECT_H

#include <scenegraph\lsgbase.h>

namespace Lotus
{

	class Renderer;

	class Effect : public Object
	{
	private:
	public:
		static const int NULL_PRIORITY = 0x0FFFFFFF;
		virtual int getPriority() const = 0;
		virtual void begin(Renderer* renderer) = 0;
		virtual void end(Renderer* renderer) = 0;
	};

	class EffectPtrComparator
	{
	public:
		bool operator() (const Ptr<Effect> a, const Ptr<Effect> b);
	};
}

#endif