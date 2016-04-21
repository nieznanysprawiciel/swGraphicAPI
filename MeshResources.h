#pragma once
/**
@file MeshResources.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Plik zawiera deklaracje format�w wierzcho�k�w oraz klas zawieraj�cych assety shadery itp.
*/


#include "Common/ObjectDeleter.h"
#include "Common/MacrosSwitches.h"

#include "GraphicAPI/ResourceObject.h"
#include "GraphicAPI/ITexture.h"
#include "GraphicAPI/IShader.h"
#include "GraphicAPI/IBuffer.h"
#include "GraphicAPI/IRenderTarget.h"
#include "IShaderInputLayout.h"
#include "GraphicAPI/GraphicAPIConstants.h"
#include "DirectXMath.h"


//definicje
/** @def WRONG_ID
B��dny identyfikator assetu w klasie @ref ResourceObject.*/
#define WRONG_ID						0

/**@defgroup Resources Zasoby
@ingroup ResourcesManagment
@ingroup GraphicAPI
@brief Klasy zasob�w przechowywanych przez silnik.

Zasoby s� silnie zale�ne od u�ywanej platformy sprz�towej. W celu oddzielenia referencji do
API graficznego od @ref EngineCore, wszystkie obiekty silnika u�ywaj� jedynie klas bazowych, kt�re
s� implementowane przez poszczeg�lne API graficzne. Aby zobaczy� konkretne implementacje tych klas
zobacz @ref GraphicAPI.

Zasoby nigdy nie s� tworzone bezpo�rednio. Zamiast tego u�ywa si� klasy @ref ResourcesFactory, kt�r�
implementuje konkretne API graficzne.

Poniewa� zasoby mog� by� wsp�dzielone przez wiele obiekt�w w silniku, istnieje mechanizm zliczania
odwo�a� do obiekt�w implementowany przez klas� @ref ResourceObject.*/

class ModelsManager;
struct ModelPart;
class BufferObject;
class TextureObject;
class VertexShaderObject;
class PixelShaderObject;
struct MeshPartObject;
struct MaterialObject;

/*
// W buforze wierzcho�k�w znajduj� si� elementy typu VERT_INDEX.
// Definicja typu VERT_INDEX znajduje si� w pliku macros_switches.h i wygl�da tak:

#if defined(INDEX_BUFFER_UINT16)
typedef UINT16 VERT_INDEX;
#elif defined(INDEX_BUFFER_UINT32)
typedef UINT32 VERT_INDEX;
#else
typedef UINT32 VERT_INDEX;
#endif

*/


static const std::wstring RENDER_TARGET_COLOR_BUFFER_NAME = L"::color";
static const std::wstring RENDER_TARGET_DEPTH_BUFFER_NAME = L"::depth";
static const std::wstring RENDER_TARGET_STENCIL_BUFFER_NAME = L"::stencil";


/**@brief Indeksy tekstur w tablicy ModelPart.

S� to warto�ci domy�lne u�ywane przez wbudowane shadery.
W przypadku w�asnor�cznie pisanych shader�w nie trzeba si� trzyma� tych sta�ych.*/
enum TextureUse
{
#if ENGINE_MAX_TEXTURES > 0
	TEX_DIFFUSE			///<Tekstura dla kana�u diffuse
#endif
#if ENGINE_MAX_TEXTURES > 1
	, TEX_LIGHTMAP		///<Lightmapa
#endif
#if ENGINE_MAX_TEXTURES > 2
	, TEX_SPECULAR		///<Tekstura dla kana�u specular
#endif
#if ENGINE_MAX_TEXTURES > 3
	, TEX_BUMP_MAP		///<Bump mapa
#endif
#if ENGINE_MAX_TEXTURES > 4
	, TEX_AMBIENT		///<Tekstura dla kana�u ambient
#endif
#if ENGINE_MAX_TEXTURES > 5
	, TEX_DISPLACEMENT_MAP	///<Tekstura przemieszcze� wierzcho�k�w, w przypadku u�ywania teselacji wierzcho�k�w
#endif
#if ENGINE_MAX_TEXTURES > 6
	, TEX_OTHER1		///<Tekstura o dowolnym znaczeniu
#endif
#if ENGINE_MAX_TEXTURES > 7
	, TEX_OTHER2		///<Tekstura o dowolnym znaczeniu
#endif

};



