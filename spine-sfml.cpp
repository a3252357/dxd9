/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#define SPINE_SHORT_NAMES

#include "spine-sfml.h"

#ifndef SPINE_MESH_VERTEX_COUNT_MAX
#define SPINE_MESH_VERTEX_COUNT_MAX 1000
#endif


namespace spine {

SkeletonDrawable::SkeletonDrawable(SkeletonData *skeletonData, AnimationStateData *stateData) :
		timeScale(1),
		vertexEffect(NULL), worldVertices(), clipper() {
	Bone::setYDown(true);
	worldVertices.ensureCapacity(SPINE_MESH_VERTEX_COUNT_MAX);
	skeleton = new(__FILE__, __LINE__) Skeleton(skeletonData);
	tempUvs.ensureCapacity(16);
	tempColors.ensureCapacity(16);

	ownsAnimationStateData = stateData == 0;
	if (ownsAnimationStateData) stateData = new(__FILE__, __LINE__) AnimationStateData(skeletonData);

	state = new(__FILE__, __LINE__) AnimationState(stateData);
	quadIndices.add(0);
	quadIndices.add(1);
	quadIndices.add(2);
	quadIndices.add(2);
	quadIndices.add(3);
	quadIndices.add(0);
}

SkeletonDrawable::~SkeletonDrawable() {
	//delete vertexArray;
	if (ownsAnimationStateData) delete state->getData();
	delete state;
	delete skeleton;
}

void SkeletonDrawable::update(float deltaTime) {
	skeleton->update(deltaTime);
	state->update(deltaTime * timeScale);
	state->apply(*skeleton);
	skeleton->updateWorldTransform();
	//Update();
}
void SkeletonDrawable::Update() const
{
	//vertexArray->clear();
	//states.texture = NULL;

	// Early out if skeleton is invisible
	if (skeleton->getColor().a == 0) return;

	if (vertexEffect != NULL) vertexEffect->begin(*skeleton);

	Vertex vertex;
	Sprite *texture = NULL;
	for (unsigned i = 0; i < skeleton->getSlots().size(); ++i) {
		Slot &slot = *skeleton->getDrawOrder()[i];
		Attachment *attachment = slot.getAttachment();
		if (!attachment) continue;

		// Early out if the slot color is 0
		if (slot.getColor().a == 0) {
			clipper.clipEnd(slot);
			continue;
		}

		Vector<float> *vertices = &worldVertices;
		int verticesCount = 0;
		Vector<float> *uvs = NULL;
		Vector<unsigned short> *indices = NULL;
		int indicesCount = 0;
		Color *attachmentColor;

		if (attachment->getRTTI().isExactly(RegionAttachment::rtti)) {
			RegionAttachment *regionAttachment = (RegionAttachment *)attachment;
			attachmentColor = &regionAttachment->getColor();

			// Early out if the slot color is 0
			if (attachmentColor->a == 0) {
				clipper.clipEnd(slot);
				continue;
			}

			worldVertices.setSize(8, 0);
			regionAttachment->computeWorldVertices(slot.getBone(), worldVertices, 0, 2);
			verticesCount = 4;
			uvs = &regionAttachment->getUVs();
			indices = &quadIndices;
			indicesCount = 6;
			AtlasRegion * h = ((AtlasRegion *)regionAttachment->getRendererObject());
			AtlasPage* z=h->page;
			texture = (Sprite *)((AtlasRegion *)regionAttachment->getRendererObject())->page->getRendererObject();
			indicesCount = 6;
			IDirect3DVertexBuffer9 *VB = 0;
			D3DUtil::getD3DDev()->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX1), D3DUSAGE_WRITEONLY,
				D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &VB, 0);
			CUSTOMVERTEX1 *vertexs;
			VB->Lock(0, 0, (void**)&vertexs, 0);
			for (int h = 0; h < verticesCount; h++) {
				vertexs[h] = CUSTOMVERTEX1(worldVertices[h * 2], worldVertices[h * 2 + 1], 10.0f, uvs[0][h * 2], uvs[0][h * 2 + 1]);
			}
			//draw(texture, vertices, triangles, slot.data.blendMode);
			VB->Unlock();
			D3DUtil::getD3DDev()->SetFVF(D3DFVF_CUSTOMVERTEX);

			D3DUtil::getD3DDev()->SetStreamSource(0, VB, 0, sizeof(CUSTOMVERTEX1));

			D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			//D3DUtil::getD3DDev()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
			D3DUtil::getD3DDev()->SetTexture(0, *texture->m_animationFrame->curtexture2d->ptexture9);
			D3DUtil::getD3DDev()->DrawPrimitive(/*D3DPT_TRIANGLELIST,*/D3DPT_TRIANGLESTRIP, 0, 4);
		}
		else if (attachment->getRTTI().isExactly(MeshAttachment::rtti)) {
			MeshAttachment *mesh = (MeshAttachment *)attachment;
			attachmentColor = &mesh->getColor();

			// Early out if the slot color is 0
			//if (attachmentColor->a == 0) {
			//	clipper.clipEnd(slot);
			//	continue;
			//}
			AtlasRegion * h = ((AtlasRegion *)mesh->getRendererObject());
			AtlasPage* z = h->page;
			worldVertices.setSize(mesh->getWorldVerticesLength(), 0);
			texture = (Sprite *)((AtlasRegion *)mesh->getRendererObject())->page->getRendererObject();
			mesh->computeWorldVertices(slot, 0, mesh->getWorldVerticesLength(), worldVertices, 0, 2);
			verticesCount = mesh->getWorldVerticesLength() >> 1;
			uvs = &mesh->getUVs();
			indices = &mesh->getTriangles();
			indicesCount = mesh->getTriangles().size();

			//
			// We are going to fill the empty mesh with the geometry of a box,
			// so we need 12 triangles and 24 vetices.
			//
			ID3DXMesh*         Mesh = 0;
			D3DXCreateMeshFVF(
				verticesCount,
				indicesCount/3,
				D3DXMESH_MANAGED,
				D3DFVF_CUSTOMVERTEX,
				D3DUtil::getD3DDev(),
				&Mesh);
			CUSTOMVERTEX1 *v = 0;
			Mesh->LockVertexBuffer(0, (void**)&v);
			for (int h = 0; h < verticesCount;h++) {
			
				v[h] = CUSTOMVERTEX1(worldVertices[h*2], worldVertices[h*2+1], 10.0f, uvs[0][h*2], uvs[0][h * 2+1]);
			}
			Mesh->UnlockVertexBuffer();
			WORD* IndexBuffer = 0;
			
			Mesh->LockIndexBuffer(0, (void**)&IndexBuffer);
			//IndexBuffer = indices[0].buffer();
			memcpy(IndexBuffer, indices[0].buffer(), sizeof(indices[0].buffer()));
			Mesh->UnlockIndexBuffer();
			DWORD* attributeBuffer = 0;
			
			
			Mesh->LockAttributeBuffer(0, &attributeBuffer);
 
			for (int a = 0; a < indicesCount/9; a++)
			{
				attributeBuffer[a] = 0;
			}
			Mesh->UnlockAttributeBuffer();
			D3DUtil::getD3DDev()->SetFVF(D3DFVF_CUSTOMVERTEX);

		//	D3DUtil::getD3DDev()->SetStreamSource(0, Mesh, 0, sizeof(CUSTOMVERTEX1));

			D3DUtil::getD3DDev()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			//std::vector<DWORD> adjacencyBuffer(Mesh->GetNumFaces() * 3);
			//Mesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);
			D3DUtil::getD3DDev()->SetTexture(0, *texture->m_animationFrame->curtexture2d->ptexture9);
			D3DUtil::getD3DDev()->DrawPrimitive(/*D3DPT_TRIANGLELIST,*/D3DPT_TRIANGLESTRIP, 0, indicesCount / 3);
			Mesh->DrawSubset(0);
		}

