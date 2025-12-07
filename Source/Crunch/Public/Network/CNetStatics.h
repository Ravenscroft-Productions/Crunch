// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CNetStatics.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UCNetStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static uint8 GetPlayerCountPerTeam();
};
