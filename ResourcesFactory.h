#pragma once
/**
@file ResourcesFactory.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "MeshResources.h"
#include "IGraphicAPIInitializer.h"

/**@brief Klasa ze statycznymi funkcjami do tworzenia obiekt�w asset�w.

Jest potrzebna, �eby wybra� implementacj� resourc�w zgodn� z typem renderera.
Ka�de API graficzne powinno zaimplementowa� t� klas�.
*/
class ResourcesFactory
{
public:
	static IGraphicAPIInitializer*	CreateAPIInitializer			();

	static TextureObject*			CreateTextureFromFile			( const std::wstring& fileName );
	static VertexShaderObject*		CreateVertexShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel );
	static PixelShaderObject*		CreatePixelShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel );
	static BufferObject*			CreateBufferFormMemory			( const void* buffer,
																	unsigned int elementSize,
																	unsigned int vertCount,
																	unsigned int bindFlag,
																	ResourceUsage usage = ResourceUsage::RESOURCE_USAGE_STATIC );

	static VertexShaderObject*		CreateVertexShaderFromFile		( const std::wstring& fileName,
																	const std::string& shaderName,
																	ShaderInputLayout** layout,
																	InputLayoutDescriptor* layout_desc,
																	const char* shaderModel = "vs_4_0" );

	static RenderTargetObject*		CreateScreenRenderTarget		();
};

