#pragma once
#include "EngineMath.h"

// ���� :
class UEngineSerializer 
{
public:
	// constrcuter destructer
	UEngineSerializer();
	~UEngineSerializer();

	// delete Function
	UEngineSerializer(const UEngineSerializer& _Other) = delete;
	UEngineSerializer(UEngineSerializer&& _Other) noexcept = delete;
	UEngineSerializer& operator=(const UEngineSerializer& _Other) = delete;
	UEngineSerializer& operator=(UEngineSerializer&& _Other) noexcept = delete;

	//Save
	void Write(void* _Data, unsigned int _Size);
	void operator<<(int& _Data) { Write(&_Data, sizeof(int)); }
	void operator<<(bool& _Data) { Write(&_Data, sizeof(bool)); }
	void operator<<(FVector4& _Data) { Write(&_Data, sizeof(FVector4)); }
	void operator<<(FIntPoint& _Data) { Write(&_Data, sizeof(FIntPoint)); }
	void operator<<(std::string& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		operator<<(Size);
		Write(&_Data[0], static_cast<int>(_Data.size()));
	}
	template<typename DataType>
	void operator<<(std::vector<DataType>& _vector)
	{
		int Size = static_cast<int>(_vector.size());
		operator<<(Size);

		for (size_t i = 0; i < _vector.size(); i++)
		{
			// �ڷ��� ��ȯ�� �ȵȴ�
			operator<<(_vector[i]);
		}
	}
	void operator<<(class ISerializableObject& _Data);

	//Load
	void Read(void* _Data, unsigned int _Size);
	void operator>>(int& _Data) { Read(&_Data, sizeof(int)); }
	void operator>>(bool& _Data) { Read(&_Data, sizeof(bool)); }
	void operator>>(FVector4& _Data) { Read(&_Data, sizeof(FVector4)); }
	void operator>>(FIntPoint& _Data) { Read(&_Data, sizeof(FIntPoint)); }
	void operator>>(std::string& _Data)
	{
		int Size;
		operator>>(Size);
		_Data.resize(Size);
		Read(&_Data[0], static_cast<int>(_Data.size()));
	}
	template<typename DataType>
	void operator>>(std::vector<DataType>& _vector)
	{
		int Size = 0;
		operator>>(Size);
		_vector.resize(Size);
		for (size_t i = 0; i < _vector.size(); i++)
		{
			// �ڷ��� ��ȯ�� �ȵȴ�.
			operator>>(_vector[i]);
		}
	}
	void operator>>(class ISerializableObject& _Data);

	void* GetDataPtr()
	{
		return &Data[0];
	}

	int GetWriteOffset()
	{
		return WriteOffset;
	}

	void DataResize(int _Value)
	{
		Data.resize(_Value);
	}
protected:

private:
	// �󸶳� �����Ͱ� ä����?
	int WriteOffset = 0;

	// �󸶳� �����Ͱ� ä����?
	int ReadOffset = 0;
	std::vector<char> Data;
};


class ISerializableObject
{
public:
	// �����͸� ����ȭ(����)
	virtual void Serialize(UEngineSerializer& _Serializer) = 0;
	// �����͸� ����(�Ҷ�)
	virtual void DeSerialize(UEngineSerializer& _Serializer) = 0;
};

