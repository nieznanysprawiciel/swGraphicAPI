/**
@file nResourceManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "nResourceManager.h"
#include "swGraphicAPI/ResourceManager/nResourceContainer.h"
#include "swGraphicAPI/ResourceManager/Cache/MemoryCache.h"


namespace sw
{

// ================================ //
//
nResourceManager::nResourceManager()
	:	m_asyncThread( RMAsyncLoaderAPI( this ) )
{
	m_cache = MemoryCacheOPtr( new MemoryCache() );
	m_assetsFactory = AssetsFactoryOPtr( new AssetsFactory( m_cache.get() ) );
}

// ================================ //
//
nResourceManager::~nResourceManager()
{}

// ================================ //
//
ResourcePtr< ResourceObject >			nResourceManager::LoadGeneric				( const filesystem::Path& name, IAssetLoadInfo* desc, TypeID type )
{
	auto resource = FindResource( name, type );
	if( !resource )
	{

	}

	return resource;
}

// ================================ //
//
ResourcePtr< ResourceObject >			nResourceManager::CreateGenericAsset		( const filesystem::Path& name, TypeID assetType, IAssetCreateInfo&& createInfo )
{
	return ResourcePtr<ResourceObject>();
}


//====================================================================================//
//			Internal implementation	
//====================================================================================//


// ================================ //
//
ResourcePtr< ResourceObject >			nResourceManager::FindResource				( const filesystem::Path& name, TypeID resourceType )
{
	auto containerIter = m_resources.find( resourceType );
	if( containerIter != m_resources.end() )
	{
		ResourceContainer< ResourceObject > & container = containerIter->second;
		return container.Get( name );
	}

	return ResourcePtr< ResourceObject >();
}

}	// sw

