#include "DX11Texture.h"

#include "../DX11Initializer/DX11ConstantsMapper.h"

#include "Common/MemoryLeaks.h"




DX11Texture::DX11Texture( TextureInfo&& texInfo, ID3D11Texture2D* tex, ID3D11ShaderResourceView* texView )
	:	m_texture( tex )
	,	m_textureView( texView )
	,	m_descriptor( std::move( texInfo ) )
{}

DX11Texture::~DX11Texture()
{
	if( m_texture )
		m_texture->Release();
	m_texture = nullptr;
}


/**@copydoc TextureObject::GetDescriptor.*/
const TextureInfo&			DX11Texture::GetDescriptor() const
{
	return m_descriptor;
}

/**@copydoc TextureObject::GetFilePath.*/
const filesystem::Path&		DX11Texture::GetFilePath() const
{
	return m_descriptor.FilePath;
}


/**@brief Tworzy tekstur� z podanego wska�nika.

@return Zawraca stworzony wewn�trz obiekt DX11Texture z wczytan� tekstur� lub nullptr w przypadku niepowodzenia.*/
DX11Texture*	DX11Texture::CreateFromMemory( const MemoryChunk& texData, TextureInfo&& texInfo )
{
	if( texData.IsNull() )
		return nullptr;

	/// @todo Trzeba zacz�� kiedy� ob��ugiwac inne typy tekstur.
	assert( texInfo.TextureType == TextureType::TEXTURE_TYPE_TEXTURE2D );
	if( texInfo.TextureType != TextureType::TEXTURE_TYPE_TEXTURE2D )
		return nullptr;

	ID3D11Texture2D* texture = nullptr;
	ID3D11ShaderResourceView* texView = nullptr;
	D3D11_TEXTURE2D_DESC texDesc = FillDesc( texInfo );

	std::unique_ptr< D3D11_SUBRESOURCE_DATA[] > initData( new D3D11_SUBRESOURCE_DATA[ texInfo.MipMapLevels /** texInfo.ArraySize*/ ] );
	uint16 mipWidth = texInfo.TextureWidth;
	uint16 mipHeight = texInfo.TextureHeight;
	PtrOffset offset = 0;

	for( int level = 0; level < texInfo.MipMapLevels; level++ )
	{
		initData[ level ].pSysMem = texData.GetMemory< int8 >() + offset;
		initData[ level ].SysMemPitch = (uint32)mipWidth * BytesPerPixel( texInfo.Format );

		offset += mipWidth * mipHeight * BytesPerPixel( texInfo.Format );

		mipWidth /= 2;
		mipHeight /= 2;
		if( mipHeight == 0 )	mipHeight = 1;
		if( mipWidth == 0 )		mipWidth = 1;
	}

	HRESULT result = device->CreateTexture2D( &texDesc, initData.get(), &texture );
	if( result == S_OK )
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;

		if( texInfo.TextureType == TextureType::TEXTURE_TYPE_TEXTURE2D )
		{
			viewDesc.Format = texDesc.Format;
			viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			viewDesc.Texture2D.MostDetailedMip = 0;
			viewDesc.Texture2D.MipLevels = texInfo.MipMapLevels;

			result = device->CreateShaderResourceView( texture, &viewDesc, &texView );
			if( result == S_OK )
				return new DX11Texture( std::move( texInfo ), texture, texView );
			else 
				return nullptr;
		}
		
		assert( !"Other texture types are not suported" );
	}

	return nullptr;
}


/**@brief Zwraca zawarto�� tekstury.

@attention Funkcja wywo�uje metod� DeviceContextu. Mo�e by� problem z synchronizacj�, je�eli
wiele w�tk�w b�dzie wywo�ywa�o jakie� funkcje z kontekstu jednocze�nie.*/
MemoryChunk					DX11Texture::CopyData() const
{
	D3D11_TEXTURE2D_DESC texDesc = FillDesc( m_descriptor );
	texDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_READ;
	texDesc.Usage			= D3D11_USAGE::D3D11_USAGE_STAGING;

	ID3D11Texture2D* newTex;

	HRESULT result = device->CreateTexture2D( &texDesc, nullptr, &newTex );
	if( FAILED( result ) )
		return MemoryChunk();


	// Kopiowanie zawarto�ci mi�dzy buforami
	device_context->CopyResource( newTex, m_texture );

	assert( m_descriptor.MemorySize != 0 );

	MemoryChunk memoryChunk( m_descriptor.MemorySize );
	PtrOffset offset = 0;

	for( int level = 0; level < m_descriptor.MipMapLevels; level++ )
	{
		D3D11_MAPPED_SUBRESOURCE data;
		result = device_context->Map( newTex, level, D3D11_MAP::D3D11_MAP_READ, 0, &data );
		if( FAILED( result ) )
			return MemoryChunk();

		memcpy( memoryChunk.GetMemory< uint8 >() + offset, data.pData, data.RowPitch << ( m_descriptor.MipMapLevels - level - 1 ) );

		device_context->Unmap( newTex, level );
	}

	
	newTex->Release();

	return std::move( memoryChunk );
}

/**@brief Tworzy deskryptor tekstury 2D na podstawie deskryptora.*/
D3D11_TEXTURE2D_DESC			DX11Texture::FillDesc	( const TextureInfo& texInfo )
{
	D3D11_TEXTURE2D_DESC texDesc;

	unsigned int ArraySize = 1;
	if( texInfo.TextureType == TextureType::TEXTURE_TYPE_TEXTURE2D_ARRAY || texInfo.TextureType == TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE_ARRAY )
		ArraySize = texInfo.ArraySize;

	texDesc.Width				= texInfo.TextureWidth;
	texDesc.Height				= texInfo.TextureHeight;
	texDesc.MipLevels			= texInfo.MipMapLevels;
	texDesc.Usage				= DX11ConstantsMapper::Get( texInfo.Usage );
	texDesc.ArraySize			= ArraySize;
	
	
	assert( texInfo.TextureType != TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE && texInfo.TextureType != TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE_ARRAY );
	texDesc.SampleDesc.Count	= 1;
	texDesc.SampleDesc.Quality	= 0;
	
	texDesc.MiscFlags = 0;
	if( texInfo.IsCubeMap )
		texDesc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
	if( texInfo.AllowShareResource )
		texDesc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED ;

	texDesc.CPUAccessFlags = 0;
	if( texInfo.CPURead )
		texDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
	if( texInfo.CPUWrite )
		texDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;


	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texDesc.Format = DX11ConstantsMapper::Get( texInfo.Format );

	return texDesc;
}

