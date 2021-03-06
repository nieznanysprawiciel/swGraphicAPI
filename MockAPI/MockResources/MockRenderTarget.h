#pragma once
/**
@file MockRenderTarget.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"


namespace sw
{



/**@brief
@ingroup MockAPI*/
class MockRenderTarget : public RenderTarget
{
	RTTR_ENABLE( RenderTarget );
private:

	uint16							m_height;
	uint16							m_width;

protected:

	virtual			~MockRenderTarget		();
public:
	explicit			MockRenderTarget	(	const AssetPath& name, 
												Texture* colorBuffer,
												Texture* depthBuffer,
												Texture* stencilBuffer );


	inline uint16								GetWidth() { return m_width; }
	inline uint16								GetHeight() { return m_height; }
	inline void									SetHeight		( uint16 value ) { m_height = value; }
	inline void									SetWidth		( uint16 value ) { m_width = value; }

	static MockRenderTarget*					CreateScreenRenderTarget	();
	static sw::Nullable< MockRenderTarget* >	CreateRenderTarget			( const AssetPath& name, const RenderTargetDescriptor& renderTargetDescriptor );

private:
	static bool									ValidateDescriptor			( const RenderTargetDescriptor& renderTargetDescriptor );
};

}	// sw
