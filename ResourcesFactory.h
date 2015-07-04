#pragma once


#include "MeshResources.h"

/**Klasa ze statycznymi funkcjami do tworzenia obiekt�w asset�w.

Jest potrzebna, �eby wybra� inplementacj� zgodn� z typem renderera.*/
class ResourcesFactory
{
public:
	static TextureObject*			CreateTextureFromFile( const std::wstring& fileName );
	static VertexShaderObject*		CreateVertexShaderFromFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel );
	static PixelShaderObject*		CreatePixelShaderFromFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel );
	static BufferObject*			CreateBufferFormMemory( const void* buffer,
															unsigned int elementSize,
															unsigned int vertCount,
															unsigned int bindFlag,
															D3D11_USAGE usage = D3D11_USAGE_DEFAULT );
};

