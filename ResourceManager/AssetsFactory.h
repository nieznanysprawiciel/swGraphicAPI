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

	uint8				m_buffersCreatorIdx;
	uint8				m_VSCreatorIdx;
	uint8				m_PSCreatorIdx;
	uint8				m_ESCreatorIdx;
	uint8				m_CSCreatorIdx;
	uint8				m_CtrlSCreatorIdx;
	uint8				m_GSCreatorIdx;

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

	/**@brief Registers built in creators.*/
	void					RegisterDefaults();


public:

	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateVertexBuffer			( const filesystem::Path& name, const VertexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount );
	ResourcePtr< BufferObject >		CreateIndexBuffer			( const filesystem::Path& name, const IndexBufferInitData& data );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int size );
	ResourcePtr< BufferObject >		CreateConstantsBuffer		( const filesystem::Path& name, const ConstantBufferInitData& data );
};


DEFINE_OPTR_TYPE( AssetsFactory );

}	// sw
