#pragma once
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


/// @note You can disable all headers in precompiled header with one macro.
/// All cpp files should be precompiled header independet and explicitly include needed headers.
#ifndef DISABLE_PRECOMPILED_HEADER


#include <cassert>

#include <string>
#include <vector>
#include <map>

#include <DirectXMath.h>

#include "swCommonLib/Common/RTTR.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "swGraphicAPI/Resources/SwapChain.h"

#include "swGraphicAPI/MockAssets/MockAsset.h"
#include "swGraphicAPI/MockAssets/MockAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockAssetLoader.h"
#include "swGraphicAPI/MockAssets/MockCompositeAsset.h"
#include "swGraphicAPI/MockAssets/MockCompositeAssetCreator.h"
#include "swGraphicAPI/MockAssets/MockCompositeAssetLoader.h"

#include "swCommonLib/System/File.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"



#undef min
#undef max
#undef RegisterClass


#endif // !DISABLE_PRECOMPILED_HEADER


