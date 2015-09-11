#include "GraphicAPI/ResourcesFactory.h"

//----------------------------------------------------------------------------------------------//
//								PixelShaderObject												//
//----------------------------------------------------------------------------------------------//

#ifndef __UNUSED
/**@bref Tworzy obiekt PixelShaderObject na podstawie pliku.

W przypadku b��d�w kompilacji w trybie debug s� one przekierowane do okna Output.

Na razie obs�uguje tylko nieskompilowane pliki.
@param[in] fileName Nazwa pliku, z kt�rego zostanie wczytany shader.
@param[in] shaderName Nazwa funkcji, kt�ra jest punktem poczatkowym wykonania shadera.
@param[in] shaderModel �a�cuch znak�w opisuj�cy shader model.
*/
PixelShaderObject* PixelShaderObject::create_from_file( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return ResourcesFactory::CreatePixelShaderFromFile( fileName, shaderName, shaderModel );
}
#endif

//----------------------------------------------------------------------------------------------//
//								VertexShaderObject												//
//----------------------------------------------------------------------------------------------//

#ifndef __UNUSED
/**@brief Tworzy obiekt VertexShaderObject na podstawie pliku.

W przypadku b��d�w kompilacji w trybie debug s� one przekierowane do okna Output.

Na razie obs�uguje tylko nieskompilowane pliki.
@param[in] fileName Nazwa pliku, z kt�rego zostanie wczytany shader
@param[in] shaderName Nazwa funkcji, kt�ra jest punktem poczatkowym wykonania shadera
@param[in] shaderModel �a�cuch znak�w opisuj�cy shader model.
@return Zwraca wska�nik na obiekt VertexShaderObject lub nullptr w przypadku niepowodzenia.*/
VertexShaderObject* VertexShaderObject::create_from_file( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return ResourcesFactory::CreateVertexShaderFromFile( fileName, shaderName, shaderModel );
}

/**@brief Tworzy obiekt VertexShaderObject na podstawie pliku. Zwraca r�wnie� layout dla podanej struktury wierzcho�ka.
Nie nale�y u�ywa� tej funkcji, je�eli layout nie jest rzeczywi�cie potrzebny. Trzeba pamieta� o zwolnieniu
go, kiedy przestanie by� potrzebny.

W przypadku b��d�w kompilacji w trybie debug s� one przekierowane do okna Output.

Na razie obs�uguje tylko nieskompilowane pliki.
@param[in] fileName Nazwa pliku, z kt�rego zostanie wczytany shader
@param[in] shaderName Nazwa funkcji, kt�ra jest punktem poczatkowym wykonania shadera
@param[out] layout W zmiennej umieszczany jest wska�nik na layout wierzcho�ka. Nale�y pami�ta� o zwolnieniu go kiedy b�dzie niepotrzebny.
@param[in] layoutDesc Deskryptor opisujacy tworzony layout.
@param[in] shaderModel �a�cuch znak�w opisuj�cy shader model.
@return Zwraca wska�nik na obiekt VertexShaderObject lub nullptr w przypadku niepowodzenia.*/
VertexShaderObject* VertexShaderObject::create_from_file( const std::wstring& fileName,
														  const std::string& shaderName,
														  ShaderInputLayoutObject** layout,
														  InputLayoutDescriptor* layoutDesc,
														  const char* shaderModel )
{
	return ResourcesFactory::CreateVertexShaderFromFile( fileName, shaderName, layout, layoutDesc, shaderModel );
}

#endif

//----------------------------------------------------------------------------------------------//
//								TextureObject													//
//----------------------------------------------------------------------------------------------//


/**@brief Por�wnuje ze soba dwa obiekty tekstur.

Obiekty s� takie same, kiedy odwo�uj� si� do tego samego pliku.
*/
bool TextureObject::operator==( TextureObject& object)
{
	if (this->GetFileName() == object.GetFileName())
		return true;
	return false;
}

/**@brief Por�wnuje ze soba dwa obiekty tekstur.

Obiekty s� takie same, kiedy odwo�uj� si� do tego samego pliku.
*/
bool TextureObject::operator==(const std::wstring& fileName)
{
	if (this->GetFileName() == fileName)
		return true;
	return false;
}

#ifndef __UNUSED
/** @brief Tworzy z podanego pliku obiekt tekstury.

@param[in] fileName Nazwa pliku zawieraj�cego tekstur�
@return Zawraca stworzony wewn�trz obiekt TextureObject z wczytan� tekstur� lub nullptr w przypadku niepowodzenia.
*/
TextureObject* TextureObject::create_from_file( const std::wstring& fileName )
{
	return ResourcesFactory::CreateTextureFromFile( fileName );
}
#endif
//----------------------------------------------------------------------------------------------//
//								RenderTargetObject												//
//----------------------------------------------------------------------------------------------//


