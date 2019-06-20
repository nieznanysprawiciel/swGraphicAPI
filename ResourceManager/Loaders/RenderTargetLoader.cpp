/**
@file RenderTargetLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "RenderTargetLoader.h"

#include "swGraphicAPI/Resources/Textures/RenderTarget.h"
#include "swGraphicAPI/Resources/Textures/Texture.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/Textures/TextureCreator.h"

#include "swGraphicAPI/ResourceManager/Loaders/Tools/LoadingContext.h"



namespace sw
{

// ================================ //
//
bool											RenderTargetLoader::CanLoad			( const AssetPath& filePath, TypeID resourceType )
{
	if( TypeID::get< RenderTarget >() != resourceType )
		return false;

	return true;
}

// ================================ //
//
void											AddTextureIfNotNull					( TexturePtr tex, LoadingContext& context )
{
	if( tex )
	{
		TextureExistingInitInfo info;
		info.Tex = tex;

		auto result = context.Factory.CreateGenericAsset( tex->GetAssetPath(), TypeID::get< Texture >(), std::move( info ) );
		if( context.Warnings.Success( result ) )
			context.AssetsCollection.push_back( result.Get() );
	}
}


// ================================ //
//
LoadingResult									RenderTargetLoader::Load			( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	// Translate load info to descriptor used in creators.
	const RenderTargetLoadInfo* loadInfo = static_cast< const RenderTargetLoadInfo* >( assetDesc );
	auto descriptor = loadInfo->ToDescriptor();

	auto resourceNullable = factory.CreateGenericAsset( filePath, resourceType, std::move( descriptor ) );

	// Creation failed.
	if( !resourceNullable.IsValid() )
		return { resourceNullable.GetError() };

	// Add associated textures to ResourceManager.
	RenderTargetPtr rt = static_cast< RenderTarget* >( resourceNullable.Get().Ptr() );

	TexturePtr color = rt->GetColorBuffer();
	TexturePtr depth = rt->GetDepthBuffer();
	TexturePtr stencil = rt->GetStencilBuffer();

	ErrorsCollector warnings;
	LoadingContext context( factory );


	context.CollectAsset( rt );

	AddTextureIfNotNull( color, context );
	AddTextureIfNotNull( depth, context );
	AddTextureIfNotNull( stencil, context );

	return { std::move( context.AssetsCollection ), context.Warnings.GetException() };
}

// ================================ //
//
ReturnResult									RenderTargetLoader::Prefetch		( const AssetPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
	return Result::Error;
}



}	// sw


