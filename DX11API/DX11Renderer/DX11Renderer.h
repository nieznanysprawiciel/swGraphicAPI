#pragma once
/**
@file DX11Renderer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

Deklaracja renderera u�ywaj�cego DirectX 11.
*/


#include "../../DX11API/DX11Initializer/DX11APIObjects.h"
#include "../../MeshResources.h"
#include "../../IRenderer.h"

class DX11Renderer;
typedef DX11Renderer Renderer;




/**@brief Renderer obs�uguj�cy DirectX 11.
@ingroup DX11API*/
class DX11Renderer	: public IRenderer,	public DX11AuxiliaryObjects
{
private:
	/**Kontekst urz�dzenia s�u��cy do renderowania. W zale�no�ci czy stosujemy op�nione renderowanie (deferred rendering) czy nie,
	ta zmienna przechowuje kopi� wska�nika z DX11_interfaces_container lub op�niony kontekst (deferred context).
	W trakcie renderowania nie musimy wiedzie� z czym mamy do czynienia.*/
	ID3D11DeviceContext*		m_localDeviceContext;			
	bool						m_valid;					///< Je�eli klasa nie zosta�a zainicjowana poprawnie, to b�dzie tu warto�� false.
	RendererUsage				m_usageType;				///< Informacja jak b�dzie u�ywany rederer.
public:
	DX11Renderer( RendererUsage usage = USE_AS_IMMEDIATE );
	~DX11Renderer();

	bool SupportsDefferedContextRendering() override	{ return true; }		///< Informuje czy Renderer nadaje si� do renderowania w wielu w�tkach do op�nionego contextu.
	bool IsValid() override								{ return m_valid; }


	void SetTextures								( const ModelPart& model )																override;
	void SetIndexBuffer								( BufferObject* buffer )																override;
	bool SetVertexBuffer							( BufferObject* buffer, unsigned int offset = 0 )										override;
	void DepthBufferEnable							( bool state )																			override;
	void SetDefaultVertexLayout						()																						override;
	void SetDefaultSampler							()																						override;

	void InitBuffers								( unsigned int sizePerFram, unsigned int sizePerMesh )									override;
	void InitDepthStates							()																						override;

	void IASetPrimitiveTopology						( PrimitiveTopology topology )															override;
	void IASetInputLayout							( ShaderInputLayout* pInputLayout )														override;


	void VSSetConstantBuffers						( uint32 slot, BufferObject* buffer )													override;
	void PSSetConstantBuffers						( uint32 slot, BufferObject* buffer )													override;

	void UpdateSubresource							( BufferObject* pDstResource, const void *pSrcData )									override;

	void SetShaders									( ModelPart& model )																	override;

	// Rendering
	void Draw										( unsigned int vertexCount, unsigned int startVertexLocation )							override;
	void DrawIndexed								( unsigned int indexCount, unsigned int startIndexLocation, int baseVertexLocation )	override;
	
	void Present									()																						override;
	void BeginScene									( RenderTargetObject* mainRenderTarget )												override;
};



