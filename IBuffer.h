#pragma once
/**
@file IBuffer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "ReferencedObject.h"

class IBuffer	:	public referenced_object
{
private:

protected:
	IBuffer() : referenced_object( 0 ) {}
	virtual ~IBuffer();
public:

};

