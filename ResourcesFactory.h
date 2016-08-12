#pragma once
/**
@file ResourcesFactory.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "GraphicAPI/MeshResources.h"
#include "GraphicAPI/SwapChain.h"
#include "GraphicAPI/IGraphicAPIInitializer.h"

class ModelsManager;


/**@brief Klasa ze statycznymi funkcjami do tworzenia obiekt�w asset�w.
@ingroup GraphicAPI

Jest potrzebna, �eby wybra� implementacj� resourc�w zgodn� z typem renderera.
Ka�de API graficzne powinno zaimplementowa� t� klas�.
*/
class ResourcesFactory
{
	friend class ModelsManager;
private:
	static TextureObject*			CreateTextureFromMemory			( const MemoryChunk& texData, TextureInfo&& texInfo );

	static VertexShader*			CreateVertexShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static PixelShader*				CreatePixelShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "ps_4_0" );
	static ComputeShader*			CreateComputeShaderFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "cs_4_0" );
	static BufferObject*			CreateBufferFromMemory			( const void* buffer,
																	unsigned int elementSize,
																	unsigned int vertCount,
																	ResourceBinding bindFlag,
																	ResourceUsage usage = ResourceUsage::RESOURCE_USAGE_STATIC );

	static VertexShader*			CreateVertexShaderFromFile		( const std::wstring& fileName,
																	const std::string& shaderName,
																	ShaderInputLayout** layout,
																	InputLayoutDescriptor* layout_desc,
																	const char* shaderModel = "vs_4_0" );
public:
	static IGraphicAPIInitializer*	CreateAPIInitializer			();
	static RenderTargetObject*		CreateScreenRenderTarget		();
	static SwapChain*				CreateScreenSwapChain			( RenderTargetObject* screenRT );
	static InputLayoutDescriptor*	CreateInputLayoutDescritor		( const std::wstring& layoutName );
	static RenderTargetObject*		CreateRenderTarget				( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor );
};

