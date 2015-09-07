#include "DX11ComputeShader.h"

#include "Common\memory_leaks.h"


DX11ComputeShader::DX11ComputeShader()
{
	m_computeShader = nullptr;
}

DX11ComputeShader::~DX11ComputeShader()
{
	if( m_computeShader )
		m_computeShader->Release();
	m_computeShader = nullptr;
}

bool DX11ComputeShader::ReloadFromFile()
{
	return false;
}

bool DX11ComputeShader::ReloadFromBinFile()
{
	return false;
}

void DX11ComputeShader::SaveShaderBinFile( const std::wstring& file_name )
{

}

DX11ComputeShader* DX11ComputeShader::CreateFromFile( const std::wstring& file_name, const std::string& shader_name, const char* shader_model )
{

	return nullptr;
}

DX11ComputeShader* DX11ComputeShader::CreateFromBinFile( const std::wstring& file_name )
{

	return nullptr;
}


