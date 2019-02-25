/**
@file MockVertexShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "MockVertexShader.h"

#include "MockInputLayoutDescriptor.h"
#include "MockInputLayout.h"

#include "swCommonLib/System/Path.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockVertexShader >( "sw::MockVertexShader" );
}


namespace sw
{


MockVertexShader::MockVertexShader()
{}

MockVertexShader::~MockVertexShader()
{}


bool MockVertexShader::ReloadFromFile()
{

	return false;
}

bool MockVertexShader::ReloadFromBinFile()
{

	return false;
}

void MockVertexShader::SaveShaderBinFile( const std::wstring& file_name )
{


}

// ================================ //
//
Nullable< MockVertexShader* >			MockVertexShader::CreateFromCode		( const std::wstring& fileName, const std::string& code, const std::string& entrypoint )
{
	if( code.empty() )
		return "Empty shader code.";

	auto shader = new MockVertexShader();
	
	shader->SetFileName( fileName );
	shader->SetShaderName( entrypoint );

	return shader;
}


// ================================ //
//
MockVertexShader* MockVertexShader::CreateFromFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	if( !filesystem::Path( fileName ).Exists() )
		return nullptr;

	return new MockVertexShader();
}

/**@brief Tworzy obiekt MockVertexShader oraz MockInputLayout na podstawie pliku. Zwraca również layout dla podanej struktury wierzchołka.
Nie należy używać tej funkcji, jeżeli layout nie jest rzeczywiście potrzebny. Trzeba pamietać o zwolnieniu
go, kiedy przestanie być potrzebny.

W przypadku błędów kompilacji w trybie debug są one przekierowane do okna Output.

Na razie obsługuje tylko nieskompilowane pliki.
@param[in] fileName Nazwa pliku, z którego zostanie wczytany shader
@param[in] shaderName Nazwa funkcji, która jest punktem poczatkowym wykonania shadera
@param[out] layout W zmiennej umieszczany jest wskaźnik na layout wierzchołka. Należy pamiętać o zwolnieniu go kiedy będzie niepotrzebny.
@param[in] layoutDesc Deskryptor opisujacy tworzony layout.
@param[in] shaderModel Łańcuch znaków opisujący shader model.
@return Zwraca wskaźnik na obiekt VertexShader lub nullptr w przypadku niepowodzenia.*/
MockVertexShader* MockVertexShader::CreateFromFile		( const std::wstring& fileName,
														  const std::string& shaderName,
														  ShaderInputLayout** layout,
														  InputLayoutDescriptor* layoutDesc,
														  const char* shaderModel/* = "vs_4_0" */ )
{
	if( !filesystem::Path( fileName ).Exists() )
		return nullptr;

	MockVertexShader* newShader = new MockVertexShader();
	*layout = new MockInputLayout();
	return newShader;
}


MockVertexShader* MockVertexShader::CreateFromBinFile( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{

	return nullptr;
}

}	// sw
