#pragma once

#include "../../MeshResources.h"
#include "../DX11Initializer/DX11APIObjects.h"


/**@brief Implementacja render targetu w DirectX11.
@ingroup DX11API*/
class DX11RenderTarget	:	public RenderTargetObject, public DX11APIObjects
{
private:
	ID3D11RenderTargetView*			m_renderTarget;
	ID3D11DepthStencilView*			m_depthStencilView;

	uint16							m_height;
	uint16							m_width;
protected:
	~DX11RenderTarget();
public:
	DX11RenderTarget( ID3D11RenderTargetView* renderTarget,
					  ID3D11DepthStencilView* depthStencil,
					  TextureObject* colorBuffer,
					  TextureObject* depthBuffer,
					  TextureObject* stencilBuffer);

	inline uint16							GetWidth()					{ return m_width; }
	inline uint16							GetHeight()					{ return m_height; }
	inline void								SetHeight		( uint16 value )	{ m_height = value; }
	inline void								SetWidth		( uint16 value )	{ m_width = value; }

	inline ID3D11RenderTargetView*			GetRenderTarget()			{ return m_renderTarget; }
	inline ID3D11DepthStencilView*			GetDepthStencil()			{ return m_depthStencilView; }

	static DX11RenderTarget*				CreateScreenRenderTarget();
	static DX11RenderTarget*				CreateRenderTarget( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor );

private:
	static bool								ValidateDescriptor( const RenderTargetDescriptor& renderTargetDescriptor );
};

