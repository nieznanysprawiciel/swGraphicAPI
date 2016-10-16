#pragma once
/**
@file IRenderer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/


#include "GraphicAPI/MeshResources.h"
#include "RenderCommands.h"


/**@brief Spos�b u�ycia renderera.

Renderer mo�e wysy�a� polecenia na kart� graficzn� od razu lub
zamiast tego tworzyc kolejk� komunikat�w i wysy�a� dopiero kiedy wszystko b�dzie przygotowane.
Ta druga opcja umo�liwia renderowanie wielow�tkowe.*/
enum RendererUsage
{
	USE_AS_DEFERRED,			///<Renderowanie do kolejki rozkaz�w.
	USE_AS_IMMEDIATE			///<Renderowanie natychmiastowe
};



/**@brief Klasa interfejsu renderera.
@ingroup GraphicAPI
@ingroup RenderingCommands*/
class IRenderer
{
private:
public:
	IRenderer() = default;
	virtual ~IRenderer() = default;


	virtual bool SupportsDefferedContextRendering() = 0;		///< Informuje czy Renderer nadaje si� do renderowania w wielu w�tkach do op�nionego contextu.
	virtual bool IsValid() = 0;

///@name DepracatedAPI
///@deprecated Use commands
///@{
	virtual void SetTextures						( const ModelPart& model ) = 0;
	virtual void SetIndexBuffer						( BufferObject* buffer ) = 0;
	virtual bool SetVertexBuffer					( BufferObject* buffer, unsigned int offset = 0 ) = 0;
	virtual void DepthBufferEnable					( bool state ) = 0;
	virtual void SetDefaultVertexLayout				() = 0;
	virtual void SetDefaultSampler					() = 0;

	virtual void InitBuffers						( unsigned int sizePerFrame, unsigned int sizePerMesh ) = 0;
	virtual void InitDepthStates					() = 0;

	virtual void IASetPrimitiveTopology				( PrimitiveTopology topology ) = 0;
	virtual void IASetInputLayout					( ShaderInputLayout* inputLayout ) = 0;


	//virtual void VSSetConstantBuffers				( uint32 startSlot, uint32 numBuffers, ID3D11Buffer *const *ppConstantBuffers ) = 0;
	virtual void VSSetConstantBuffers				( uint32 slot, BufferObject* buffer ) = 0;

	//virtual void PSSetConstantBuffers				( uint32 startSlot, uint32 numBuffers, ID3D11Buffer *const *ppConstantBuffers ) = 0;
	virtual void PSSetConstantBuffers				( uint32 slot, BufferObject* buffer ) = 0;

	virtual void UpdateSubresource					( BufferObject* pDstResource, const void *pSrcData ) = 0;

	virtual void SetShaders							( ModelPart& model ) = 0;

	// Rendering
	virtual void Draw								( unsigned int vertexCount, unsigned int startVertexLocation ) = 0;
	virtual void DrawIndexed						( unsigned int indexCount, unsigned int startIndexLocation, int BaseVertexLocation ) = 0;

	virtual void Present							() = 0;
	virtual void BeginScene							( RenderTargetObject* mainRenderTarget ) = 0;
///}@


	virtual void		Draw					( const DrawCommand& command )						= 0;
	virtual void		DrawInstanced			( const DrawInstancedCommand& command )				= 0;

	virtual void		SetRenderTarget			( const SetRenderTargetCommand& command )			= 0;
	virtual void		SetRenderTarget			( const SetRenderTargetExCommand& command )			= 0;
	virtual void		ClearRenderTarget		( const ClearRenderTargetCommand& command )			= 0;

	virtual void		UpdateBuffer			( const UpdateBufferCommand& command )				= 0;
	virtual void		BindBuffer				( const BindBufferCommand& command )				= 0;
	virtual void		UpdateAndBindBuffer		( const UpdateBindBuffer& command )					= 0;

	virtual void		SetDefaultBuffers		( const SetDefaultBuffersCommand& command )			= 0;
	
	virtual void		SetShaderState			( const SetShaderStateCommand& command )			= 0;
	virtual void		SetShaderState			( const SetShaderStateExCommand& command )			= 0;
	virtual void		SetShaderState			( const SetRenderStateCommand& command )			= 0;
	virtual void		SetShaderState			( const SetRenderStateExCommand& command )			= 0;

	virtual void		CopyTexture				( const CopyTextureCommand& command )				= 0;
};


