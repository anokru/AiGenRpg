#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldManager.generated.h"

class ULocationTypeDefinition;

UCLASS()
class AIGENRPG_API AWorldManager : public AActor
{
    GENERATED_BODY()

public:
    AWorldManager();

protected:
    virtual void BeginPlay() override;

private:
    void ApplyWorldSeed();

    // Если у зоны LocationType == nullptr, берём из этого списка детерминированно по seed.
    UPROPERTY(EditAnywhere, Category = "World|Catalogs")
    TArray<TObjectPtr<ULocationTypeDefinition>> DefaultLocationTypes;

    // Base world seed from SaveGame
    int32 WorldSeed = 0;

    // Seasons later (keep 0 for now)
    int32 SeasonSalt = 0;

    static int32 StableSaltFromName(const FName& Name);
    static int32 CombineSeeds(int32 A, int32 B, int32 C);
};
