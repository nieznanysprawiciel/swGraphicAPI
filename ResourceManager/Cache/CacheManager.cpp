/**
@file CacheManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"
#include "CacheManager.h"


#include "swGraphicAPI/ResourceManager/Cache/MemoryCache.h"


namespace sw
{

// ================================ //
//
CacheManager::CacheManager()
{
	InitDefaultCacheHierarchy();
}

// ================================ //
//
ResourcePtr< Resource >		CacheManager::LoadFromCache		( const AssetPath& assetName, TypeID assetType )
{
	return ResourcePtr< Resource >();
}


//====================================================================================//
//			Internal	
//====================================================================================//

// ================================ //
//
void		CacheManager::InitDefaultCacheHierarchy()
{
	m_cacheList = MemoryCacheOPtr( new MemoryCache() );
}

}	// sw


