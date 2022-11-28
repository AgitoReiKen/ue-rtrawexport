// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RTRawExportBPLibrary.generated.h"

UENUM(BlueprintType)
enum class ERTRawExportType : uint8
{
	HDR,
	EXR,
	PNG,
	ANY
};
UCLASS()
class URTRawExportBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
		//bool UKismetRenderingLibrary::ReadRenderTarget(UObject* WorldContextObject, UTextureRenderTarget2D* TextureRenderTarget, TArray<FColor>& OutSamples, bool bNormalize)

	/*
	 * Exports Render Target into specified file format
	 */


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Render Target Raw Export", Keywords = "Render Target Raw Export"), Category = "Render Target Raw Export")
	static bool RTRawExport(const TArray<uint8>& OutFileData, bool bIsHDR, UTextureRenderTarget2D* TextureRenderTarget);
};
