#pragma once

// ���� :
class Random
{
public:
	// constrcuter destructer
	Random();
	~Random();

	// delete Function
	Random(const Random& _Other) = delete;
	Random(Random&& _Other) noexcept = delete;
	Random& operator=(const Random& _Other) = delete;
	Random& operator=(Random&& _Other) noexcept = delete;

protected:

private:

};