RenderTargetObject::RenderTargetObject( TextureObject* colorBuffer, TextureObject* depthStencil )
	: m_colorBuffer( colorBuffer ),
	m_depthStencilBuffer( depthStencil )
{
	if( m_colorBuffer )
		m_colorBuffer->add_file_reference();
	if( m_depthStencilBuffer )
		m_depthStencilBuffer->add_file_reference();
}

/**@brief Destruktor kasuje obiekty tekstury g��boko�ci i bufora koloru, je�eli nie s� u�ywane.
Je�eli istniej� odwo�ania do tych obiekt�w, to nie s� one kasowane, a jedynie usuwa si� odwo�ania
pochodz�ce od RenderTargetObject.*/
RenderTargetObject::~RenderTargetObject()
{
	if( m_colorBuffer )
	{
		m_colorBuffer->delete_file_reference();
		if( m_colorBuffer->can_delete() )
			ObjectDeleter<TextureObject>::delete_object( m_colorBuffer, ObjectDeleterKey<TextureObject>() );		
	}
	if( m_depthStencilBuffer )
	{
		m_depthStencilBuffer->delete_file_reference();
		if( m_depthStencilBuffer->can_delete() )
			ObjectDeleter<TextureObject>::delete_object( m_depthStencilBuffer, ObjectDeleterKey<TextureObject>() );
	}
}

//----------------------------------------------------------------------------------------------//
//								BufferObject													//
//----------------------------------------------------------------------------------------------//

BufferObject::BufferObject( unsigned int elementSize, unsigned int elementCount )
	:	m_elementSize( elementSize ),
		m_elementCount( elementCount )
{
}


#ifndef __UNUSED
/**@brief Tworzy bufor wierzcho�k�w lub indeks�w o podanych parametrach.

@param[in] buffer Wska�nik na bufor z danym, kt�re maj� by� przeniesione do bufora DirectXowego.
@param[in] element_size Rozmiar pojedynczego elementu w buforze
@param[in] vert_count Liczba wierzcho�k�w/indeks�w w buforze
@param[in] bind_flag Okre�la z czym zwi�za� podany bufor w potoku graficznym.
Dla bufora wierzcho�k�w nale�y poda� D3D11_BIND_VERTEX_BUFFER, a dla bufora indeks�w
D3D11_BIND_INDEX_BUFFER.
@param[in] usage Jedna z warto�ci D3D11_USAGE, kt�r� nale�y poda� DirectXowi.
@return Wska�nik na BufferObject w przypadku powodzenia lub nullptr, je�eli co� p�jdzie nie tak.*/
BufferObject* BufferObject::create_from_memory( const void* buffer,
												unsigned int element_size,
												unsigned int vert_count,
												ResourceBinding bind_flag,
												ResourceUsage usage )
{
	return ResourcesFactory::CreateBufferFromMemory( buffer, element_size, vert_count, bind_flag, usage );
}

#endif

//----------------------------------------------------------------------------------------------//
//								MaterialObject													//
//----------------------------------------------------------------------------------------------//

MaterialObject::MaterialObject( const MaterialObject* material )
: ResourceObject(WRONG_ID)
{
	memcpy( this, material, sizeof(MaterialObject) );
}

/**@brief Ustawia materia� na warto�ci domy�lne dla silnika.

Te warto�ci s� najbardziej neutralne, w przypadku gdy nie ma materia�u, a jest ustawiona tekstura.
Wtedy shadery wymana�aj� jasno�� piksela przez 1.0 i nic sie nie zmienia.*/
void MaterialObject::SetNullMaterial( )
{
	Diffuse.x = 1.0f;
	Diffuse.y = 1.0f;
	Diffuse.z = 1.0f;
	Diffuse.w = 1.0f;

	Ambient.x = 1.0f;
	Ambient.y = 1.0f;
	Ambient.z = 1.0f;
	Ambient.w = 1.0f;

	Specular.x = 1.0f;
	Specular.y = 1.0f;
	Specular.z = 1.0f;
	Specular.w = 1.0f;

	Emissive.x = 1.0f;
	Emissive.y = 1.0f;
	Emissive.z = 1.0f;
	Emissive.w = 1.0f;

	Power = 1.0f;
}


