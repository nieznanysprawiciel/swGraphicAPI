/**
@file AssetsFactory.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "AssetsFactory.h"



namespace sw
{


// ================================ //
//
AssetsFactory::AssetsFactory	( IAssetCache* cache )
	:	m_cacheRef( cache )
{}


// ================================ //
//
bool			AssetsFactory::RegisterCreator		( IAssetCreatorPtr creator )
{
	TypeID type = creator->GetAssetType();
	for( size_t i = 0; i < m_assetCreators.size(); i++ )
	{
		if( m_assetCreators[ i ]->GetAssetType() == type )
			return false;
	}

	m_assetCreators.push_back( creator );
	return true;
}

}	// sw

