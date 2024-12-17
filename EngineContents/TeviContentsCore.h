#pragma once

#include <EngineCore/IContentsCore.h>

// 규칙을 만드는 수밖에 없다.

// 설명 :
class UTeviContentsCore : public UObject, public IContentsCore
{
public:
	// constrcuter destructer
	UTeviContentsCore();
	~UTeviContentsCore();

	// delete Function
	UTeviContentsCore(const UTeviContentsCore& _Other) = delete;
	UTeviContentsCore(UTeviContentsCore&& _Other) noexcept = delete;
	UTeviContentsCore& operator=(const UTeviContentsCore& _Other) = delete;
	UTeviContentsCore& operator=(UTeviContentsCore&& _Other) noexcept = delete;

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();

private:

};

