#pragma once

/**@file ReferencedObject.h
@brief Plik zawiera deklaracj� i definicj� klasy referenced_object s�u��c�
do zliczania odwo�a� do obiektu.*/


/** \brief Klasa u�atwiaj�ca zarz�dzanie odwo�aniami do asset�w.
*
*Obiekty asset�w (np. MaterialObject, TextureObject, VertexShaderObject, PixelShaderObject itp.) wymagaj� jakiego� systemu zapewniaj�cego wsp�dzielenie mi�dzy innymi obiektami.
*
*Do ka�dego pojedynczego obiektu mog� istnie� wilokrotne odwo�ania w klasie Model3DFromFile,
*a tak�e w obiektach dziedzicz�cych po Dynamic_mesh_object.
*Z tego wzgl�du istniej� zmienne file_references i object_references.
*Pierwsza okre�la, ile razy wyst�puj� odwo�ania do obiektu w klasie Model3DFromFile.
*(uwaga: nie zliczamy, ile klas si� odwo�uje. Je�eli w klasie pojawiaj� si� 3 odwo�ania, to licz� si� jako 3. Taka konwencja
*u�atwia zliczanie i zwalnianie pami�ci)
*Druga zmienna okre�la, ile wystepuje odwo�a� bezpo�rednich przez obiekty, kt�re b�d� nast�pnie wy�wietlane. Oznacza to, �e przypisuj�c
*jakiemus obiektowi plik z modelem, musimy zinkrementowa� other_references o tyle, ile by�o odwo�a� w tym pliku.
*�aden obiekt nie powinien by� kasowany, dop�ki istniej� do niego odwo�ania.

Zmienna unique_id jest na pocz�tku ustawiana na 0. Jej faktyczne ustawienie odbywa robi klasa ResourceContainer.
Jest to wymagane do u�atwienia obs�ugi wielow�tkowo�ci. Inaczej mog�yby si� pokrywa� identyfikatory.
**/

class referenced_object
{//definicja w pliku Model3DFormFile
private:
	unsigned int	file_references;	///< Liczba plik�w, kt�re sie odwo�uj�
	unsigned int	object_references;	///< Liczba modeli, kt�re si� odwo�uj�
	unsigned int	unique_id;			///< Unikalny identyfikator materia�u

protected:
	virtual ~referenced_object() = default;		///<Nie ka�dy mo�e skasowa� obiekt

public:
	/**
	Ustawia zerow� liczb� odwo�a�.*/
	referenced_object( int id )
	{
		file_references = 0;
		object_references = 0;
		unique_id = id;
	}


	inline void set_id( unsigned int id ) { unique_id = id; }	///<Ustawia identyfikator obiektu

	//sprawdza czy mo�na zwolni� zmienn�
	inline bool can_delete( unsigned int& file_ref, unsigned int& other_ref );

	/*Funkcje s�u��ce do zarz�dzania odwo�aniami.
	*Nale�y pilnowa�, aby wszystkie funkcje, kt�re modyfikuj� jakiekolwiek przypisania obiekt�w
	*do tekstur, materia��w i meshy, modyfikowa�y r�wnie� ilo�� odwo�a�.
	*U�ytkownik silnika powinien mie� udost�pnion� wartstw� po�redniczac�, �eby nie musia�
	*pami�ta� o odwo�aniach.*/
	inline void add_file_reference( ) { ++file_references; }		///< Dodaje odwo�anie plikowe do assetu
	inline void add_object_reference( ) { ++object_references; }	///< Dodaje odwo�anie bezpo�rednie obiektu do assetu
	inline void delete_file_reference( ) { --file_references; }		///< Kasuje odwo�anie plikowe do assetu
	inline void delete_object_reference( ) { --object_references; }	///< Kasuje odwo�anie bezpo�rednie obiektu do assetu

	inline unsigned int get_id() { return unique_id; }				///< Zwraca identyfikator nadany assetowi
};




//----------------------------------------------------------------------------------------------//
//									referenced_object											//
//----------------------------------------------------------------------------------------------//

//==============================================================================================//



/** \brief Funkcja informuje czy obiekt s� obiektu, kt�re odwo�uj� si� do assetu.

@param[out] file_ref W zmiennej zostanie umieszczona liczba referencji plikowych.
@param[out] other_ref W zmiennej zostanie umieszczona liczba referencji bezpo�rednich od obiekt�w.
@return Zwraca warto�� logiczn� m�wi�c� czy asset nadaje si� do usuni�cia.
*/
bool referenced_object::can_delete(unsigned int& file_ref, unsigned int& other_ref)
{
	file_ref = file_references;
	other_ref = object_references;

	if (file_references == 0 && object_references == 0)
		return true;
	return false;
}