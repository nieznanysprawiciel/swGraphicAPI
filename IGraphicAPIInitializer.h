#pragma once
/**
@file IGraphicAPIInitializer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Deklaracja interfejsu IGraphicAPIInitializer.
*/

#include "GraphicAPI/IRenderer.h"
#include "Common/TypesDefinitions.h"

#include <string>

/**@defgroup GraphicAPI
@ingroup ModulesStructure
@brief Interfejsy dla obiekt�w zasob�w, renderera i initializera.

@EngineCore jest niezale�ny od konkretnej implementacji API graficznego, kt�ra
zosta�a u�yta. W tym celu w tym projekcie zgromadzone s� wszystkie interfejsy,
kt�re powinny zosta� zaimplementowane przez dziedzicz�ce API oraz zestawy sta�ych silnikowych
niezale�nych od platformy.

Pliki w tym projekcie powinny zosta� w��czone do ka�dego projektu, kt�ry u�ywa b�d�
implementuje API graficzne. Opr�cz interfejs�w do zaimplementowania, projekt zawiera te�
pliki .cpp, kt�re powinny by� skompilowane do biblioteki statycznej razem z poszczeg�lnymi API graficznymi.*/


/**@brief Przechowuje informacje potrzebne do inicjalizacji
API graficznego. Parametr dla funkcji @ref IGraphicAPIInitializer::InitAPI.
@ingroup GraphicAPI*/
struct GraphicAPIInitData
{
	uint16 windowWidth;
	uint16 windowHeight;
	uint32 windowHandle;
	bool singleThreaded;
	bool fullScreen;
	ResourceFormat depthStencilFormat;

	void DefaultSettings()
	{
		windowWidth = 1024;
		windowHeight = 768;
		singleThreaded = true;
		fullScreen = false;
		depthStencilFormat = ResourceFormat::RESOURCE_FORMAT_D24_UNORM_S8_UINT;
	}
};

/**@brief Interfejs klasy do inicjowania API graficznego.

Klasa powinna zosta� zainicjowana przez dziedziczace API graficzne.
Podstawowymi funkcjonalno�ciami klasy jest:
- zainicjowanie i zwolnienie API
- stworzenie renderer�w*/
class IGraphicAPIInitializer
{
private:
protected:
public:
	virtual ~IGraphicAPIInitializer() = default;

	virtual IRenderer*		CreateRenderer			( RendererUsage usage ) = 0;
	virtual bool			InitAPI					( GraphicAPIInitData& initData ) = 0;
	virtual void			ReleaseAPI				() = 0;

	// Future
	// virtual std::wstring	GetErrorString() = 0;
	// virtual void			Resize( uint16 newWidth, uint16 newHeight ) = 0;
};
