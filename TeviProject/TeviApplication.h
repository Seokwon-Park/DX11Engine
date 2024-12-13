#pragma once

// Ό³Έν :
class TeviApplication
{
public:
	// constrcuter destructer
	TeviApplication();
	~TeviApplication();

	// delete Function
	TeviApplication(const TeviApplication& _Other) = delete;
	TeviApplication(TeviApplication&& _Other) noexcept = delete;
	TeviApplication& operator=(const TeviApplication& _Other) = delete;
	TeviApplication& operator=(TeviApplication&& _Other) noexcept = delete;

protected:

private:

};

