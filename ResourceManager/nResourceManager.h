#pragma once
/**
@file nResourceManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/BlendingState.h"
#include "swGraphicAPI/Resources/RasterizerState.h"
#include "swGraphicAPI/Resources/DepthStencilState.h"
#include "swGraphicAPI/ResourceManager/ResourceContainer.h"


#include "AssetsFactory.h"
#include "IAssetLoader.h"
#include "Cache/IAssetCache.h"
#include "AsyncLoad/AssetsThread.h"

#include <vector>


namespace sw
{



/**@brief Future implementation of ResourceManager.


@ingroup AssetsManagement*/
class nResourceManager
{
private:
protected:

	AssetsFactoryOPtr			m_assetsFactory;		///< Factory for generic and non generic assets creation.
	IAssetCacheOPtr				m_cache;				///< Assets cache.

	std::vector< IAssetLoaderOPtr >		m_loaders;		///< File loaders.

	AssetsThread				m_asyncThread;			///< Thread used for asynchronous loading.

public:

	/**@brief This constructor creates default cache and AssetsFactory.*/
	explicit		nResourceManager		();
	virtual			~nResourceManager		();



	RenderTargetObject*				CreateRenderTarget			( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor );

	///@name Geting existing resource
	///@detail Gets resource if exist otherwise returns nullptr.
	///@{

	BlendingState*				GetBlendingState			( const std::wstring& name );
	RasterizerState*			GetRasterizerState			( const std::wstring& name );
	DepthStencilState*			GetDepthStencilState		( const std::wstring& name );

	BlendingState*				GetBlendingState			( const BlendingInfo& info );
	RasterizerState*			GetRasterizerState			( const RasterizerStateInfo& info );
	DepthStencilState*			GetDepthStencilState		( const DepthStencilInfo& info );

	RenderTargetObject*			GetRenderTarget				( const std::wstring& name );	///<Zwraca RenderTarget o podanej nazwie, je¿eli jest wczytany.
	VertexShader*				GetVertexShader				( const std::wstring& name );	///<Zwraca vertex shader o podanej nazwie, je¿eli jest wczytany.
	PixelShader*				GetPixelShader				( const std::wstring& name );	///<Zwraca pixel shader o podanej nazwie, je¿eli jest wczytany.
	TextureObject*				GetTexture					( const std::wstring& name );	///<Zwraca teksturê o podanej nazwie, je¿eli jest wczytany.
	BufferObject*				GetVertexBuffer				( const std::wstring& name );	///<Zwraca bufor wierzcho³ków o podanej nazwie, je¿eli jest wczytany.
	BufferObject*				GetConstantBuffer			( const std::wstring& name );	///<Zwraca bufor sta³ych o podanej nazwie, je¿eli jest wczytany.
	BufferObject*				GetIndexBuffer				( const std::wstring& name );	///<Zwraca bufor indeksów o podanej nazwie, je¿eli jest wczytany.
	ShaderInputLayout*			GetLayout					( const std::wstring& name );	///<Zwraca layout o podanej nazwie.	
	///@}


	///@name Resource loading
	///@detail Load assets from specified file. Functions protect from loading assets multiple times.
	///@{
	TextureObject*					LoadTexture					( const std::wstring& fileName );
	VertexShader*					LoadVertexShader			( const std::wstring& fileName, const std::string& shaderEntry );
	VertexShader*					LoadVertexShader			( const std::wstring& fileName, const std::string& shaderEntry, ShaderInputLayout** layout, InputLayoutDescriptor* layout_desc );
	PixelShader*					LoadPixelShader				( const std::wstring& fileName, const std::string& shaderEntry );
	GeometryShader*					LoadGeometryShader			( const std::wstring& fileName, const std::string& shaderEntry );
	ControlShader*					LoadControlShader			( const std::wstring& fileName, const std::string& shaderEntry );
	EvaluationShader*				LoadEvaluationShader		( const std::wstring& fileName, const std::string& shaderEntry );
	///@}

	///@name Resource creation
	///@detail You can create assets in code using these functions. Remember to give unique names for your assets.
	///Engine uses convention, that all generated resources have :: before name, to distinguish them from assets loaded from files.
	///@{
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const std::wstring& name, const void* buffer, unsigned int element_size, unsigned int vert_count );
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const std::wstring& name, const VertexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const std::wstring& name, const void* buffer, unsigned int element_size, unsigned int vert_count );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const std::wstring& name, const IndexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const std::wstring& name, const void* buffer, unsigned int size );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const std::wstring& name, const ConstantBufferInitData& data );

	ResourcePtr< BlendingState >	CreateBlendingState			( const std::wstring& name, const BlendingInfo& info );
	ResourcePtr< RasterizerState >	CreateRasterizerState		( const std::wstring& name, const RasterizerStateInfo& info );
	ResourcePtr< DepthStencilState >CreateDepthStencilState		( const std::wstring& name, const DepthStencilInfo& info );

	///@}

	RenderTargetObject*				AddRenderTarget				( RenderTargetObject* renderTarget, const std::wstring& name );


	///@name Listing resources
	///@{
	std::vector< ResourcePtr< BufferObject > >			ListVertexBuffers	();
	std::vector< ResourcePtr< BufferObject > >			ListIndexBuffers	();
	std::vector< ResourcePtr< BufferObject > >			ListConstantBuffers	();
	std::vector< ResourcePtr< ShaderInputLayout > >		ListShaderLayouts	();

	std::vector< ResourcePtr< TextureObject > >			ListTextures		();
	std::vector< ResourcePtr< VertexShader > >			ListVertexShaders	();
	std::vector< ResourcePtr< PixelShader > >			ListPixelShaders	();
	
	std::vector< ResourcePtr< RenderTargetObject > >	ListRenderTargets	();
	///@}
};

}	// sw

