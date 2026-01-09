#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RPGSaveGame.generated.h"

UCLASS()
class AIGENRPG_API URPGSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Save", SaveGame)
    int32 SaveVersion = 1;

    UPROPERTY(BlueprintReadWrite, Category = "Save", SaveGame)
    FString WorldId = TEXT("World_001");

    UPROPERTY(BlueprintReadWrite, Category = "Save", SaveGame)
    int32 WorldSeed = 12345;
};
