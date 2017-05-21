#pragma once
/**
@file AssetLoadRequest.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/External/FastDelegate/FastDelegate.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/ResourceManager/IAssetLoadInfo.h"

#include "AssetLoadResponse.h"


namespace sw
{


/**@brief Queue element for asynchronous asset loading thread.

@ingroup AsyncLoading*/
struct AssetLoadRequest
{
	filesystem::Path		FilePath;
	IAssetLoadInfoOPtr		LoadInfo;
	AsyncLoadHandler		OnLoaded;

private:
	bool					EndMessage;		///< Set to true if you want end loading thread execution.

// ================================ //
//
public:
	AssetLoadRequest()
		: EndMessage( false )
	{}
};

}	// sw