//----------------------------------------------------------------------------------------------//
//								Mesh i Model													//
//----------------------------------------------------------------------------------------------//

/** @brief Struktura opisuje pojedyncz� cz�stk� mesha o jednym materiale, teksturze i shaderach.
@ingroup Resources
@ingroup GraphicAPI

W zale�no�ci od zawarto�ci pola index_buffer w strukturze ModelPart, mesh jest wy�wietlany w trybie
indeksowanym lub nie.
Je�eli warto�� tego pola wynosi nullptr, to wtedy u�ywane s� zmienne buffer offset i vertices count, kt�re jednoznacznie wskazuj�, kt�ra cz�� bufora wierzcho�k�w ma zosta� wy�wietlona.

Je�eli wska�nik index_buffer wskazuje na obiekt, to wtedy u�ywany jest tryb indeksowany
i zmienne buffer_offset, vertices_count i base_vertex.

Klasa jest alokowana w Model3DFromFile i to w�a�nie ta klasa odpowiada za zwolnienie pami�ci.

Pomimo dziedziczenia po klasie ResourceObject, nie jest u�ywane pole m_uniqueId. Dlatego
jest ono w kontruktorze ustawiane na WRONG_ID. MeshPartObject nie mog� by� wsp�dzielone
mi�dzy obiektami.*/
struct MeshPartObject : public ResourceObject
{
	DirectX::XMFLOAT4X4		transform_matrix;	///<Macierz przekszta�cenia wzgl�dem �rodka modelu
	unsigned int			buffer_offset;		///<Offset wzgl�dem pocz�tku bufora indeks�w albo wierzcho�k�w (zobacz: opis klasy)
	unsigned int			vertices_count;		///<Liczba wierzcho�k�w do wy�wietlenia
	int						base_vertex;		///<Warto�� dodawana do ka�dego indeksu przed przeczytaniem wierzcho�ka z bufora. (Tylko wersja indeksowana)
	bool					use_index_buf;		///<Informacja czy jest u�ywany bufor indeks�w czy nie
	
	/** @brief inicjuje objekt neutralnymi warto�ciami tzn. zerami, ustawia use_index_buf na false i
	ustawia macierz przekszta�cenia na macierz identyczno�ciow�.*/
	MeshPartObject( )
		: ResourceObject( 0 )		//W tym przypadku identyfikator nie ma znaczenia
	{
		buffer_offset = 0;
		vertices_count = 0;
		base_vertex = 0;
		use_index_buf = false;
		//domy�lnie nie wykonujemy �adnego przekszta�cenia
		DirectX::XMMATRIX identity = DirectX::XMMatrixIdentity( );
		XMStoreFloat4x4( &transform_matrix, identity );
	}
};

/** @brief Struktura opisuj�ca pojedyncz� cz�� mesha gotow� do wy�wietlenia.
@ingroup Resources
@ingroup GraphicAPI

Meshe s� przechowywane w cz�ciach, poniewa� do r�nych wierzcho�k�w mog� by� przypisane r�ne
materia�y, tekstury i inne elementy. Ta struktura zawiera wska�niki na te elementy.

Struktura nie zawiera bufora wierzcho�k�w ani bufora indeks�w. S� one przechowywane zewn�trznie
w klasie Model3DFromFile lub Dynamic_mesh_object i na jeden mesh przypada tylko jeden bufor wierzcho�k�w i maksymalnie
jeden bufor indeks�w (mo�e go nie by�). 

Obecno�c bufora indeks�w nie oznacza, �e ca�y mesh jest wy�wietlany w trybie indeksowanym. Mozliwe jest mieszanie tryb�w.
Tryb odnosi si� wi�c nie do ca�ego mesha, a pojednyczego obiektu ModelPart.

Tablica texture zawiera wska�niki na obiekty tekstur, kt�rych maksymalna liczba wynosi ENGINE_MAX_TEXTURES.
Aby obs�u�y� wszystkie tekstury jakie mog� byc przypisane do obiektu, nale�y poda� mu odpowiedni shader, kt�ry
umie to zrobi�. Znaczenie poszczeg�lnych p�l tablicy tekstur jest opisywane przez enumeracj� TextureUse
i w taki spos�b wykorzystuj� je domy�lne shadery.
*/
struct ModelPart
{
	VertexShaderObject*		vertex_shader;
	PixelShaderObject*		pixel_shader;
	MaterialObject*			material;
	TextureObject*			texture[ENGINE_MAX_TEXTURES];
	MeshPartObject*			mesh;

