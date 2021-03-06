/**
@file MockAssetCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/MockAssets/stdafx.h"

#include "MockAssetCreator.h"

#include "MockAsset.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"




namespace sw
{

// ================================ //
//
Nullable< Resource* >		MockAssetCreator::Create			( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
	if( createInfo.get_type() == TypeID::get< MockAssetCreateInfo >() )
	{
		auto& typedInfo = static_cast< MockAssetCreateInfo& >(createInfo);
		return new MockAsset( this, assetName, typedInfo.Content );
	}

	return "Wrong IAssetCreateInfo of type [" + createInfo.get_type().get_name().to_string() + "].";
}

// ================================ //
//
Nullable< Resource* >		MockAssetCreator::LoadFromRaw		( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"InputLayout is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					MockAssetCreator::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					MockAssetCreator::SaveToRaw		( ResourcePtr< Resource > resource )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						MockAssetCreator::IsCacheable		() const
{
	return false;
}

// ================================ //
//
bool						MockAssetCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						MockAssetCreator::GetAssetType			() const
{
	return TypeID::get< MockAsset >();
}

// ================================ //
//
void						MockAssetCreator::OnDeleteAsset			( MockAsset* asset )
{
	auto iter = std::find( m_livingAssets.begin(), m_livingAssets.end(), asset );
	m_livingAssets.erase( iter );
}

// ================================ //
//
void						MockAssetCreator::OnCreateAsset			( MockAsset* asset )
{
	m_livingAssets.push_back( asset );
}

// ================================ //
//
MockAssetCreatorPtr			MockAssetCreator::CreateCreator			()
{
	return std::make_shared< MockAssetCreator >();
}



}	// sw



