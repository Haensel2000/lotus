/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\lffeffects.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class TextureLayer:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
TextureLayer::TextureLayer()
: m_colorOperation(TO_DISABLE), m_alphaOperation(TO_DISABLE), m_color(TA_CURRENT), m_alpha(TA_CURRENT),
m_addressMode(AM_WRAP), m_min(TF_LINEAR), m_mag(TF_LINEAR), m_mip(TF_LINEAR), m_wrappingMode(WM_NONE), m_texture(0)
{
}
/* ------------------------------------------------------- */
TextureLayer::TextureLayer(Ptr<Texture>& texture, TextureOperation colorOperation, TextureOperation alphaOperation,
						   TextureArgument color, TextureArgument alpha, AddressMode addressMode, TextureFilter min,
						   TextureFilter mag, TextureFilter mip, WrappingMode wmode)
	: m_colorOperation(colorOperation), m_alphaOperation(alphaOperation), m_color(color), m_alpha(alpha), m_addressMode(addressMode), m_min(min), m_mag(mag), 
	m_mip(mip), m_wrappingMode(wmode), m_texture(texture)
{
	assert((!(color == TA_TEXTURE) && !(alpha == TA_TEXTURE)) || texture);
}
/* ------------------------------------------------------- */
void TextureLayer::setConstantColor(const Color4& color)
{
	m_constantColor = color;
}
/* ------------------------------------------------------- */
const Color4& TextureLayer::getConstantColor() const
{
	return m_constantColor;
}
/* ------------------------------------------------------- */
void TextureLayer::setBorderColor(const Color4& color)
{
	m_borderColor = color;
}
/* ------------------------------------------------------- */
const Color4& TextureLayer::getBorderColor() const
{
	return m_borderColor;
}
/* ------------------------------------------------------- */
void TextureLayer::setTexture(Ptr<Texture>& texture)
{
	assert((!(m_color == TA_TEXTURE) && !(m_alpha == TA_TEXTURE)) || texture);
	m_texture = texture;
}
/* ------------------------------------------------------- */
const Ptr<Texture>& TextureLayer::getTexture() const
{
	return m_texture;
}
/* ------------------------------------------------------- */
AddressMode TextureLayer::getAddressMode() const
{
	return m_addressMode;
}
/* ------------------------------------------------------- */
TextureFilter TextureLayer::getMinificationFilter() const
{
	return m_min;
}
/* ------------------------------------------------------- */
TextureFilter TextureLayer::getMagnificationFilter() const
{
	return m_mag;
}
/* ------------------------------------------------------- */
TextureFilter TextureLayer::getMipmapFilter() const
{
	return m_mip;
}
/* ------------------------------------------------------- */
WrappingMode TextureLayer::getWrappingMode() const
{
	return m_wrappingMode;
}
/* ------------------------------------------------------- */
TextureArgument TextureLayer::getColorArgument() const
{
	return m_color;
}
/* ------------------------------------------------------- */
TextureArgument TextureLayer::getAlphaArgument() const
{
	return m_alpha;
}
/* ------------------------------------------------------- */
TextureOperation TextureLayer::getColorOperation() const
{
	return m_colorOperation;
}
/* ------------------------------------------------------- */
TextureOperation TextureLayer::getAlphaOperation() const
{
	return m_alphaOperation;
}
/* ------------------------------------------------------- */
void TextureLayer::load(Stream& stream)
{
	stream.read(m_addressMode);
	stream.read(m_min);
	stream.read(m_mag);
	stream.read(m_mip);
	stream.read(m_wrappingMode);
	stream.read(m_color);
	stream.read(m_alpha);
	stream.read(m_colorOperation);
	stream.read(m_alphaOperation);
	stream.read(m_texture);
	stream.read(m_constantColor);
	stream.read(m_borderColor);
}
/* ------------------------------------------------------- */
void TextureLayer::link(PtrLinker& linker)
{
	if (m_texture)
		linker.link(m_texture);
}
/* ------------------------------------------------------- */
void TextureLayer::save(Stream& stream) const
{
	stream.write(m_addressMode);
	stream.write(m_min);
	stream.write(m_mag);
	stream.write(m_mip);
	stream.write(m_wrappingMode);
	stream.write(m_color);
	stream.write(m_alpha);
	stream.write(m_colorOperation);
	stream.write(m_alphaOperation);
	stream.write(m_texture);
	stream.write(m_constantColor);
	stream.write(m_borderColor);
}
/* ------------------------------------------------------- */
int TextureLayer::getDiskUsed() const
{
	return sizeof(this) - sizeof(int);
}
/* ------------------------------------------------------- */
bool TextureLayer::fowardAll(Fowarder& c)
{
	return m_texture->fowardAll(c);
}
/* ------------------------------------------------------- */
/* class TextureEffect:                                    */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
TextureEffect::TextureEffect(TextureArgument base)
: m_base(base), m_layerCount(0)
{
	assert(m_base == TA_CONSTANT || m_base == TA_DIFFUSE || m_base == TA_SPECULAR);
}
/* ------------------------------------------------------- */
TextureEffect::~TextureEffect()
{
	for (unsigned int i = 0; i < m_layerCount; i++)
	{
		delete m_layers[i];
	}
}
/* ------------------------------------------------------- */
void TextureEffect::load(Stream& stream)
{
	Effect::load(stream);
	stream.read(m_layerCount);
	stream.read(m_base);
	for (unsigned int i = 0; i < m_layerCount; i++)
	{
		m_layers[i] = new TextureLayer;
		m_layers[i]->load(stream);
	}
}
/* ------------------------------------------------------- */
void TextureEffect::link(PtrLinker& linker)
{
	Effect::link(linker);
	for (unsigned int i = 0; i < m_layerCount; i++)
	{
		m_layers[i]->link(linker);
	}
}
/* ------------------------------------------------------- */
void TextureEffect::save(Stream& stream) const
{
	Effect::save(stream);
	stream.write(m_layerCount);
	stream.write(m_base);
	for (unsigned int i = 0; i < m_layerCount; i++)
	{
		m_layers[i]->save(stream);
	}
}
/* ------------------------------------------------------- */
int TextureEffect::getDiskUsed() const
{
	int sum = Effect::getDiskUsed() + sizeof(m_layerCount) + sizeof(m_base);
	for (unsigned int i = 0; i < m_layerCount; i++)
	{
		sum += m_layers[i]->getDiskUsed();
	}
	return sum;
}
/* ------------------------------------------------------- */
bool TextureEffect::fowardAll(Fowarder& c)
{
	if (Effect::fowardAll(c))
	{
		for (unsigned int i = 0; i < m_layerCount; i++)
		{
			m_layers[i]->fowardAll(c);
		}
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
void TextureEffect::addLayer(TextureLayer* layer)
{
	assert(layer);
	if (m_layerCount < TextureDeclaration::MAX_TEXCOOR)
	{
		m_layers[m_layerCount] = layer;
		m_layerCount++;
	}
}
/* ------------------------------------------------------- */
unsigned int TextureEffect::getLayerCount() const
{
	return m_layerCount;
}
/* ------------------------------------------------------- */
const TextureLayer* TextureEffect::getLayer(unsigned int index) const
{
	assert(index < m_layerCount);
	return m_layers[index];
}
/* ------------------------------------------------------- */
TextureArgument TextureEffect::getBaseArgument() const
{
	return m_base;
}
/* ------------------------------------------------------- */
int TextureEffect::getPriority() const
{
	return PRIORITY;
}
/* ------------------------------------------------------- */
void TextureEffect::begin(Renderer* renderer)
{
	renderer->setTextureEffect(this);
}
/* ------------------------------------------------------- */
void TextureEffect::end(Renderer* renderer)
{
	renderer->setTextureEffect(0);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class MaterialEffect:                                   */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
MaterialEffect::MaterialEffect()
: ambient(Color4::WHITE), diffuse(Color4::WHITE), specular(Color4::WHITE), emissive(Color4::BLACK), power(1.0f)
{
}
/* ------------------------------------------------------- */
void MaterialEffect::load(Stream& stream)
{
	Effect::load(stream);
	stream.read(ambient);
	stream.read(diffuse);
	stream.read(specular);
	stream.read(emissive);
	stream.read(power);
}
/* ------------------------------------------------------- */
void MaterialEffect::save(Stream& stream) const
{
	Effect::save(stream);
	stream.write(ambient);
	stream.write(diffuse);
	stream.write(specular);
	stream.write(emissive);
	stream.write(power);
}
/* ------------------------------------------------------- */
int MaterialEffect::getDiskUsed() const
{
	return Effect::getDiskUsed() + sizeof(Color4)*4 + sizeof(float);
}
/* ------------------------------------------------------- */
int MaterialEffect::getPriority() const
{
	return PRIORITY;
}
/* ------------------------------------------------------- */
void MaterialEffect::begin(Renderer* renderer)
{
	renderer->setMaterialEffect(this);
}
/* ------------------------------------------------------- */
void MaterialEffect::end(Renderer* renderer)
{
	renderer->setMaterialEffect(0);
}
/* ------------------------------------------------------- */