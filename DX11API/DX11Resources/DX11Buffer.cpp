#include "DX11Buffer.h"
#include "../DX11Initializer/DX11ConstantsMapper.h"

#include "Common/MemoryLeaks.h"

DX11Buffer::DX11Buffer( unsigned int elementSize, unsigned int elementCount, ID3D11Buffer* buff )
	: BufferObject(elementSize, elementCount), m_buffer( buff )
{
}

DX11Buffer::~DX11Buffer()
{
	if( m_buffer )
		m_buffer->Release();
	m_buffer = nullptr;
}

/**@brief Tworzy bufor wierzcho�k�w, indeks�w lub sta�ych o podanych parametrach.

@param[in] buffer Wska�nik na bufor z danym, kt�re maj� by� przeniesione do bufora DirectXowego.
@param[in] elementSize Rozmiar pojedynczego elementu w buforze
@param[in] vertCount Liczba wierzcho�k�w/indeks�w w buforze
@param[in] bindFlag Okre�la z czym zwi�za� podany bufor w potoku graficznym.
Dla bufora wierzcho�k�w nale�y poda� D3D11_BIND_VERTEX_BUFFER, a dla bufora indeks�w
D3D11_BIND_INDEX_BUFFER.
@param[in] usage Jedna z warto�ci D3D11_USAGE, kt�r� nale�y poda� DirectXowi.
@return Wska�nik na DX11Buffer w przypadku powodzenia lub nullptr, je�eli co� p�jdzie nie tak.*/
DX11Buffer* DX11Buffer::CreateFromMemory(	const void* buffer,
											unsigned int elementSize,
											unsigned int vertCount,
											ResourceBinding bindFlag,
											ResourceUsage usage )
{
	// Wype�niamy deskryptor bufora
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = DX11ConstantsMapper::Get( usage );
	bufferDesc.BindFlags = DX11ConstantsMapper::Get( bindFlag );
	bufferDesc.ByteWidth = vertCount * elementSize;

	D3D11_SUBRESOURCE_DATA* initDataPtr = nullptr;
	D3D11_SUBRESOURCE_DATA initData;
	if( buffer )
	{
		// Je�eli bufor nie istnieje to do funkcji tworz�cej bufor powinni�my poda� nullptr.
		ZeroMemory( &initData, sizeof( initData ) );
		initData.pSysMem = buffer;
		initDataPtr = &initData;
	}

	HRESULT result;
	ID3D11Buffer* new_buffer;
	result = device->CreateBuffer( &bufferDesc, initDataPtr, &new_buffer );
	if( FAILED( result ) )
		return nullptr;

	DX11Buffer* new_buffer_object = new DX11Buffer( elementSize, vertCount, new_buffer );
	return new_buffer_object;
}


/**@brief Kopiuje pami�� bufora i zwraca w MemoryChunku.

Funkcja zwraca zawarto�� bufora. Pami�� jest kopiowana dwukrotnie.
Najpierw na GPU do tymczasowego bufora, a potem po zmapowaniu na pami�� RAM,
odbywa si� kopiowanie do MemoryChunka.

@todo Nie trzeba by wykonywa� kopiowania na GPU, gdyby bufor by� stworzony z flag�
D3D11_USAGE_STAGING lub D3D11_USAGE_DEFAULT. Trzeba sprawdzi� flagi i robi� kopiowanie tylko, gdy to konieczne.

@attention Funkcja nie nadaje si� do wykonania wielow�tkowego. U�ywa DeviceContextu do kopiowania danych
w zwi�zku z czym wymaga synchronizacji z innymi funkcjami renderuj�cymi.
*/
MemoryChunk DX11Buffer::CopyData()
{
	// Trzeba stworzy� nowy bufor
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
	//bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;		// Przy fladze usage::staging nie mo�na bindowa� zasobu do potoku graficznego.
	bufferDesc.ByteWidth = m_elementSize * m_elementCount;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	HRESULT result;
	ID3D11Buffer* newBuffer;
	result = device->CreateBuffer( &bufferDesc, nullptr, &newBuffer );
	if( FAILED( result ) )
		return MemoryChunk();

	// Kopiowanie zawarto�ci mi�dzy buforami
	device_context->CopyResource( newBuffer, m_buffer );

	D3D11_MAPPED_SUBRESOURCE data;
	result = device_context->Map( newBuffer, 0, D3D11_MAP::D3D11_MAP_READ, 0, &data );
	if( FAILED( result ) )
		return MemoryChunk();

	MemoryChunk memoryChunk;
	memoryChunk.MemoryCopy( (int8*)data.pData, m_elementSize * m_elementCount );

	device_context->Unmap( newBuffer, 0 );
	newBuffer->Release();

	return std::move( memoryChunk );
}
