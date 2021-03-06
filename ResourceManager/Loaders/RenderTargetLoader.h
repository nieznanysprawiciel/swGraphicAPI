#pragma once
/**
@file RenderTargetLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"
#include "swGraphicAPI/ResourceManager/Loaders/RenderTargetLoadInfo.h"

#include "swGraphicAPI/Resources/Textures/RenderTarget.h"
#include "swGraphicAPI/Resources/SwapChain.h"


namespace sw
{




/**@brief Creates RenderTarget.

Render Target has internal textures which have to be added to ResourceManager.
We need this loader to add them, because asset creators don't have access to ResourceManager.*/
class RenderTargetLoader : public IAssetLoader
{
private:
protected:
public:
	explicit		RenderTargetLoader		() = default;
	virtual			~RenderTargetLoader		() = default;


	virtual bool											CanLoad			( const AssetPath& filePath, TypeID resourceType )															override;
	virtual LoadingResult									Load			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;
	virtual ReturnResult									Prefetch		( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;

};




}	// sw

