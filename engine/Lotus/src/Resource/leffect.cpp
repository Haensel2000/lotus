/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\leffect.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class EffectPtrComparator:                              */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
bool EffectPtrComparator::operator() (const Ptr<Effect> a, const Ptr<Effect> b)
{
	return a->getPriority() < b->getPriority();
}