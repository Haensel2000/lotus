/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LGLOBAL_H
#define _HDR_LGLOBAL_H

#include <math\lcolor.h>
#include <resource\leffect.h>
#include <scenegraph\lrenderer.h>

namespace Lotus
{

	enum Comparison
	{
		CP_NEVER,
		CP_LESS,
		CP_EQUAL,
		CP_LEQUAL,
		CP_GREATER,
		CP_NOTEQUAL,
		CP_GEQUAL,
		CP_ALWAYS,
		CP_MAX
	};

	enum Blend
	{
		BL_ZERO = 1,
		BL_ONE = 2,
		BL_SRCCOLOR = 3,
		BL_INVSRCCOLOR = 4,
		BL_SRCALPHA = 5,
		BL_INVSRCALPHA = 6,
		BL_DESTALPHA = 7,
		BL_INVDESTALPHA = 8,
		BL_DESTCOLOR = 9,
		BL_INVDESTCOLOR = 10,
		BL_SRCALPHASAT = 11,
		BL_BOTHSRCALPHA = 12,
		BL_BOTHINVSRCALPHA = 13,
		BL_BLENDFACTOR = 14,
		BL_INVBLENDFACTOR = 15,
		BL_MAX = 16
	};

	enum FogDensity
	{
		FD_LINEAR,
		FD_EXP,
		FD_EXPSQR,
		FD_MAX
	};

	enum FogApplication
	{
		FA_PER_VERTEX,
		FA_PER_PIXEL,
		FA_MAX
	};

	enum ShadeMode
	{
		SM_FLAT,
		SM_SMOOTH,
		SM_MAX
	};

	class ZBufferState : public Effect
	{
	private:
	public:
		static const Ptr<ZBufferState> DEFAULT;

		ZBufferState();
		//ZBufferState(const ZBufferState& s);
		//void operator=(const ZBufferState& s);

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		int getPriority() const;
		void begin(Renderer* renderer);
		void end(Renderer* renderer);

		bool enabled;
		bool writable;
		Comparison compare;
	};

	class AlphaState : public Effect
	{
	private:
	public:
		AlphaState();

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		bool enabled;
		Blend source, destination;
		bool testEnabled;
		Comparison test;
		float reference;
	};

	class FogState : public Effect
	{
	private:
	public:
		FogState();

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		bool enabled;
		float start;
		float end;
		float density;
		Color4 color;
		FogDensity densityFunction;
		FogApplication application;
	};

	class CullState : public Effect
	{
	public:
		CullState();

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;	

		bool enabled;
		bool clockwise;
		bool cullFront;	
	};

	class WireframeState : public Effect
	{
	public:
		WireframeState();

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		bool enabled;
	};

	class ShadingState : public Effect
	{
	public:
		ShadingState();

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;	

		ShadeMode mode;
	};
	

}

#endif