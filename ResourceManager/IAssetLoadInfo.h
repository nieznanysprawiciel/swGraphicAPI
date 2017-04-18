#pragma once
/**
@file IAssetLoadInfo.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/RTTR.h"


namespace sw
{


/**@brief Interface of asset descriptor used to load asset.

@ingroup Loaders*/
class IAssetLoadInfo
{
private:
protected:
public:
	explicit		IAssetLoadInfo		() = default;
	virtual			~IAssetLoadInfo		() = 0;


	virtual TypeID		GetAssetType	() = 0;

};




}	// sw
