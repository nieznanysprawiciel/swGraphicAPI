/**
@file MockPixelShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "MockPixelShader.h"



//====================================================================================//
//			RTTR registration	
//====================================================================================//

RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockPixelShader >( "sw::MockPixelShader" );
}


//====================================================================================//
//			MockPixelShader	
//====================================================================================//

namespace sw
{


/**@brief */
MockPixelShader::MockPixelShader()
{}

/**@brief */
MockPixelShader::~MockPixelShader()
{}

/**@brief */
bool MockPixelShader::ReloadFromFile()
{

	return false;
}

/**@brief */
bool MockPixelShader::ReloadFromBinFile()
{

	return false;
}

/**@brief */
void					MockPixelShader::SaveShaderBinFile			( const std::wstring& fileName )
{
	assert( false );

}

/**@bref */
MockPixelShader*		MockPixelShader::CreateFromFile				( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	if( !filesystem::Path( fileName ).Exists() )
		return nullptr;

	return new MockPixelShader();
}

MockPixelShader*		MockPixelShader::CreateFromBinFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return nullptr;
}

}	// sw
