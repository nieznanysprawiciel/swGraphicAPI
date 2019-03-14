/**
@file RasterizerStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "RasterizerStateCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"
#include "swCommonLib/Common/Converters.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"


namespace sw
{

// ================================ //
//
Nullable< Resource* >		RasterizerStateCreator::Create		( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();
	if( type == TypeID::get< RasterizerStateInfo >() )
		return ResourcesFactory::CreateRasterizerState( static_cast< RasterizerStateInfo& >( createInfo ) );

	return "[RasterizerStateCreator] IAssetCreateInfo of type [" + type.get_name().to_string() + "] not supported.";
}

// ================================ //
//
Nullable< Resource* >		RasterizerStateCreator::LoadFromRaw	( const filesystem::Path& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					RasterizerStateCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					RasterizerStateCreator::SaveToRaw	( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						RasterizerStateCreator::IsCacheable	() const
{
	return false;
}

// ================================ //
//
bool						RasterizerStateCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						RasterizerStateCreator::GetAssetType	() const
{
	return TypeID::get< RasterizerState >();
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//



}	// sw