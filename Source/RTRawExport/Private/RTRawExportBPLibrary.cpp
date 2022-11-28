// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTRawExportBPLibrary.h"

#include "ImageUtils.h"
#include "RTRawExport.h"
#include "Engine/Classes/Engine/TextureRenderTarget2D.h"

#include "Serialization/BufferArchive.h"

URTRawExportBPLibrary::URTRawExportBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool URTRawExportBPLibrary::RTRawExport(const TArray<uint8>& OutFileData, bool bIsHDR,  UTextureRenderTarget2D* TextureRenderTarget)
{

	if (!TextureRenderTarget)
	{
		FMessageLog("Blueprint").Warning( FText::FromString(TEXT("ExportRenderTarget: TextureRenderTarget must be non-null.")));
	}
	else if (!TextureRenderTarget->GetResource())
	{
		FMessageLog("Blueprint").Warning(FText::FromString(TEXT("ExportRenderTarget: render target has been released.")));
	} 
	else
	{
		FBufferArchive Buffer;
		bool bSuccess = false;
		if (TextureRenderTarget->RenderTargetFormat == RTF_RGBA16f)
		{
			if (bIsHDR)
			{
				bSuccess = FImageUtils::ExportRenderTarget2DAsHDR(TextureRenderTarget, Buffer);
			}
			else
			{
				bSuccess = FImageUtils::ExportRenderTarget2DAsEXR(TextureRenderTarget, Buffer);
			}
		}
		else
		{
			bSuccess = FImageUtils::ExportRenderTarget2DAsPNG(TextureRenderTarget, Buffer);
		}
		auto MutableData = const_cast<TArray<uint8>*>(&OutFileData);
		if (bSuccess)
		{
			MutableData->Empty();
			MoveAssignItems(MutableData->GetData(), Buffer.GetData(), Buffer.Num());
		}
		return bSuccess;
	}
	return false;
}
