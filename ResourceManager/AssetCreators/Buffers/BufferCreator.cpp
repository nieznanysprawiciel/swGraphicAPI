/**
@file BufferCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "BufferCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"
#include "swCommonLib/Common/Converters.h"



namespace sw
{

// ================================ //
//
ResourceObject*				BufferCreator::Create		( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	return nullptr;
}

// ================================ //
//
ResourceObject*				BufferCreator::LoadFromRaw	( const filesystem::Path& assetName, const MemoryChunk& rawData )
{
	return nullptr;
}

// ================================ //
//
MemoryChunk					BufferCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	return MemoryChunk();
}

// ================================ //
//
MemoryChunk					BufferCreator::SaveToRaw	( ResourcePtr< ResourceObject > resource )
{
	return MemoryChunk();
}

// ================================ //
//
bool						BufferCreator::SupportsResourceToRaw()
{
	return false;
}

// ================================ //
//
TypeID						BufferCreator::GetAssetType()
{
	return TypeID::get< BufferObject >();
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//


// ================================ //
//
ResourcePtr< BufferObject >			BufferCreator::CreateVertexBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount )
{
	VertexBufferInitData initData;
	initData.Data = buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;
	
	return CreateVertexBuffer( name, initData );
}

// ================================ //
//
ResourcePtr< BufferObject >			BufferCreator::CreateVertexBuffer		( const filesystem::Path& name, const VertexBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name.WString(), data.Data, data.CreateBufferInfo() );
}

// ================================ //
//
ResourcePtr< BufferObject >			BufferCreator::CreateIndexBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount )
{
	IndexBufferInitData initData;
	initData.Data = buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;

	return CreateIndexBuffer( name, initData );
}

// ================================ //
//
ResourcePtr< BufferObject >			BufferCreator::CreateIndexBuffer		( const filesystem::Path& name, const IndexBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name.WString(), data.Data, data.CreateBufferInfo() );
}

// ================================ //
//
ResourcePtr< BufferObject >			BufferCreator::CreateConstantsBuffer	( const filesystem::Path& name, const uint8* buffer, unsigned int size )
{
	ConstantBufferInitData initData;
	initData.Data = (const uint8*)buffer;
	initData.ElementSize = size;
	initData.NumElements = 1;

	return CreateConstantsBuffer( name, initData );
}

// ================================ //
//
ResourcePtr< BufferObject >			BufferCreator::CreateConstantsBuffer	( const filesystem::Path& name, const ConstantBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name.WString(), data.Data, data.CreateBufferInfo() );
}


}	// sw
