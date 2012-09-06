/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\lglobal.h>

using namespace Lotus;

const Ptr<ZBufferState> ZBufferState::DEFAULT(new ZBufferState());

/* ------------------------------------------------------- */
/* class ZBufferState:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
ZBufferState::ZBufferState()
{
	enabled = true;
	writable = true;
	compare = CP_ALWAYS;
}
/* ------------------------------------------------------- */
void ZBufferState::load(Stream& stream)
{
	Object::load(stream);

	stream.read(enabled);
	stream.read(writable);
	stream.read(compare);
}
/* ------------------------------------------------------- */
void ZBufferState::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(enabled);
	stream.write(writable);
	stream.write(compare);
}
/* ------------------------------------------------------- */
int ZBufferState::getDiskUsed() const
{
	return Object::getDiskUsed() + sizeof(enabled) + sizeof(writable) + sizeof(compare);
}
/* ------------------------------------------------------- */
int ZBufferState::getPriority() const
{
	return NULL_PRIORITY;
}
/* ------------------------------------------------------- */
void ZBufferState::begin(Renderer* renderer)
{
	renderer->setZBufferState(this);
}
/* ------------------------------------------------------- */
void ZBufferState::end(Renderer* renderer)
{
	renderer->setZBufferState(DEFAULT.toInternal());
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class AlphaState:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
AlphaState::AlphaState()
{
	enabled = false;
	source = BL_SRCALPHA;
	destination = BL_INVSRCALPHA;
	testEnabled = false;
	test = CP_EQUAL;
	reference = 1.0f;
}
/* ------------------------------------------------------- */
void AlphaState::load(Stream& stream)
{
	Object::load(stream);

	stream.read(enabled);
	stream.read(source);
	stream.read(destination);
	stream.read(testEnabled);
	stream.read(test);
	stream.read(reference);
}
/* ------------------------------------------------------- */
void AlphaState::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(enabled);
	stream.write(source);
	stream.write(destination);
	stream.write(testEnabled);
	stream.write(test);
	stream.write(reference);
}
/* ------------------------------------------------------- */
int AlphaState::getDiskUsed() const
{
	return	Object::getDiskUsed() + 
			sizeof(enabled) +
			sizeof(source) +
			sizeof(destination) +
			sizeof(testEnabled) +
			sizeof(test) +
			sizeof(reference);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class FogState:                                         */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
FogState::FogState()
{
	enabled = false;
	start = 0.0f;
	end = 1.0f;
	density = 1.0f;
	color = Color4(0, 0, 0, 1);
	densityFunction = FD_LINEAR;
	application = FA_PER_VERTEX;
}
/* ------------------------------------------------------- */
void FogState::load(Stream& stream)
{
	Object::load(stream);

	stream.read(enabled);
	stream.read(start);
	stream.read(end);
	stream.read(density);
	stream.read(color);
	stream.read(densityFunction);
	stream.read(application);
}
/* ------------------------------------------------------- */
void FogState::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(enabled);
	stream.write(start);
	stream.write(end);
	stream.write(density);
	stream.write(color);
	stream.write(densityFunction);
	stream.write(application);
}
/* ------------------------------------------------------- */
int FogState::getDiskUsed() const
{
	return Object::getDiskUsed() + 
			sizeof(enabled) +
			sizeof(start) +
			sizeof(end) +
			sizeof(density) +
			sizeof(color) +
			sizeof(densityFunction) +
			sizeof(application);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class CullState:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
CullState::CullState()
{
	enabled = true;
	clockwise = false;
	cullFront = false;
}
/* ------------------------------------------------------- */
void CullState::load(Stream& stream)
{
	Object::load(stream);

	stream.read(enabled);
	stream.read(clockwise);
	stream.read(cullFront);
}
/* ------------------------------------------------------- */
void CullState::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(enabled);
	stream.write(clockwise);
	stream.write(cullFront);
}
/* ------------------------------------------------------- */
int CullState::getDiskUsed() const
{
	return Object::getDiskUsed() + sizeof(enabled) + sizeof(clockwise) + sizeof(cullFront);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class WireframeState:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
WireframeState::WireframeState()
{
	enabled = true;
}
/* ------------------------------------------------------- */
void WireframeState::load(Stream& stream)
{
	Object::load(stream);

	stream.read(enabled);
}
/* ------------------------------------------------------- */
void WireframeState::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(enabled);
}
/* ------------------------------------------------------- */
int WireframeState::getDiskUsed() const
{
	return Object::getDiskUsed() + sizeof(enabled);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class ShadingState:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
ShadingState::ShadingState()
{
	mode = SM_SMOOTH;
}
/* ------------------------------------------------------- */
void ShadingState::load(Stream& stream)
{
	Object::load(stream);

	stream.read(mode);
}
/* ------------------------------------------------------- */
void ShadingState::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(mode);
}
/* ------------------------------------------------------- */
int ShadingState::getDiskUsed() const
{
	return Object::getDiskUsed() + sizeof(mode);
}
/* ------------------------------------------------------- */