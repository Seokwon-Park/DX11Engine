#pragma once
#include <EngineCore/Resources/EngineMesh.h>
#include <EngineCore/Resources/EngineShader.h>
#include <EngineCore/Resources/EngineMaterial.h>

// 클래스 설명 :
class URenderUnit
{
public:
	// Constrcuter Destructer
	URenderUnit();
	~URenderUnit();

	// Delete Function
	URenderUnit(const URenderUnit& _Other) = delete;
	URenderUnit(URenderUnit&& _Other) noexcept = delete;
	URenderUnit& operator=(const URenderUnit& _Other) = delete;
	URenderUnit& operator=(URenderUnit&& _Other) noexcept = delete;

	void Render(class UCameraComponent* _Camera, float _DeltaTime);

	template <typename DataType>
	inline void SetConstantBufferData(std::string_view _BufferName, EShaderType _Type, DataType& Data) 
	{ 
		Material->GetShaderResources(_Type)->SetConstantBuffer(_BufferName, Data); 
	}
	void SetTexture(std::string_view _Name, EShaderType _Type, std::shared_ptr<UEngineTexture2D> _Texture)
	{
		Material->GetShaderResources(_Type)->SetTexture(_Name, _Texture);
	}
	void SetSampler(std::string_view _Name, EShaderType _Type, std::shared_ptr<UEngineSamplerState> _SamplerState)
	{
		Material->GetShaderResources(_Type)->SetSamplerState(_Name, _SamplerState);
	}


	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);
	inline void Init(std::string_view _MeshName, std::string_view _MaterialName) { SetMesh(_MeshName); SetMaterial(_MaterialName); };
	inline void Init(std::shared_ptr<class UEngineMesh> _Mesh, std::shared_ptr<class UEngineMaterial> _Material)
	{
		Mesh = _Mesh;
		Material = _Material;
	};
	inline void SetMesh(std::shared_ptr<class UEngineMesh> _Mesh) { Mesh = _Mesh; }
	inline void SetMaterial(std::shared_ptr<class UEngineMaterial> _Material) { Material = _Material; }
	inline void SetOwner(class URendererComponent* _Owner) { Owner = _Owner; }
protected:

private:
	class URendererComponent* Owner;
	std::shared_ptr<UEngineMesh> Mesh;
	std::shared_ptr<UEngineMaterial> Material;
};
