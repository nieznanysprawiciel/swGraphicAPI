#pragma once
/**
@file IBuffer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "GraphicAPI/ResourceObject.h"

class IBuffer	:	public ResourceObject
{
private:

protected:
	IBuffer() : ResourceObject( 0 ) {}
	virtual ~IBuffer() = default;
public:

};

