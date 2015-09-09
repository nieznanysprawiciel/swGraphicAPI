#pragma once
/**
@file DX11InputLayout.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "GraphicAPI/MeshResources.h"
#include "../DX11Initializer/DX11APIObjects.h"


class DX11InputLayout : public ShaderInputLayout, public DX11APIObjects
{
private:
	ID3D11InputLayout*				m_vertexLayout;
protected:
	~DX11InputLayout();
public:
	DX11InputLayout( ID3D11InputLayout* layout );

	inline ID3D11InputLayout*		Get() { return m_vertexLayout; }
};