	ModelPart( )
	{
		vertex_shader = nullptr;
		pixel_shader = nullptr;
		material = nullptr;
		mesh = nullptr;

#if ENGINE_MAX_TEXTURES > 0
		texture[0] = nullptr;
#endif
#if ENGINE_MAX_TEXTURES > 1
		texture[1] = nullptr;
#endif
#if ENGINE_MAX_TEXTURES > 2
		texture[2] = nullptr;
#endif
#if ENGINE_MAX_TEXTURES > 3
		texture[3] = nullptr;
#endif
#if ENGINE_MAX_TEXTURES > 4
		texture[4] = nullptr;
#endif
#if ENGINE_MAX_TEXTURES > 5
		texture[5] = nullptr;
#endif
#if ENGINE_MAX_TEXTURES > 6
		texture[6] = nullptr;
#endif
#if ENGINE_MAX_TEXTURES > 7
		texture[7] = nullptr;
#endif
	}
};

//----------------------------------------------------------------------------------------------//
//								TextureObject													//
//----------------------------------------------------------------------------------------------//


/** @brief Klasa przechowuj�ca tekstury.
@ingroup Resources
@ingroup GraphicAPI

Klasa bazowa, kt�ra b�dzie u�ywana przez obiekty silnika.
Powinny po niej odziedziczy� obiekty konkretnego API graficznego,
�eby zaimplementowa� najwa�niejsze funkcjonalno�ci.*/
class TextureObject : public ITexture
{
	friend ObjectDeleter<TextureObject>;
private:
protected:
	std::wstring				m_fileName;		///<Plik, z kt�rego powsta�a tekstura lub po prostu nazwa tekstury, je�eli zosta�a wygenerowana.

	//�eby unikn�� pomy�ki, obiekt mo�e by� kasowany tylko przez ModelsManager. Zapewnia to ObjectDeleter.
	~TextureObject() = default;
public:
	TextureObject() = default;
	std::wstring&	GetFileName() { return m_fileName; }		///<Zwraca nazw� pliku, kt�ry pos�u�y� do stworzenia obiektu.

	inline bool operator==( TextureObject& object );
	inline bool operator==( const std::wstring& file_name );
};

//----------------------------------------------------------------------------------------------//
//								RenderTargetObject												//
//----------------------------------------------------------------------------------------------//

/**@brief Struktura u�ywana do tworzenia render targetu.
@ingroup GraphicAPI*/
struct RenderTargetDescriptor
{
	uint16				textureWidth;				///<Sszeroko�� tekstury w pikselach.
	uint16				textureHeight;				///<Wysoko�� tekstury w pikselach.
	uint16				arraySize;					///<Liczba element�w tablicy.
	int8				CPURead : 1;				///<Pozwala na odczyt tekstury przez CPU.
	int8				CPUWrite : 1;				///<Pozwala na zapis tekstury przez CPU.
	int8				allowShareResource : 1;		///<Pozwala na dost�p do zasoby z wielu API graficznych i pomi�dzy kontekstami.
	int8				isCubeMap : 1;				///<Nale�y ustawi� je�eli tekstura jest cubemap�.
	uint8				numSamples;					///<Liczba pr�bek w przypadku stosowania multisamplingu.
	uint16				samplesQuality;				///<Jako�� pr�bek przy multisamplingu.
	TextureType			textureType;				///<Typ tekstury (liczba wymiar�w, multsampling). Tekstura nie mo�e by� inna ni� dwuwymiarowa (mo�e by� tablic�).
	ResourceFormat		colorBuffFormat;			///<Format bufora kolor�w.
	DepthStencilFormat	depthStencilFormat;			///<Format bufora g��boko�ci i stencilu.
	ResourceUsage		usage;						///<Spos�b u�ycia render targetu. Wp�ywa na optymalizacje u�o�enia w pami�ci.

