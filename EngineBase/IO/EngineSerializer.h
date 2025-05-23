#pragma once
#include <EngineBase/EngineMath.h>

// 설명 :
class UEngineSerializer 
{
public:
	// constrcuter destructer
	BASE_API UEngineSerializer();
	BASE_API ~UEngineSerializer();

	// delete Function
	UEngineSerializer(const UEngineSerializer& _Other) = delete;
	UEngineSerializer(UEngineSerializer&& _Other) noexcept = delete;
	UEngineSerializer& operator=(const UEngineSerializer& _Other) = delete;
	UEngineSerializer& operator=(UEngineSerializer&& _Other) noexcept = delete;

	//Save
	BASE_API void Write(const void* _Data, unsigned int _Size);

	inline void operator<<(const int& _Data) { Write(&_Data, sizeof(int)); }
	inline void operator<<(const unsigned __int64& _Data) { Write(&_Data, sizeof(unsigned __int64)); }
	inline void operator<<(const float& _Data) { Write(&_Data, sizeof(float)); }
	inline void operator<<(const double& _Data) { Write(&_Data, sizeof(double)); }
	inline void operator<<(const bool& _Data) { Write(&_Data, sizeof(bool)); }
	inline void operator<<(const FVector2& _Data) { Write(&_Data, sizeof(FVector2)); }
	inline void operator<<(const FVector4& _Data) { Write(&_Data, sizeof(FVector4)); }
	inline void operator<<(const FIntPoint& _Data) { Write(&_Data, sizeof(FIntPoint)); }
	inline void operator<<(const std::string& _Data)
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
			// 자료형 변환이 안된다
			operator<<(_vector[i]);
		}
	}
	void operator<<(class ISerializableObject& _Data);

	//Load
	BASE_API void Read(void* _Data, unsigned int _Size);
	void operator>>(int& _Data) { Read(&_Data, sizeof(int)); }
	void operator>>(unsigned __int64& _Data) { Read(&_Data, sizeof(unsigned __int64)); }
	void operator>>(float& _Data) { Read(&_Data, sizeof(float)); }
	void operator>>(double& _Data) { Read(&_Data, sizeof(double)); }
	void operator>>(bool& _Data) { Read(&_Data, sizeof(bool)); }
	void operator>>(FVector2& _Data) { Read(&_Data, sizeof(FVector2)); }
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
			// 자료형 변환이 안된다.
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

	size_t GetDataSize()
	{
		return Data.size();
	}
protected:

private:
	// 얼마나 데이터가 채워짐?
	int WriteOffset = 0;

	// 얼마나 데이터가 채워짐?
	int ReadOffset = 0;
	std::vector<char> Data;
};


class ISerializableObject
{
public:
	// 데이터를 직렬화(압축)
	BASE_API virtual void Serialize(UEngineSerializer& _Serializer) = 0;
	// 데이터를 복구(할때)
	BASE_API virtual void Deserialize(UEngineSerializer& _Serializer) = 0;
};

