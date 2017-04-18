#pragma once
/**
@file nResourceManager.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/BlendingState.h"
#include "swGraphicAPI/Resources/RasterizerState.h"
#include "swGraphicAPI/Resources/DepthStencilState.h"
#include "swGraphicAPI/ResourceManager/ResourceContainer.h"


#include "AssetsFactory.h"
#include "IAssetLoader.h"


namespace sw
{



/**@brief Future implementation of ResourceManager.


@ingroup AssetsManagement*/
class nResourceManager
{
private:
protected:
public:
	explicit		nResourceManager		() = default;
	virtual			~nResourceManager		() = default;



};

}	// sw