		else if (attachment->getRTTI().isExactly(ClippingAttachment::rtti)) {
			ClippingAttachment *clip = (ClippingAttachment *)slot.getAttachment();
			clipper.clipStart(slot, clip);
			continue;
		}
		else continue;

		unsigned int r = static_cast<unsigned int>(skeleton->getColor().r * slot.getColor().r * attachmentColor->r * 255);
		unsigned int g = static_cast<unsigned int>(skeleton->getColor().g * slot.getColor().g * attachmentColor->g * 255);
		unsigned int b = static_cast<unsigned int>(skeleton->getColor().b * slot.getColor().b * attachmentColor->b * 255);
		unsigned int a = static_cast<unsigned int>(skeleton->getColor().a * slot.getColor().a * attachmentColor->a * 255);
		Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;

		Color light;
		light.r = r / 255.0f;
		light.g = g / 255.0f;
		light.b = b / 255.0f;
		light.a = a / 255.0f;

		BlendMode blend;
		/*
		if (!usePremultipliedAlpha) {
			switch (slot.getData().getBlendMode()) {
			case BlendMode_Normal:
				//blend = normal;
				break;
			case BlendMode_Additive:
				//blend = additive;
				break;
			case BlendMode_Multiply:
				//blend = multiply;
				break;
			case BlendMode_Screen:
				//blend = screen;
				break;
			default:
				//blend = normal;
			}
		}
		else {
			switch (slot.getData().getBlendMode()) {
			case BlendMode_Normal:
				//blend = normalPma;
				break;
			case BlendMode_Additive:
				//blend = additivePma;
				break;
			case BlendMode_Multiply:
				//blend = multiplyPma;
				break;
			case BlendMode_Screen:
				//blend = screenPma;
				break;
			default:
				//blend = normalPma;
			}
		}*/
	//	texture->Update(); texture->Render();

		if (clipper.isClipping()) {
			clipper.clipTriangles(worldVertices, *indices, *uvs, 2);
			vertices = &clipper.getClippedVertices();
			verticesCount = clipper.getClippedVertices().size() >> 1;
			uvs = &clipper.getClippedUVs();
			indices = &clipper.getClippedTriangles();
			indicesCount = clipper.getClippedTriangles().size();
		}
	
		//float w = texture->w;
		//float h = texture->h;
	}
	//clipper.clipEnd();

	//if (vertexEffect != 0) vertexEffect->end();
}


void HuangTextureLoader::load(AtlasPage &page, const String &path) {
	Sprite * texture = new Sprite();
	texture->Sprite_Init(StringUtil::ConvertstringToLPCWSTR(path.buffer()),0,0,0);
	page.setRendererObject(texture); // use the texture later in your rendering code

	//f (page.magFilter == TextureFilter_Linear) texture->setSmooth(true);
	//if (page.uWrap == TextureWrap_Repeat && page.vWrap == TextureWrap_Repeat) texture->setRepeated(true);

	//page.setRendererObject(texture);
	//Vector2u size = texture->getSize();
	page.width = texture->m_animationFrame->curtexture2d->w;
	page.height = texture->m_animationFrame->curtexture2d->h;
}

void HuangTextureLoader::unload(void *texture) {
	delete (Texture2d *) texture;
}

SpineExtension *getDefaultExtension() {
	return new DefaultSpineExtension();
}
}