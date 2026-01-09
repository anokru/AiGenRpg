// #pragma once

// #include "CoreMinimal.h"
// #include "Engine/DataAsset.h"
// #include "LocationTypeDefinition.generated.h"

// UCLASS(BlueprintType)
// class AIGENRPG_API ULocationTypeDefinition : public UDataAsset
// {
//     GENERATED_BODY()

// public:
//     // ���������� ID ���� ������� (Forest, Hills, Plains, ...)
//     UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
//     FName LocationId;

//     // ����� ��������� �������� (���������)
//     UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
//     float Density = 1.0f;

//     // ������� ������ / ����������
//     UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation")
//     float HeightVariance = 0.0f;

//     // ����� ����� ��� ������
//     UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes")
//     TArray<TSoftObjectPtr<UStaticMesh>> MeshPool;

//     // ��������� �� ����
//     UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
//     bool bAllowWater = false;

//     // ��������� �� ������
//     UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
//     bool bAllowRoads = false;
// };
