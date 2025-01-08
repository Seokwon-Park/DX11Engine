#pragma once
#include "EngineBuffer.h"
#include "EngineShader.h"
#include "EngineShaderResources.h"
#include "EngineShaderResources.h"
#include <EngineCore/States/EngineBlendState.h>
#include <EngineCore/States/EngineRasterizerState.h>
#include <EngineCore/States/EngineDepthStencilState.h>

struct FMaterialDescription
{
	std::string_view VSName = "";
	std::string_view HSName = "";
	std::string_view DSName = "";
	std::string_view GSName = "";
	std::string_view PSName = "";
	std::string_view CSName = "";
	std::string_view InputLayoutName = "";
	std::string_view BSName= "";
	std::string_view RSName = "";
	std::string_view DSSName= "";

};

// 클래스 설명 :
class UEngineMaterial : public UEngineResource
{
public:
	// Constrcuter Destructer
	UEngineMaterial();
	~UEngineMaterial();

	// Delete Function
	UEngineMaterial(const UEngineMaterial& _Other) = delete;
	UEngineMaterial(UEngineMaterial&& _Other) noexcept = delete;
	UEngineMaterial& operator=(const UEngineMaterial& _Other) = delete;
	UEngineMaterial& operator=(UEngineMaterial&& _Other) noexcept = delete;

	void SetShader(std::string_view _ShaderName, EShaderType _Type);
	void SetShader(std::shared_ptr<UEngineShader> _Shader, EShaderType _Type);

	std::shared_ptr<UEngineShader> GetShader(EShaderType _Type);
	std::shared_ptr<UEngineShaderResources> GetShaderResources(EShaderType _Type) { return ShaderResources[_Type]; }
	void Bind();

	inline void SetBlendState(std::shared_ptr<UEngineBlendState> _BlendState) { BlendState = _BlendState; }
	inline void SetRasterizerState(std::shared_ptr<UEngineRasterizerState> _RasterizerState) { RasterizerState = _RasterizerState; }
	inline void SetDepthStencilState(std::shared_ptr<UEngineDepthStencilState> _DepthStencilState) { DepthStencilState = _DepthStencilState; }

	ENGINE_API static std::shared_ptr<UEngineMaterial> Create(std::string _Name);
	ENGINE_API static std::shared_ptr<UEngineMaterial> Create(std::string _Name, FMaterialDescription _Desc);
protected:

private:
	void CreateMaterial(FMaterialDescription _Desc);

	std::shared_ptr<UEngineInputLayout> InputLayout;

	std::map<EShaderType, std::shared_ptr<UEngineShader>> Shaders;
	//std::shared_ptr<UEngineShader> VertexShader;
	//std::shared_ptr<UEngineShader> HullShader;
	//std::shared_ptr<UEngineShader> DomainShader;
	//std::shared_ptr<UEngineShader> GeometryShader;
	//std::shared_ptr<UEngineShader> PixelShader;
	//std::shared_ptr<UEngineShader> ComputeShader;

	std::map<EShaderType, std::shared_ptr<UEngineShaderResources>> ShaderResources;
	std::shared_ptr<UEngineBlendState> BlendState;
	std::shared_ptr<UEngineRasterizerState> RasterizerState;
	std::shared_ptr<UEngineDepthStencilState> DepthStencilState;
	

	//std::map<EShaderType, std::vector<std::shared_ptr<UEngineTexture2D>>> Textures;

	//D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	// UEngineCore::GetDevice().GetContext()->IASetPrimitiveTopology(Topology);
};
