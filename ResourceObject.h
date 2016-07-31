#pragma once
/**@file ResourceObject.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Plik zawiera deklaracj� i definicj� klasy ResourceObject s�u��c�
do zliczania odwo�a� do obiektu.*/

#include "Common/EngineObject.h"


/**@brief Klasa u�atwiaj�ca zarz�dzanie odwo�aniami do asset�w.
@ingroup GraphicAPI

Obiekty asset�w (np. MaterialObject, TextureObject, VertexShaderObject, PixelShaderObject itp.) wymagaj� jakiego� systemu zapewniaj�cego wsp�dzielenie mi�dzy innymi obiektami.

Do ka�dego pojedynczego obiektu mog� istnie� wilokrotne odwo�ania w klasie Model3DFromFile,
a tak�e w obiektach dziedzicz�cych po @ref DynamicMeshActor oraz w modu�ach silnika.
Z tego wzgl�du istniej� zmienne m_assetReferences i m_objectReferences.
Pierwsza okre�la, ile razy wyst�puj� odwo�ania do obiektu w klasie Model3DFromFile.
(uwaga: nie zliczamy, ile klas si� odwo�uje. Je�eli w klasie pojawiaj� si� 3 odwo�ania, to licz� si� jako 3. Taka konwencja
u�atwia zliczanie i zwalnianie pami�ci)
Druga zmienna okre�la, ile wystepuje odwo�a� bezpo�rednich przez obiekty, kt�re b�d� nast�pnie wy�wietlane. Oznacza to, �e przypisuj�c
jakiemus obiektowi plik z modelem, musimy zinkrementowa� m_objectReferences o tyle, ile by�o odwo�a� w tym pliku.
�aden obiekt nie powinien by� kasowany, dop�ki istniej� do niego odwo�ania.

Zmienna m_uniqueId jest na pocz�tku ustawiana na 0. Jej faktyczne ustawienie odbywa robi klasa ResourceContainer.
Jest to wymagane do u�atwienia obs�ugi wielow�tkowo�ci. Inaczej mog�yby si� pokrywa� identyfikatory.

@todo Zliczanie referencji w ResourceObject nie nadaje si� do wielow�tkowo�ci. Poprawi� w odpowiednim momencie.
*/

class ResourceObject	: public EngineObject
{
	RTTR_ENABLE( EngineObject )
private:
	unsigned int	m_assetReferences;	///< Liczba asset�w, kt�re sie odwo�uj�.
	unsigned int	m_objectReferences;	///< Liczba obiekt�w aktor�w, kt�re si� odwo�uj�.
	unsigned int	m_uniqueId;			///< Unikalny identyfikator zasobu.

protected:
	virtual ~ResourceObject() = default;		///<Nie ka�dy mo�e skasowa� obiekt

public:
	/**
	Ustawia zerow� liczb� odwo�a�.*/
	ResourceObject( int id )
	{
		m_assetReferences = 0;
		m_objectReferences = 0;
		m_uniqueId = id;
	}


	inline void SetID( unsigned int id ) { m_uniqueId = id; }	///<Ustawia identyfikator obiektu

	///sprawdza czy mo�na zwolni� zmienn�
	inline bool CanDelete( unsigned int& assetRef, unsigned int& objectRef );
	inline bool CanDelete();

	/**Funkcje s�u��ce do zarz�dzania odwo�aniami.
	Nale�y pilnowa�, aby wszystkie funkcje, kt�re modyfikuj� jakiekolwiek przypisania obiekt�w
	do tekstur, materia��w i meshy, modyfikowa�y r�wnie� ilo�� odwo�a�.
	U�ytkownik silnika powinien mie� udost�pnion� wartstw� po�redniczac�, �eby nie musia�
	pami�ta� o odwo�aniach.*/
	inline void AddAssetReference()		{ ++m_assetReferences; }	///< Dodaje odwo�anie plikowe do assetu
	inline void AddObjectReference()	{ ++m_objectReferences; }	///< Dodaje odwo�anie bezpo�rednie obiektu do assetu
	inline void DeleteAssetReference()	{ --m_assetReferences; }	///< Kasuje odwo�anie plikowe do assetu
	inline void DeleteObjectReference()	{ --m_objectReferences; }	///< Kasuje odwo�anie bezpo�rednie obiektu do assetu

	inline unsigned int GetID()			{ return m_uniqueId; }		///< Zwraca identyfikator nadany assetowi
};




//----------------------------------------------------------------------------------------------//
//									ResourceObject											//
//----------------------------------------------------------------------------------------------//

//==============================================================================================//



/**@brief Funkcja informuje czy obiekt s� obiektu, kt�re odwo�uj� si� do assetu.

@param[out] file_ref W zmiennej zostanie umieszczona liczba referencji plikowych.
@param[out] other_ref W zmiennej zostanie umieszczona liczba referencji bezpo�rednich od obiekt�w.
@return Zwraca warto�� logiczn� m�wi�c� czy asset nadaje si� do usuni�cia.
*/
inline bool ResourceObject::CanDelete( unsigned int& assetRef, unsigned int& objectRef )
{
	assetRef = m_assetReferences;
	objectRef = m_objectReferences;

	if( m_assetReferences == 0 && m_objectReferences == 0 )
		return true;
	return false;
}

/**@brief Funkcja informuje czy obiekt s� obiektu, kt�re odwo�uj� si� do assetu.

@return Zwraca warto�� logiczn� m�wi�c� czy asset nadaje si� do usuni�cia.
*/
inline bool ResourceObject::CanDelete()
{
	if( m_assetReferences == 0 && m_objectReferences == 0 )
		return true;
	return false;
}
