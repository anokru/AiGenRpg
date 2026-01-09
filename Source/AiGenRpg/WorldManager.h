#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldManager.generated.h"

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

    // Базовый seed мира (из Save)
    int32 WorldSeed = 0;

    // Соль сезона (пока 0, сезоны добавим позже)
    int32 SeasonSalt = 0;

    static int32 StableSaltFromName(const FName& Name);
    static int32 CombineSeeds(int32 A, int32 B, int32 C);
};
