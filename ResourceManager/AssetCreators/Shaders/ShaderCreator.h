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
template< typename ShaderObjectType >
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

	VertexShader*					CreateVertexShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	PixelShader*					CreatePixelShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	GeometryShader*					CreateGeometryShader		( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	ControlShader*					CreateControlShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	EvaluationShader*				CreateEvaluationShader		( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	ComputeShader*					CreateComputeShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );

};






}	// sw



