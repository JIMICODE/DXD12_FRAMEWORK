#pragma once
#ifndef FRAMERESOURCE_H_
#define FRAMERESOURCE_H_

#include"d3dUtil.h"
#include"UploadBuffer.h"

struct FrameResource
{
public:
	FrameResource(ID3D12Device* device, UINT passCount, UINT objectCount);
	FrameResource(const FrameResource&  rhs) = delete;
	FrameResource& operator= (const FrameResource& rhs) = delete;
	~FrameResource();

	//We cannot reset the allocator until the GPU is deone processing the 
	//command. So each frame needs their own allocator.
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CmdListAlloc;

	//we cannot update a cbuffer until the GPU is done processing the
	//commands that reference it. SO each frame needs their own cbuffers.
	std::unique_ptr<UploadBuffer<PassConstan>>
};

#endif // !FRAMERESOURCE_H_
