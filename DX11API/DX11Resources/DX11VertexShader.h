#pragma once

#include "../../MeshResources.h"
#include "../DX11Initializer/DX11APIObjects.h"


class DX11VertexShader	:	public VertexShaderObject, public DX11APIObjects
{
private:
	ID3D11VertexShader*				m_vertexShader;
protected:
	~DX11VertexShader();
public:
	DX11VertexShader( ID3D11VertexShader* shader );

	ID3D11VertexShader*				get()					{ return m_vertexShader; }


	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const std::wstring& fileName ) override;

	static DX11VertexShader*		CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static DX11VertexShader*		CreateFromFile			( const std::wstring& fileName,
															  const std::string& shaderName,
															  ShaderInputLayout** layout,
															  InputLayoutDescriptor* layout_desc,
															  const char* shaderModel = "vs_4_0" );
	static DX11VertexShader*		CreateFromBinFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
};

