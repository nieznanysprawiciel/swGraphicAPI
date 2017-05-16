#pragma once
/**
@file ShaderCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"


namespace sw
{


/**@brief */
class ShaderCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		ShaderCreator		() = default;
	virtual			~ShaderCreator		() = default;


public:

	virtual ResourceObject*			Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual ResourceObject*			LoadFromRaw			( const filesystem::Path& assetName, const MemoryChunk& rawData )			override;
	virtual MemoryChunk				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual MemoryChunk				SaveToRaw			( ResourcePtr< ResourceObject > resource )									override;

	virtual bool					SupportsResourceToRaw	() override;
	virtual TypeID					GetAssetType			() override;

public:

};






}	// sw



