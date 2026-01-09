#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RPGSaveGame.generated.h"

UCLASS()
class AIGENRPG_API URPGSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    // Версия формата сохранений (на будущее миграции)
    UPROPERTY(BlueprintReadWrite)
    int32 SaveVersion = 1;

    // ID текущего мира (позже станет GUID)
    UPROPERTY(BlueprintReadWrite)
    FString WorldId = TEXT("World_001");

    // Seed мира (чтобы детерминированно восстанавливать генерацию)
    UPROPERTY(BlueprintReadWrite)
    int32 WorldSeed = 12345;
};
