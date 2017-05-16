/**
@file ShaderCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ShaderCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"


namespace sw
{

// ================================ //
//
ResourceObject*				ShaderCreator::Create		( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{

	return nullptr;
}

// ================================ //
//
ResourceObject*				ShaderCreator::LoadFromRaw	( const filesystem::Path& assetName, const MemoryChunk& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
MemoryChunk					ShaderCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return MemoryChunk();
}

// ================================ //
//
MemoryChunk					ShaderCreator::SaveToRaw	( ResourcePtr< ResourceObject > resource )
{
	assert( !"Buffer is not cacheable" );
	return MemoryChunk();
}

// ================================ //
//
bool						ShaderCreator::SupportsResourceToRaw()
{
	return false;
}

// ================================ //
//
TypeID						ShaderCreator::GetAssetType()
{
	return TypeID::get< BufferObject >();
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//




}	// sw