	/**@brief Ustawia domy�lne warto�ci deskryptora.
	
	Ustawiane s� pola CPURead, CPUWrite, allowShareResource, isCubeMap, usage.
	Te zmienne s� u�ywane rzadko i dlatego powinny mie� takie warto�ci, �eby nie trzeba by�o ich jawnie ustawia�.
	Pozosta�e warto�ci u�ytkownik i tak musi zdefiniowa� samemu, wi�c nie ma co nadk�ada� pracy.
	
	Pola numSamples i samplesQuality s� ignorowane, je�eli textureType nie zosta� ustawiony na tekstur� z multisamplingiem.
	Pole arraySize jest ignorowane, je�eli tekstura nie jest tablic�.*/
	RenderTargetDescriptor()
	{
		CPURead = 0;
		CPUWrite = 0;
		allowShareResource = 0;
		isCubeMap = 0;
		usage = ResourceUsage::RESOURCE_USAGE_DEFAULT;
	}
};

/**@brief Klasa dla render target�w.
@ingroup Resources
@ingroup GraphicAPI

Klasa umo�liwia pobranie jednej z tekstur sk�adowych i udost�pnienie dla shader�w.
Je�eli API graficzne nie pozwala na oddzielne trzymanie bufora g��boko�ci i stencilu,
to mo�e tu by� przechowywany ten sam obiekt. Ewentualnie mog� by� to dwa obiekty,
kt�re przechowuj� inny widok, ale fizycznie odwo�uj� si� do tej samej pami�ci.*/
class RenderTargetObject : public IRenderTarget
{
private:
protected:
	TextureObject*			m_colorBuffer;			///<Pozwala na dost�p do bufora kolor�w dla innych obiekt�w. Mo�e by� nullptrem.
	TextureObject*			m_depthBuffer;			///<Pozwala na dost�p do bufora g��boko�ci. Mo�e by� nullptrem.
	TextureObject*			m_stencilBuffer;		///<Pozwala na dost�p do bufora stencil. Mo�e by� nulltrem.
public:
	RenderTargetObject( TextureObject* colorBuffer, TextureObject* depthBuffer, TextureObject* stencilBuffer );
	virtual ~RenderTargetObject();

	inline TextureObject*		GetColorBuffer()			{ return m_colorBuffer; }		///<Zwraca obiekt bufora kolor�w.
	inline TextureObject*		GetDepthBuffer()			{ return m_depthBuffer; }		///<Zwraca obiekt bufora g��boko�ci.
	inline TextureObject*		GetStencilBuffer()			{ return m_stencilBuffer; }		///<Zwraca obiekt bufora stencilu.
};

//----------------------------------------------------------------------------------------------//
//								ShaderInputLayoutObject											//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuje layout wierzcho�ka trafiaj�cego do
vertex shadera.
@ingroup Resources
@ingroup GraphicAPI*/
class ShaderInputLayoutObject : public IShaderInputLayout
{
	friend ObjectDeleter<ShaderInputLayoutObject>;
private:
protected:
	virtual ~ShaderInputLayoutObject() = default;
public:
	ShaderInputLayoutObject() = default;
};

/**@brief Klasa przechowuje opis layoutu wierzcho�ka, na podstawie kt�rego
tworzony jest obiekt layoutu.
@ingroup GraphicAPI*/
class InputLayoutDescriptor
{
private:
	std::wstring				m_inputLayoutName;
protected:
public:
	InputLayoutDescriptor( const std::wstring& layoutName ) : m_inputLayoutName( layoutName ){}
	virtual ~InputLayoutDescriptor() = default;

	virtual void		AddRow		( const char* semanticName, ResourceFormat format, unsigned int inputSlot, unsigned int byteOffset, bool perInstance, unsigned int instanceDataStep ) = 0;

	std::wstring&		GetName		() { return m_inputLayoutName; }
};


