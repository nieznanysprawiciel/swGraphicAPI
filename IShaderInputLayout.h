#pragma once
/**
@file IShader.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/


#include "GraphicAPI/ResourceObject.h"

class IShaderInputLayout : public ResourceObject
{
private:
protected:
	IShaderInputLayout() : ResourceObject( 0 ) {}
	virtual ~IShaderInputLayout() = default;
public:

};

