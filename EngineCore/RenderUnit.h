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
protected:

private:

};