//----------------------------------------------------------------------------------------------//
//								VertexShaderObject												//
//----------------------------------------------------------------------------------------------//

/** @brief Klasa przechowuj�ca vertex shader.
@ingroup Resources
@ingroup GraphicAPI*/
class VertexShaderObject : public IShader
{
	friend ObjectDeleter<VertexShaderObject>;
private:
protected:
	~VertexShaderObject() = default;
public:
	VertexShaderObject() = default;
};

//----------------------------------------------------------------------------------------------//
//								PixelShaderObject												//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuj�ca pixel shader.
@ingroup Resources
@ingroup GraphicAPI*/
class PixelShaderObject : public IShader
{
	friend ObjectDeleter<PixelShaderObject>;
private:
protected:
	~PixelShaderObject() = default;
public:
	PixelShaderObject() = default;
};

//----------------------------------------------------------------------------------------------//
//								ComputeShaderObject												//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuj�ca compute shader
@ingroup Resources
@ingroup GraphicAPI*/
class ComputeShaderObject : public IShader
{
	friend ObjectDeleter<ComputeShaderObject>;
private:
protected:
	~ComputeShaderObject() = default;
public:
	ComputeShaderObject() = default;
};

//----------------------------------------------------------------------------------------------//
//								BufferObject													//
//----------------------------------------------------------------------------------------------//

/**@brief Obiekt opakowuj�cy bufor.
@ingroup Resources
@ingroup GraphicAPI

Bufor mo�e by� zar�wno buforem wierzcho�k�w, indeks�w jak i sta�ych.
*/
class BufferObject : public IBuffer
{
	friend ObjectDeleter<BufferObject>;
protected:
	unsigned int		m_elementSize;			///<Rozmiar elementu.
	unsigned int		m_elementCount;			///<Liczba element�w.

	~BufferObject() = default;
public:
	BufferObject( unsigned int elementSize, unsigned int elementCount );

	inline unsigned int GetStride()				{ return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int	GetElementSize()		{ return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int GetElementCount()		{ return m_elementCount; }		///<Zwraca liczb� element�w w buforze.
};

//----------------------------------------------------------------------------------------------//
//								MaterialObject													//
//----------------------------------------------------------------------------------------------//


/**@brief Struktura przechowuj�ca materia�.
@ingroup Resources
@ingroup GraphicAPI

DirectX 11 nie ma w�asnych obiekt�w na materia�y, poniewa� nie ma ju� domy�lnego
potoku przetwarzania na karcie graficznej. Na wszystko trzeba napisa� shader i dostarcza
mu si� takie dane, jakie si� chce dostarczy�. Dlatego informacja o materia�ach b�dzie
przekazywana z buforze sta�ych.

Struktura zachowuje si� jak asset w zwi�zku z czym mo�e
by� wsp�dzielona przez wiele obiekt�w. Z tego wzgl�du nie mo�na jej u�y� bezpo�rednio w ConstantPerMesh,
poniewa� nie chcemy przekazywa� do bufora sta�ych zmiennych odziedziczonych po ResourceObject.
Zamiast tego trzeba t� strukture przepisa�.

Zwracam uwag�, �e tylko kana� Diffuse jest wektorem 4 wymiarowym, w kt�rym sk�adowa w jest odpowiedzialna
za przezroczysto��. Pozosta�e s� takie tylko dlatego, �e jest to domy�lny format przechowywania danych 
w rejestrach karty graficznej i przyspiesza to operacj� kopiowania.
@see ConstantPerFrame
*/
typedef struct MaterialObject : public ResourceObject
{
	friend ObjectDeleter<MaterialObject>;

	DirectX::XMFLOAT4		Diffuse;		//Sk�adowa przezroczysto�ci odnosi si� do ca�ego materia�u
	DirectX::XMFLOAT4		Ambient;
	DirectX::XMFLOAT4		Specular;
	DirectX::XMFLOAT4		Emissive;
	float					Power;

	MaterialObject( unsigned int id = WRONG_ID ) : ResourceObject( id ){}
	MaterialObject( const MaterialObject* material );

	void SetNullMaterial();
} MaterialObject;


