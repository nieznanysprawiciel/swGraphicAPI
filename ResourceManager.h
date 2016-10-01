#pragma once
/**
@file ResourceManager.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "MeshResources.h"
#include "ResourceContainer.h"

class ILoader;



/**@brief Manager for low level resources.

@todo This class should implement generic high level asssets managment.

@ingroup ResourcesManagment*/
class ResourceManager
{
private:
protected:
	ResourceContainer< VertexShader >			m_vertexShader;		///<Vertex shadery.
	ResourceContainer< PixelShader >			m_pixelShader;		///<Pixel shadery.
	ResourceContainer< GeometryShader >			m_geometryShader;	///< Geometry shaders.
	ResourceContainer< EvaluationShader >		m_evaluationShader;	///< Tesselation evaluation shaders.
	ResourceContainer< ControlShader >			m_controlShaders;	///< Tesselation control shaders.

	ResourceContainer<TextureObject>			m_texture;			///<Tekstury.
	ResourceContainer<BufferObject>				m_vertexBuffer;		///<Bufory wierzcho�k�w.
	ResourceContainer<BufferObject>				m_indexBuffer;		///<Bufory indeks�w.
	ResourceContainer<BufferObject>				m_constantBuffer;	///<Bufory sta�ych dla shader�w.
	ResourceContainer<ShaderInputLayout>		m_vertexLayout;		///<Layouty dla r�znych format�w wierzcho�k�w.
	// UWAGA! m_fileModel musi by� na ko�cu. Jego destruktor kasuje odwo�ania do obiekt�w powy�ej. Podobnie RenderTargetObject odwo�uje si� do tekstur.
	// Musz� one w tym czasie istnie�, a destruktory s� wywo�ywane w kolejno�ci odwrotnej do zadeklarowanej w klasie.
	ResourceContainer<RenderTargetObject>		m_renderTarget;		///<Obiekty mog�ce s�u�y� za render target.

	/*loadery dla r�nych format�w plik�w z modelami*/
	//std::vector<ILoader*>						m_loader;				///<Loadery do plik�w z modelami 3D

public:
	explicit						ResourceManager();
									~ResourceManager();

	// Funkcje do zarz�dzania assetami
	RenderTargetObject*				CreateRenderTarget			( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor );

	inline RenderTargetObject*		GetRenderTarget				( const std::wstring& name ) { return m_renderTarget.get( name ); }	///<Zwraca RenderTarget o podanej nazwie, je�eli jest wczytany.
	inline VertexShader*			GetVertexShader				( const std::wstring& name ) { return m_vertexShader.get( name ); } ///<Zwraca vertex shader o podanej nazwie, je�eli jest wczytany.
	inline PixelShader*				GetPixelShader				( const std::wstring& name ) { return m_pixelShader.get( name ); }	///<Zwraca pixel shader o podanej nazwie, je�eli jest wczytany.
	inline TextureObject*			GetTexture					( const std::wstring& name ) { return m_texture.get( name ); }		///<Zwraca tekstur� o podanej nazwie, je�eli jest wczytany.
	inline BufferObject*			GetVertexBuffer				( const std::wstring& name ) { return m_vertexBuffer.get( name ); }	///<Zwraca bufor wierzcho�k�w o podanej nazwie, je�eli jest wczytany.
	inline BufferObject*			GetConstantBuffer			( const std::wstring& name ) { return m_constantBuffer.get( name ); }	///<Zwraca bufor sta�ych o podanej nazwie, je�eli jest wczytany.
	inline BufferObject*			GetIndexBuffer				( const std::wstring& name ) { return m_indexBuffer.get( name ); }	///<Zwraca bufor indeks�w o podanej nazwie, je�eli jest wczytany.
	inline ShaderInputLayout*		GetLayout					( const std::wstring& name ) { return m_vertexLayout.get( name ); }	///<Zwraca layout o podanej nazwie.	

	TextureObject*					LoadTexture					( const std::wstring& fileName );
	VertexShader*					LoadVertexShader			( const std::wstring& fileName, const std::string& shaderEntry );
	VertexShader*					LoadVertexShader			( const std::wstring& fileName, const std::string& shaderEntry, ShaderInputLayout** layout, InputLayoutDescriptor* layout_desc );
	PixelShader*					LoadPixelShader				( const std::wstring& fileName, const std::string& shaderEntry );
	GeometryShader*					LoadGeometryShader			( const std::wstring& fileName, const std::string& shaderEntry );
	ControlShader*					LoadControlShader			( const std::wstring& fileName, const std::string& shaderEntry );
	EvaluationShader*				LoadEvaluationShader		( const std::wstring& fileName, const std::string& shaderEntry );

	ResourcePtr< BufferObject >		CreateVertexBuffer			( const std::wstring& name, const void* buffer, unsigned int element_size, unsigned int vert_count );
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const std::wstring& name, const VertexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const std::wstring& name, const void* buffer, unsigned int element_size, unsigned int vert_count );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const std::wstring& name, const IndexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const std::wstring& name, const void* buffer, unsigned int size );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const std::wstring& name, const ConstantBufferInitData& data );
	
	RenderTargetObject*				AddRenderTarget				( RenderTargetObject* renderTarget, const std::wstring& name );

	// Funkcje do listowania asset�w.

	std::vector< ResourcePtr< BufferObject > >			ListVertexBuffers	();
	std::vector< ResourcePtr< BufferObject > >			ListIndexBuffers	();
	std::vector< ResourcePtr< BufferObject > >			ListConstantBuffers	();
	std::vector< ResourcePtr< ShaderInputLayout > >		ListShaderLayouts	();

	std::vector< ResourcePtr< TextureObject > >			ListTextures		();
	std::vector< ResourcePtr< VertexShader > >			ListVertexShaders	();
	std::vector< ResourcePtr< PixelShader > >			ListPixelShaders	();
	
	std::vector< ResourcePtr< RenderTargetObject > >	ListRenderTargets	();

private:
	//ILoader*						FindLoader					( const std::wstring& path );
	
	virtual MemoryChunk				LoadTextureImpl				( const filesystem::Path& filePath, TextureInfo& texInfo );
};

