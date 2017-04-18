/**
@file nResourceManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "nResourceManager.h"
#include "swGraphicAPI/ResourceManager/Cache/MemoryCache.h"


namespace sw
{

// ================================ //
//
nResourceManager::nResourceManager()
{
	m_cache = MemoryCacheOPtr( new MemoryCache() );
	m_assetsFactory = AssetsFactoryOPtr( new AssetsFactory( m_cache.get() ) );
}

// ================================ //
//
nResourceManager::~nResourceManager()
{}

}	// sw

