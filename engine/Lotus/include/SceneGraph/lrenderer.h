/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LRENDERER_H
#define _HDR_LRENDERER_H

#include <math\lcolor.h>
#include <math\lvector.h>
#include <math\lmatrix.h>
#include <Resource\leffect.h>
#include <Resource\ltexture.h>
#include <scenegraph\lbatch.h>
#include <scenegraph\lscenegraph.h>

namespace Lotus
{
	class Camera;
	class Spatial;
	class VertexData;
	class Geometry;

	class ZBufferState;
	class TextureEffect;
	class MaterialEffect;
	class Light;
	
	
	struct RenderTreeNode
	{
		Ptr<Effect> effect;
		RenderTreeNode* parent; 
		List<RenderTreeNode*> children;
	};

	struct RenderTreeLeaf : public RenderTreeNode
	{	
		List<GeometryBatch*> batches;
	};	

	class RenderTree
	{
	private:
		RenderTreeNode* m_root;
		Renderer* m_renderer;

		class EffectEquality
		{
		public:
			Ptr<Effect> effect;
			bool operator() (RenderTreeNode* obj);
		};

		Ptr<GeometryData>& registerObject(Ptr<GeometryData>& data, RenderTreeLeaf* leaf);

		void recDraw(RenderTreeNode* node);
		void recDelete(RenderTreeNode* node);
		void recCommit(RenderTreeNode* node);
		void recUpdate(RenderTreeNode* node);
	public:
		RenderTree(Renderer* renderer);
		~RenderTree();

		// if the GeometryData is already registered this method returns the registered object and data else
		Ptr<GeometryData>& add(Ptr<GeometryData>& data);
		
		void render();
		void commit();
		void update();
		

	};
	
	/* class Renderer
	 * This class provides an abstract layer for a renderer that encapsulates Graphic API 
	 * services */
	class Renderer
	{
	protected:

		int m_width, m_height;
		Ptr<Camera> m_camera;
		Color3 m_backgroundColor;
		int m_currentFont;

		int m_maxLights;
		int m_maxTextures;

		RenderTree* m_renderTree;
		SceneGraph* m_sceneGraph;

		Renderer();	

		virtual bool beginScene();
		virtual void endScene();
	public:
		virtual ~Renderer();

		virtual void initialize();

		void setSceneGraph(SceneGraph* sgraph);

		virtual GeometryBatch* createGeometryBatch(BatchType type) = 0;

		int getWidth() const;
		int getHeight() const;

		void setCamera(Ptr<Camera>& camera);
		Ptr<Camera>& getCamera();

		virtual void setBackgroundColor(const Color3& color);
		const Color3& getBackgroundColor() const;

		virtual void clearBuffers() = 0;
		virtual void displayBackBuffer() = 0;

		virtual void setProjectionFoV(float fovVer, float aspect, float min, float max) = 0;
		virtual void setProjection(float width, float height, float min, float max) = 0;
		virtual void setView(const Vector3& eye, const Vector3& dir, const Vector3& up) = 0;
		virtual void setWorldMatrix(const Matrix4& world) = 0;

		virtual void setZBufferState(const ZBufferState* state) = 0;

		virtual void setTextureEffect(const TextureEffect* effect) = 0;
		virtual void setMaterialEffect(const MaterialEffect* effect) = 0;

		virtual void activateLight(Light* light) = 0;
		virtual void deactivateLight(Light* light) = 0;

		virtual Ptr<Texture> createTexture(const char* filepath) = 0;
		


		/*virtual int loadFont(const char* face, int size, bool bold, bool italic) = 0;
		virtual void unloadFont(int fontID) = 0;
		virtual bool selectFont(int fontID) = 0;
		virtual void draw(int x, int y, const Color4& color, const char* text) = 0;

		virtual void clearBackBuffer() = 0;
		virtual void clearZBuffer() = 0;
		virtual void clearStencilBuffer() = 0;
		
		
		virtual void clearBackBuffer(int x, int y, int width, int height) = 0;
		virtual void clearZBuffer(int x, int y, int width, int height) = 0;
		virtual void clearStencilBuffer(int x, int y, int width, int height) = 0;
		virtual void clearBuffers(int x, int y, int width, int height) = 0;*/

		int getMaxLights() const;
		int getMaxTextures() const;

		

		/* A subclass of Renderer has to implement a certain optimization strategy:
		 * A scenegraph contains several top level objects. Some of them are "subscenegraphs"
		 * that represent an object in the scene. Think of a human-model for example. It consists
		 * of more than only one Geometry object and has therefore to be organized in a scenegraph.
		 * One scenegraph is the "current" scenegraph and encodes the scene that has to be rendered.
		 * The engine supports runtime insertion of subgraphs into this current scenegraph. To ensure
		 * efficient organization of the vertexdata, it has to be "registered" with the add method.
		 * For convenience a whole subgraph can be registered. Such a subgraph is then called "assembled".
		 * All registered VertexData object can be rendered, but if a new VertexObject is introduced
		 * the Renderer may have to reorganize his data. This can be a computational intensive operation.
		 * Thus the common procedure would be to register all VertexData object that are in subgraphs that
		 * represent models. Then only add that subgraphs to the current graph. The Scenegraph class
		 * supports that operations */
		Ptr<GeometryData>& add(Ptr<GeometryData>& data);
		inline void commit(); // can be very computational intensive
		inline void update();
		void drawScene(double time);

		//virtual void setTexture(Ptr<Texture>& texture, int stage) = 0;

	};

	

}

#endif