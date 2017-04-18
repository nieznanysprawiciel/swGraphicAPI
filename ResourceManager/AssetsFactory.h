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

class IAssetCache;


/**@brief Assets factory.
@ingroup AssetsManagement*/
class AssetsFactory
{
private:
protected:

	std::vector< IAssetCreatorPtr >		m_assetCreators;
	IAssetCache*						m_cacheRef;				///< Pointer to cache object. This class is not owner.

public:
	explicit		AssetsFactory		( IAssetCache* cache );
					~AssetsFactory		() = default;

	/**@brief Function for generic asset creation.
	Internal implementation can steal content of IAssetCreateInfo.*/
	ResourceObject*			CreateAsset		( const filesystem::Path& assetName, TypeID assetType, IAssetCreateInfo&& createInfo );

	/**@brief Registers asset creator.
	Can't register creator when it existed.
	@note This function is not thread safe.*/
	bool					RegisterCreator	( IAssetCreatorPtr creator );
};


DEFINE_OPTR_TYPE( AssetsFactory );

}	// sw
