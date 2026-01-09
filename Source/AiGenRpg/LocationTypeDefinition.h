#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LocationTypeDefinition.generated.h"

UCLASS(BlueprintType)
class AIGENRPG_API ULocationTypeDefinition : public UDataAsset
{
    GENERATED_BODY()

public:
    // Уникальный ID типа локации (Forest, Hills, Plains, Water, Swamp...)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
    FName LocationTypeId = "Plains";

    // Общая плотность объектов (множитель)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float DensityMultiplier = 1.0f;

    // Разброс высоты / неровность (для будущих графов)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation", meta = (ClampMin = "0.0", UIMin = "0.0"))
    float HeightVariance = 0.0f;

    // Набор мешей (можно расширять)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
    TArray<TSoftObjectPtr<UStaticMesh>> MeshPool;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
    bool bAllowWater = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
    bool bAllowRoads = false;
};
