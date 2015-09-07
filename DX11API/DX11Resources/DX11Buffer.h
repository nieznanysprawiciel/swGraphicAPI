#pragma once

#include "GraphicAPI\MeshResources.h"
#include "../DX11Initializer/DX11APIObjects.h"


class DX11Buffer	:	public BufferObject, public DX11APIObjects
{
private:
	ID3D11Buffer*			m_buffer;
protected:
	~DX11Buffer();
public:
	DX11Buffer( unsigned int element_size, unsigned int elementCount, ID3D11Buffer* buff );

	ID3D11Buffer*			get() { return m_buffer; }

	static DX11Buffer*			CreateFromMemory(	const void* buffer,
													unsigned int elementSize,
													unsigned int vertCount,
													unsigned int bindFlag,
													ResourceUsage usage = ResourceUsage::RESOURCE_USAGE_STATIC );
};

