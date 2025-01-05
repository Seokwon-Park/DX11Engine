#pragma once

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
protected:

private:
	std::shared_ptr<class UEngineMesh> Mesh;
	std::shared_ptr<class UEngineMaterial> Material;
};
