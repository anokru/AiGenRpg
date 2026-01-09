#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LocationTypeDefinition.generated.h"

class UStaticMesh;

UCLASS(BlueprintType)
class AIGENRPG_API ULocationTypeDefinition : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
    FName LocationTypeId = TEXT("Plains");

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float DensityMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float HeightVariance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
    TArray<TSoftObjectPtr<UStaticMesh>> MeshPool;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
    bool bAllowWater = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
    bool bAllowRoads = false;
};
