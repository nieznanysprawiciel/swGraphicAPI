#pragma once
/**
@file GraphicAPIConstants.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

/**@brief Specyfikuje typ dost�pu do pami�ci danego zasobu.
@see @ref GraphicAPI*/
enum class ResourceUsage
{
	RESOURCE_USAGE_DEFAULT		= 0,		///<Pozawala GPU na zapis i odczyt.
	RESOURCE_USAGE_DYNAMIC		= 1,		///<Pozwala GPU na odczyt, a CPU na zapis. Dobre do cz�sto updatowanych zasob�w.
	RESOURCE_USAGE_STATIC		= 2,		///<Zas�b raz stworzony i nigdy nie jest zmieniany.
	RESOURCE_USAGE_STAGING		= 3			///<GPU mo�e jedynie kopiowa�, poza tym wszystkie prawa dost�pu s� po stronie CPU. Zobacz D3D11_USAGE_STAGING.
};

/**@brief Topologia wierzcho�k�w.
@see @ref GraphicAPI*/
enum class PrimitiveTopology
{
  PRIMITIVE_TOPOLOGY_POINTLIST                     = 0,
  PRIMITIVE_TOPOLOGY_LINELIST                      = 1,
  PRIMITIVE_TOPOLOGY_LINESTRIP                     = 2,
  PRIMITIVE_TOPOLOGY_TRIANGLELIST                  = 3,
  PRIMITIVE_TOPOLOGY_TRIANGLESTRIP                 = 4,
  PRIMITIVE_TOPOLOGY_LINELIST_ADJ                  = 5,
  PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ                 = 6,
  PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ              = 7,
  PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ             = 8
};

/**@brief Okre�la jak b�dzie u�ywany dany zas�b w potoku karty graficznej.

@attention DirectX pozwala na ��czenie tych sta�ych jak flag, ale w silniku mo�na wybra� tylko
jedn� opcj�.
@see @ref GraphicAPI*/
enum ResourceBinding
{
	BIND_RESOURCE_VERTEX_BUFFER     = 0x0L,
	BIND_RESOURCE_INDEX_BUFFER		= 0x1L,
	BIND_RESOURCE_CONSTANT_BUFFER	= 0x2L,
	BIND_RESOURCE_SHADER_RESOURCE	= 0x3L,
	BIND_RESOURCE_STREAM_OUTPUT		= 0x4L,
	BIND_RESOURCE_RENDER_TARGET		= 0x5L,
	BIND_RESOURCE_DEPTH_STENCIL		= 0x6L,
	BIND_RESOURCE_UNORDERED_ACCESS	= 0x7L,
	BIND_RESOURCE_DECODER			= 0x8L,
	BIND_RESOURCE_VIDEO_ENCODER		= 0x9L
	
};

