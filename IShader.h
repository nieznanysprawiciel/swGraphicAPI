#pragma once
/**
@file IShader.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/


#include "GraphicAPI/ResourceObject.h"
#include <string>

class IShader	:	public ResourceObject
{
private:
protected:
	std::string				m_shaderEntry;			///< Nazwa g�ownej funkcji shadera.
	std::wstring			m_shaderFile;			///< �cie�ka do pliku z shaderem.
protected:
	IShader() : ResourceObject( 0 ) {}
	virtual ~IShader() = default;
public:
	std::wstring&			GetShaderFile()		{ return m_shaderFile; }
	std::string&			GetShaderEntry()	{ return m_shaderEntry; }


	virtual bool			ReloadFromFile			() = 0;
	virtual bool			ReloadFromBinFile		() = 0;
	virtual void			SaveShaderBinFile		( const std::wstring& file_name ) = 0;
};

