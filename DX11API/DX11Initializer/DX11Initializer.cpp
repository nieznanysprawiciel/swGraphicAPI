#include "DX11Initializer.h"
#include "../DX11Renderer/DX11Renderer.h"
#include "../DX11Resources/DX11RenderTarget.h"
#include "DX11ConstantsMapper.h"

#include "Common/memory_leaks.h"


/**@brief Tworzy renderer zgodny z u�ywanym API graficznym.

@param[in] usage Specyfikuje czy u�y� op�nionego kontekstu renderowania czy natychmiastowego.
@note Wszystkie renderery stworzone w aplikacji powinny by� tego samego typu.*/
IRenderer* DX11Initializer::CreateRenderer( RendererUsage usage )
{
	return new DX11Renderer( usage );
}

/**@brief Inicjalizuje API graficzne.

@param[in] initData Dane u�ywane do inicjalizacji.
@return Zwraca true, je�eli inicjalizacja si� uda.*/
bool DX11Initializer::InitAPI( GraphicAPIInitData& initData )
{
	set_depth_stencil_format( DX11ConstantsMapper::Get( initData.depthStencilFormat ) );

	DX11_INIT_RESULT result = init_DX11( initData.windowWidth, initData.windowHeight, (HWND)initData.windowHandle, initData.fullScreen, initData.singleThreaded );
	if( result != DX11_INIT_RESULT::DX11_INIT_OK )
		return false;

	result = init_sampler();
	if ( result != DX11_INIT_OK )
	{
		release_DirectX();	// Jak tu co� si� nie uda�o, to znaczy, �e deskryptor by� niepoprawny.
		return false;
	}
	return true;
}

/**@brief Zwalnia stworzone obiekty DirectX 11.*/
void DX11Initializer::ReleaseAPI()
{
	release_DirectX();
}

/**@brief Zwraca wska�nik na bufor koloru render targetu.

Ta funkcja jest u�ywana do wsp�pracy z zewn�trznymi aplikacjami, kt�re potrzebuj� bezpo�redniego
wska�nika na zasoby DirectXowe. Nie ma �adnego powodu, �eby jej u�ywa� w innych przypadkach.

@param[in] renderTarget RenderTarget, z kt�rego ma zosta� wzi�tu wska�nik.
@return Zwraca wska�nik na widok na bufor koloru render targetu lub nullptr,
jezeli podano niepoprawny render target.*/
void* DX11Initializer::GetRenderTargetHandle( RenderTargetObject* renderTarget )
{
	DX11RenderTarget* renderTargetDX11 = static_cast<DX11RenderTarget*>( renderTarget );

	if( renderTargetDX11 )
		return renderTargetDX11->GetRenderTarget();
	return nullptr;
}
