#include "DX11Texture.h"

#include "Common/MemoryLeaks.h"

DX11Texture::DX11Texture( const std::wstring& path, ID3D11ShaderResourceView* tex )
{
	m_fileName = path;
	m_texture = tex;
}

DX11Texture::~DX11Texture()
{
	if( m_texture )
		m_texture->Release();
	m_texture = nullptr;
}

/**@brief Zapisuje podan� tekstur� do pliku.

@brief filePath �cie�ka do pliku, do kt�rego ma zosta� zapisana tekstura.
@return Zwraca true, je�eli zapis si� uda.*/
bool DX11Texture::SaveToFile( const std::string& filePath )
{
	//HRESULT result = D3DX11SaveTextureToFile( device_context, m_texture, )

	return false;
}

/**@brief Tworzy tekstur� na podstawie podanego pliku.

@param[in] fileName Nazwa pliku zawieraj�cego tekstur�
@return Zawraca stworzony wewn�trz obiekt DX11Texture z wczytan� tekstur� lub nullptr w przypadku niepowodzenia.
*/
DX11Texture* DX11Texture::CreateFromFile( const std::wstring& fileName )
{
	ID3D11ShaderResourceView* textureView;
	HRESULT result = D3DX11CreateShaderResourceViewFromFile( device, fileName.c_str(),
															 NULL, NULL,
															 &textureView, NULL );
	if( FAILED( result ) )
		return nullptr;

	DX11Texture* texture = new DX11Texture( fileName, textureView );

	return texture;
}

DX11Texture* DX11Texture::CreateFromMemory()
{

	return nullptr;
}
