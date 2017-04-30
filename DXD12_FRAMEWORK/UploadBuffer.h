#pragma once
#ifndef UPLOADBUFFER_H_
#define UPLOADBUFFER_H_
#include"d3dUtil.h"

template<typename T>
class UploadBuffer
{
public:
	UploadBuffer(ID3D12Device* device, UINT elementCount, bool inConstantBuffer)
	{
		mElementByteSize = sizeof(T);

		//Constant buffer elements need to be multiples of 256 bytes.
		//This is because the hardware can only view constant data
		//at m*256 byte offsets and of n*256 byte lengths.
		//typedef struct D3D12_CONSTANT_BUFFER_VIEW_DESC{
		//UINT64 OffsetInBytes;//mtltiple of 256
		//UINT SizeInByte;	//multiple if 256
		//}D3D12_CONSTANT_BUFFER_VIEW_DESC;
		if (mIsConstantBuffer)
			mElementByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(T));

		ThrowIfFailed(device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(mElementByteSize*elementCount),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&mUploadBuffer)));

		ThrowIfFailed(mUploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mMappedData)));
		
		//Wo do not need to unmap until we are done with the resourece.
		//However, we must not write to the resource while if is in use by
		//the GPU (so wo must use synchronization techniques).
	}

	UploadBuffer(const UploadBuffer& rhs) = delete;
	UploadBuffer& operator=(const UploadBuffer& rhs) = delete;
	~UploadBuffer()
	{
		if (mUploadBuffer != nullptr)
			mUploadBuffer->Unmap(0, nullptr);

		mMappedData = nullptr;
	}

	ID3D12Resource* Resource()const
	{
		return mUploadBuffer.Get();
	}

	void CopyData(int elementIndex, const T& data)
	{
		memcpy(&mMappedData[elementIndex * mElementByteSize], &data, sizeof(T));
	}

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> mUploadBuffer;
	BYTE* mMappedData = nullptr;

	UINT mElementByteSize = 0;
	bool mIsConstantBuffer = false;
};

#endif // !UPLOADBUFFER_H_
