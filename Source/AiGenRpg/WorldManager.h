#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldManager.generated.h"

class USaveSubsystem;

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

private:
    int32 WorldSeed = 0;
};
