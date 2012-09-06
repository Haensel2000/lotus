/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LFFEFFECTS_H
#define _HDR_LFFEFFECTS_H

#include <resource\leffect.h>
#include <resource\ltexture.h>
#include <scenegraph\lrenderer.h>
#include <system\lpointer.h>
#include <math\lcolor.h>

namespace Lotus
{

	enum AddressMode
	{
		AM_WRAP = 1,
		AM_MIRROR = 2,
		AM_CLAMP = 3,
		AM_BORDER = 4,
		AM_MIRRORONCE = 5,
		AM_MAX
	};

	enum WrappingMode
	{
		WM_NONE = 0,
		WM_U = 1,
		WM_V = 2,
		WM_W = 3,
		WM_MAX
	};

	enum TextureFilter
	{
		TF_NONE = 0,
		TF_POINT = 1,
		TF_LINEAR = 2,
		TF_ANISOTROPIC = 3,
		TF_PYRAMIDALQUAD = 6,
		TF_GAUSSIANQUAD = 7,
		TF_MAX
	};

	enum TextureOperation
	{
		TO_DISABLE = 1,
		TO_SELECTARG1 = 2,
		TO_SELECTARG2 = 3,
		TO_MODULATE = 4,
		TO_MODULATE2X = 5,
		TO_MODULATE4X = 6,
		TO_ADD = 7,
		TO_ADDSIGNED = 8,
		TO_ADDSIGNED2X = 9,
		TO_SUBTRACT = 10,
		TO_ADDSMOOTH = 11,
		TO_BLENDDIFFUSEALPHA = 12,
		TO_BLENDTEXTUREALPHA = 13,
		TO_BLENDFACTORALPHA = 14,
		TO_BLENDTEXTUREALPHAPM = 15,
		TO_BLENDCURRENTALPHA = 16,
		TO_PREMODULATE = 17,
		TO_MODULATEALPHA_ADDCOLOR = 18,
		TO_MODULATECOLOR_ADDALPHA = 19,
		TO_MODULATEINVALPHA_ADDCOLOR = 20,
		TO_MODULATEINVCOLOR_ADDALPHA = 21,
		TO_BUMPENVMAP = 22,
		TO_BUMPENVMAPLUMINANCE = 23,
		TO_DOTPRODUCT3 = 24,
		TO_MULTIPLYADD = 25,
		TO_LERP = 26,
		TO_MAX
	};

	enum TextureArgument
	{
		TA_CONSTANT,
		TA_CURRENT,
		TA_DIFFUSE,
		TA_SPECULAR,
		TA_TEMP,
		TA_TEXTURE,
		TA_TFACTOR,
		TA_MAX
	};

	class TextureLayer
	{
	private:
		AddressMode m_addressMode;	
		TextureFilter m_min;
		TextureFilter m_mag;
		TextureFilter m_mip;
		WrappingMode m_wrappingMode;
		TextureArgument m_color, m_alpha;
		TextureOperation m_colorOperation, m_alphaOperation;

		Ptr<Texture> m_texture;
		Color4 m_constantColor;
		Color4 m_borderColor;
	public:
		TextureLayer();
		TextureLayer(Ptr<Texture>&		texture,						TextureOperation colorOperation = TO_MODULATE,			
					 TextureOperation	alphaOperation  = TO_DISABLE,	TextureArgument	 color			= TA_TEXTURE,
					 TextureArgument	alpha			= TA_TEXTURE,	AddressMode		 addressMode	= AM_WRAP,
					 TextureFilter		min				= TF_LINEAR,	TextureFilter	 mag			= TF_LINEAR,
					 TextureFilter		mip				= TF_LINEAR,	WrappingMode		wmode			= WM_NONE);

		void setConstantColor(const Color4& color);
		const Color4& getConstantColor() const;
		void setBorderColor(const Color4& color);
		const Color4& getBorderColor() const;
		void setTexture(Ptr<Texture>& texture);
		const Ptr<Texture>& getTexture() const;

		AddressMode getAddressMode() const;
		TextureFilter getMinificationFilter() const;
		TextureFilter getMagnificationFilter() const;
		TextureFilter getMipmapFilter() const;
		WrappingMode getWrappingMode() const;
		TextureArgument getColorArgument() const;
		TextureArgument getAlphaArgument() const;
		TextureOperation getColorOperation() const;
		TextureOperation getAlphaOperation() const;
		
		void load(Stream& stream);
		void link(PtrLinker& linker);
		void save(Stream& stream) const;
		int getDiskUsed() const;
		bool fowardAll(Fowarder& c);
	};

	class TextureEffect : public Effect
	{
	private:
		TextureLayer* m_layers[TextureDeclaration::MAX_TEXCOOR];
		unsigned int m_layerCount;

		TextureArgument m_base;
	public:
		static const int PRIORITY = 256;

		TextureEffect(TextureArgument base = TA_DIFFUSE);
		~TextureEffect();

		virtual void load(Stream& stream);
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);

		void addLayer(TextureLayer* layer);
		unsigned int getLayerCount() const;
		const TextureLayer* getLayer(unsigned int index) const;
		TextureArgument getBaseArgument() const;

		int getPriority() const;
		void begin(Renderer* renderer);
		void end(Renderer* renderer);
	};

	class MaterialEffect : public Effect
	{
	public:
		static const int PRIORITY = 255;

		Color4 ambient;
		Color4 diffuse;
		Color4 specular;
		Color4 emissive;
		float power;

		MaterialEffect();
	
		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		int getPriority() const;
		void begin(Renderer* renderer);
		void end(Renderer* renderer);
	};

}

#endif