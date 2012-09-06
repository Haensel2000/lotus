/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class Global:                                           */
/* ------------------------------------------------------- */
template <class T> T max(T a, T b)
{
	return (a>b) ? a : b;
}
/* ------------------------------------------------------- */
template <class T> T max(T a, T b, T c)
{
	return (a>b) ? ((a>c)?a:c) : ((b>c)?b:c);
}
/* ------------------------------------------------------- */
/* class Math:                                             */
/*                      STATIC                             */
/* ------------------------------------------------------- */
template <class R>
R Math<R>::ACos (R value)
{
    if ( -(R)1.0 < value )
    {
        if ( value < (R)1.0 )
            return (R)acos((double)value);
        else
            return (R)0.0;
    }
    else
    {
        return PI;
    }
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::ASin (R value)
{
    if ( -(R)1.0 < value )
    {
        if ( value < (R)1.0 )
            return (R)asin((double)value);
        else
            return HALF_PI;
    }
    else
    {
        return -HALF_PI;
    }
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::ATan (R value)
{
    return (R)atan((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::ATan2 (R x, R y)
{
    return (R)atan2((double)y,(double)x);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Ceil (R value)
{
    return (R)ceil((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Cos (R value)
{
    return (R)cos((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Exp (R value)
{
    return (R)exp((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FAbs (R value)
{
    return (R)fabs((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Floor (R value)
{
    return (R)floor((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FMod (R x, R y)
{
    return (R)fmod((double)x,(double)y);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::InvSqrt (R value)
{
    return (R)(1.0/sqrt((double)value));
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Log (R value)
{
    return (R)log((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Pow (R base, R exponent)
{
    return (R)pow((double)base,(double)exponent);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Sin (R value)
{
    return (R)sin((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Sqr (R value)
{
    return value*value;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Sqrt (R value)
{
    return (R)sqrt((double)value);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Tan (R value)
{
    return (R)tan((double)value);
}
/* ------------------------------------------------------- */
template <class R>
int Math<R>::Sign (int value)
{
    if ( value > 0 )
        return 1;

    if ( value < 0 )
        return -1;

    return 0;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::Sign (R value)
{
    if ( value > (R)0.0 )
        return (R)1.0;

    if ( value < (R)0.0 )
        return -(R)1.0;

    return (R)0.0;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::UnitRandom (unsigned int seed )
{
    if ( seed > 0 )
        srand(seed);

    double ratio = ((double)rand())/((double)(RAND_MAX));
    return (R)ratio;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::SymmetricRandom (unsigned int seed)
{
    if ( seed > 0.0 )
        srand(seed);

    double ratio = ((double)rand())/((double)(RAND_MAX));
    return (R)(2.0*ratio - 1.0);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::IntervalRandom (R min, R max, unsigned int seed)
{
    if ( seed > 0 )
        srand(seed);

    double ratio = ((double)rand())/((double)(RAND_MAX));
    return min+(max-min)*((R)ratio);
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastSin0 (R angle)
{
    R aSqr = angle*angle;
    R result = (R)7.61e-03;
    result *= aSqr;
    result -= (R)1.6605e-01;
    result *= aSqr;
    result += (R)1.0;
    result *= angle;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastSin1 (R angle)
{
    R aSqr = angle*angle;
    R result = -(R)2.39e-08;
    result *= aSqr;
    result += (R)2.7526e-06;
    result *= aSqr;
    result -= (R)1.98409e-04;
    result *= aSqr;
    result += (R)8.3333315e-03;
    result *= aSqr;
    result -= (R)1.666666664e-01;
    result *= aSqr;
    result += (R)1.0;
    result *= angle;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastCos0 (R angle)
{
    R aSqr = angle*angle;
    R result = (R)3.705e-02;
    result *= aSqr;
    result -= (R)4.967e-01;
    result *= aSqr;
    result += (R)1.0;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastCos1 (R angle)
{
    R aSqr = angle*angle;
    R result = -(R)2.605e-07;
    result *= aSqr;
    result += (R)2.47609e-05;
    result *= aSqr;
    result -= (R)1.3888397e-03;
    result *= aSqr;
    result += (R)4.16666418e-02;
    result *= aSqr;
    result -= (R)4.999999963e-01;
    result *= aSqr;
    result += (R)1.0;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastTan0 (R angle)
{
    R aSqr = angle*angle;
    R result = (R)2.033e-01;
    result *= aSqr;
    result += (R)3.1755e-01;
    result *= aSqr;
    result += (R)1.0;
    result *= angle;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastTan1 (R angle)
{
    R aSqr = angle*angle;
    R result = (R)9.5168091e-03;
    result *= aSqr;
    result += (R)2.900525e-03;
    result *= aSqr;
    result += (R)2.45650893e-02;
    result *= aSqr;
    result += (R)5.33740603e-02;
    result *= aSqr;
    result += (R)1.333923995e-01;
    result *= aSqr;
    result += (R)3.333314036e-01;
    result *= aSqr;
    result += (R)1.0;
    result *= angle;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastInvSin0 (R value)
{
    R root = Math<R>::Sqrt(((R)1.0)-value);
    R result = -(R)0.0187293;
    result *= value;
    result += (R)0.0742610;
    result *= value;
    result -= (R)0.2121144;
    result *= value;
    result += (R)1.5707288;
    result = HALF_PI - root*result;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastInvSin1 (R value)
{
    R root = Math<R>::Sqrt(FAbs(((R)1.0)-value));
    R result = -(R)0.0012624911;
    result *= value;
    result += (R)0.0066700901;
    result *= value;
    result -= (R)0.0170881256;
    result *= value;
    result += (R)0.0308918810;
    result *= value;
    result -= (R)0.0501743046;
    result *= value;
    result += (R)0.0889789874;
    result *= value;
    result -= (R)0.2145988016;
    result *= value;
    result += (R)1.5707963050;
    result = HALF_PI - root*result;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastInvCos0 (R value)
{
    R root = Math<R>::Sqrt(((R)1.0)-value);
    R result = -(R)0.0187293;
    result *= value;
    result += (R)0.0742610;
    result *= value;
    result -= (R)0.2121144;
    result *= value;
    result += (R)1.5707288;
    result *= root;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastInvCos1 (R value)
{
    R root = Math<R>::Sqrt(FAbs(((R)1.0)-value));
    R result = -(R)0.0012624911;
    result *= value;
    result += (R)0.0066700901;
    result *= value;
    result -= (R)0.0170881256;
    result *= value;
    result += (R)0.0308918810;
    result *= value;
    result -= (R)0.0501743046;
    result *= value;
    result += (R)0.0889789874;
    result *= value;
    result -= (R)0.2145988016;
    result *= value;
    result += (R)1.5707963050;
    result *= root;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastInvTan0 (R value)
{
    R fVSqr = value*value;
    R result = (R)0.0208351;
    result *= fVSqr;
    result -= (R)0.085133;
    result *= fVSqr;
    result += (R)0.180141;
    result *= fVSqr;
    result -= (R)0.3302995;
    result *= fVSqr;
    result += (R)0.999866;
    result *= value;
    return result;
}
/* ------------------------------------------------------- */
template <class R>
R Math<R>::FastInvTan1 (R value)
{
    R fVSqr = value*value;
    R result = (R)0.0028662257;
    result *= fVSqr;
    result -= (R)0.0161657367;
    result *= fVSqr;
    result += (R)0.0429096138;
    result *= fVSqr;
    result -= (R)0.0752896400;
    result *= fVSqr;
    result += (R)0.1065626393;
    result *= fVSqr;
    result -= (R)0.1420889944;
    result *= fVSqr;
    result += (R)0.1999355085;
    result *= fVSqr;
    result -= (R)0.3333314528;
    result *= fVSqr;
    result += (R)1.0;
    result *= value;
    return result;
}
/* ------------------------------------------------------- */