/**@briefSpecyfikuje format tekstury b�d� innego zasobu.
@see @ref GraphicAPI*/
enum class ResourceFormat
{
	RESOURCE_FORMAT_UNKNOWN = 0,
	RESOURCE_FORMAT_R32G32B32A32_TYPELESS = 1,
	RESOURCE_FORMAT_R32G32B32A32_FLOAT = 2,
	RESOURCE_FORMAT_R32G32B32A32_UINT = 3,
	RESOURCE_FORMAT_R32G32B32A32_SINT = 4,
	RESOURCE_FORMAT_R32G32B32_TYPELESS = 5,
	RESOURCE_FORMAT_R32G32B32_FLOAT = 6,
	RESOURCE_FORMAT_R32G32B32_UINT = 7,
	RESOURCE_FORMAT_R32G32B32_SINT = 8,
	RESOURCE_FORMAT_R16G16B16A16_TYPELESS = 9,
	RESOURCE_FORMAT_R16G16B16A16_FLOAT = 10,
	RESOURCE_FORMAT_R16G16B16A16_UNORM = 11,
	RESOURCE_FORMAT_R16G16B16A16_UINT = 12,
	RESOURCE_FORMAT_R16G16B16A16_SNORM = 13,
	RESOURCE_FORMAT_R16G16B16A16_SINT = 14,
	RESOURCE_FORMAT_R32G32_TYPELESS = 15,
	RESOURCE_FORMAT_R32G32_FLOAT = 16,
	RESOURCE_FORMAT_R32G32_UINT = 17,
	RESOURCE_FORMAT_R32G32_SINT = 18,
	RESOURCE_FORMAT_R32G8X24_TYPELESS = 19,
	RESOURCE_FORMAT_D32_FLOAT_S8X24_UINT = 20,
	RESOURCE_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
	RESOURCE_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
	RESOURCE_FORMAT_R10G10B10A2_TYPELESS = 23,
	RESOURCE_FORMAT_R10G10B10A2_UNORM = 24,
	RESOURCE_FORMAT_R10G10B10A2_UINT = 25,
	RESOURCE_FORMAT_R11G11B10_FLOAT = 26,
	RESOURCE_FORMAT_R8G8B8A8_TYPELESS = 27,
	RESOURCE_FORMAT_R8G8B8A8_UNORM = 28,
	RESOURCE_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
	RESOURCE_FORMAT_R8G8B8A8_UINT = 30,
	RESOURCE_FORMAT_R8G8B8A8_SNORM = 31,
	RESOURCE_FORMAT_R8G8B8A8_SINT = 32,
	RESOURCE_FORMAT_R16G16_TYPELESS = 33,
	RESOURCE_FORMAT_R16G16_FLOAT = 34,
	RESOURCE_FORMAT_R16G16_UNORM = 35,
	RESOURCE_FORMAT_R16G16_UINT = 36,
	RESOURCE_FORMAT_R16G16_SNORM = 37,
	RESOURCE_FORMAT_R16G16_SINT = 38,
	RESOURCE_FORMAT_R32_TYPELESS = 39,
	RESOURCE_FORMAT_D32_FLOAT = 40,
	RESOURCE_FORMAT_R32_FLOAT = 41,
	RESOURCE_FORMAT_R32_UINT = 42,
	RESOURCE_FORMAT_R32_SINT = 43,
	RESOURCE_FORMAT_R24G8_TYPELESS = 44,
	RESOURCE_FORMAT_D24_UNORM_S8_UINT = 45,
	RESOURCE_FORMAT_R24_UNORM_X8_TYPELESS = 46,
	RESOURCE_FORMAT_X24_TYPELESS_G8_UINT = 47,
	RESOURCE_FORMAT_R8G8_TYPELESS = 48,
	RESOURCE_FORMAT_R8G8_UNORM = 49,
	RESOURCE_FORMAT_R8G8_UINT = 50,
	RESOURCE_FORMAT_R8G8_SNORM = 51,
	RESOURCE_FORMAT_R8G8_SINT = 52,
	RESOURCE_FORMAT_R16_TYPELESS = 53,
	RESOURCE_FORMAT_R16_FLOAT = 54,
	RESOURCE_FORMAT_D16_UNORM = 55,
	RESOURCE_FORMAT_R16_UNORM = 56,
	RESOURCE_FORMAT_R16_UINT = 57,
	RESOURCE_FORMAT_R16_SNORM = 58,
	RESOURCE_FORMAT_R16_SINT = 59,
	RESOURCE_FORMAT_R8_TYPELESS = 60,
	RESOURCE_FORMAT_R8_UNORM = 61,
	RESOURCE_FORMAT_R8_UINT = 62,
	RESOURCE_FORMAT_R8_SNORM = 63,
	RESOURCE_FORMAT_R8_SINT = 64,
	RESOURCE_FORMAT_A8_UNORM = 65,
	RESOURCE_FORMAT_R1_UNORM = 66,
	RESOURCE_FORMAT_R9G9B9E5_SHAREDEXP = 67,
	RESOURCE_FORMAT_R8G8_B8G8_UNORM = 68,
	RESOURCE_FORMAT_G8R8_G8B8_UNORM = 69,
	RESOURCE_FORMAT_BC1_TYPELESS = 70,
	RESOURCE_FORMAT_BC1_UNORM = 71,
	RESOURCE_FORMAT_BC1_UNORM_SRGB = 72,
	RESOURCE_FORMAT_BC2_TYPELESS = 73,
	RESOURCE_FORMAT_BC2_UNORM = 74,
	RESOURCE_FORMAT_BC2_UNORM_SRGB = 75,
	RESOURCE_FORMAT_BC3_TYPELESS = 76,
	RESOURCE_FORMAT_BC3_UNORM = 77,
	RESOURCE_FORMAT_BC3_UNORM_SRGB = 78,
	RESOURCE_FORMAT_BC4_TYPELESS = 79,
	RESOURCE_FORMAT_BC4_UNORM = 80,
	RESOURCE_FORMAT_BC4_SNORM = 81,
	RESOURCE_FORMAT_BC5_TYPELESS = 82,
	RESOURCE_FORMAT_BC5_UNORM = 83,
	RESOURCE_FORMAT_BC5_SNORM = 84,
	RESOURCE_FORMAT_B5G6R5_UNORM = 85,
	RESOURCE_FORMAT_B5G5R5A1_UNORM = 86,
	RESOURCE_FORMAT_B8G8R8A8_UNORM = 87,
	RESOURCE_FORMAT_B8G8R8X8_UNORM = 88,
	RESOURCE_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
	RESOURCE_FORMAT_B8G8R8A8_TYPELESS = 90,
	RESOURCE_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
	RESOURCE_FORMAT_B8G8R8X8_TYPELESS = 92,
	RESOURCE_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
	RESOURCE_FORMAT_BC6H_TYPELESS = 94,
	RESOURCE_FORMAT_BC6H_UF16 = 95,
	RESOURCE_FORMAT_BC6H_SF16 = 96,
	RESOURCE_FORMAT_BC7_TYPELESS = 97,
	RESOURCE_FORMAT_BC7_UNORM = 98,
	RESOURCE_FORMAT_BC7_UNORM_SRGB = 99,
	RESOURCE_FORMAT_AYUV = 100,
	RESOURCE_FORMAT_Y410 = 101,
	RESOURCE_FORMAT_Y416 = 102,
	RESOURCE_FORMAT_NV12 = 103,
	RESOURCE_FORMAT_P010 = 104,
	RESOURCE_FORMAT_P016 = 105,
	RESOURCE_FORMAT_420_OPAQUE = 106,
	RESOURCE_FORMAT_YUY2 = 107,
	RESOURCE_FORMAT_Y210 = 108,
	RESOURCE_FORMAT_Y216 = 109,
	RESOURCE_FORMAT_NV11 = 110,
	RESOURCE_FORMAT_AI44 = 111,
	RESOURCE_FORMAT_IA44 = 112,
	RESOURCE_FORMAT_P8 = 113,
	RESOURCE_FORMAT_A8P8 = 114,
	RESOURCE_FORMAT_B4G4R4A4_UNORM = 115,
	RESOURCE_FORMAT_P208 = 130,
	RESOURCE_FORMAT_V208 = 131,
	RESOURCE_FORMAT_V408 = 132,
};