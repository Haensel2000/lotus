/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LGROUP_H
#define _HDR_LGROUP_H

#include <scenegraph\lspatial.h>

namespace Lotus
{
	class Group : public Spatial
	{
	protected:
		List<Spatial*> m_children;
		
	public:
		Group();
		Group(const Group& g);
		virtual ~Group();

		virtual Spatial* copy();

		virtual void load(Stream& stream);
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);	
		virtual void updateBound();

		int childCount();
		List<Spatial*>& getChildren();
		void attach(Spatial* child);
		void detach(Spatial* child);		

		virtual void addEffect(Ptr<Effect> effect);
		virtual void removeEffect(Ptr<Effect> effect);
		virtual void addRenderPass(Ptr<RenderPass>& renderPass);
		virtual void removeRenderPass(Ptr<RenderPass>& renderPass);
		
		Group* getGroup(const String& name);
		Spatial* getChild(const String& name);
		
	};
}

#endif