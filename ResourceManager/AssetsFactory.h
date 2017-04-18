#pragma once
/**
@file AssetsFactory.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "AssetCreators/IAssetCreator.h"


#include <vector>


namespace sw
{

/**@brief Assets factory.
@ingroup AssetsManagement*/
class AssetsFactory
{
private:
protected:

	std::vector< IAssetCreatorPtr >		m_assetCreators;

public:
	explicit		AssetsFactory		() = default;
					~AssetsFactory		() = default;

	/**@brief Function for generic asset creation.
	Internal implementation can steal content of IAssetCreateInfo.*/
	ResourceObject*			CreateAsset		( const filesystem::Path& assetName, TypeID assetType, IAssetCreateInfo&& createInfo );

	/**@brief Registers asset creator.
	Can't register creator when it existed.
	@note This function is not thread safe.*/
	bool					RegisterCreator	( IAssetCreatorPtr creator );
};


}	// sw
