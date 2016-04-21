#include "GraphicAPI/ResourcesFactory.h"

#include "Common/MemoryLeaks.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< ResourceObject >( "ResourceObject" );
	RTTR_REGISTRATION_STANDARD_TYPE_VARIANTS( std::wstring )
}


//----------------------------------------------------------------------------------------------//
//								PixelShaderObject												//
//----------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------//
//								VertexShaderObject												//
//----------------------------------------------------------------------------------------------//


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

//----------------------------------------------------------------------------------------------//
//								RenderTargetObject												//
//----------------------------------------------------------------------------------------------//


RenderTargetObject::RenderTargetObject( TextureObject* colorBuffer, TextureObject* depthBuffer, TextureObject* stencilBuffer )
	: m_colorBuffer( colorBuffer ),
	m_depthBuffer( depthBuffer ),
	m_stencilBuffer( stencilBuffer )
{
	if( m_colorBuffer )
		m_colorBuffer->AddAssetReference();
	if( m_depthBuffer )
		m_depthBuffer->AddAssetReference();
	if( m_stencilBuffer )
		m_stencilBuffer->AddAssetReference();
}

/**@brief Destruktor kasuje obiekty tekstury g��boko�ci i bufora koloru, je�eli nie s� u�ywane.
Je�eli istniej� odwo�ania do tych obiekt�w, to nie s� one kasowane, a jedynie usuwa si� odwo�ania
pochodz�ce od RenderTargetObject.*/
RenderTargetObject::~RenderTargetObject()
{
	if( m_colorBuffer )
	{
		m_colorBuffer->DeleteAssetReference();
		//if( m_colorBuffer->CanDelete() )
		//	ObjectDeleter<TextureObject>::delete_object( m_colorBuffer, ObjectDeleterKey<TextureObject>() );
	}
	if( m_depthBuffer )
	{
		m_depthBuffer->DeleteAssetReference();
		//if( m_depthBuffer->CanDelete() )
		//	ObjectDeleter<TextureObject>::delete_object( m_depthBuffer, ObjectDeleterKey<TextureObject>() );
	}
	if( m_stencilBuffer )
	{
		m_stencilBuffer->DeleteAssetReference();
		//if( m_stencilBuffer->CanDelete() )
		//	ObjectDeleter<TextureObject>::delete_object( m_stencilBuffer, ObjectDeleterKey<TextureObject>() );
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


