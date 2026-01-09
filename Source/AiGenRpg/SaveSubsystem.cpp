#include "SaveSubsystem.h"
#include "RPGSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UE_LOG(LogTemp, Log, TEXT("SaveSubsystem Initialized"));
}

URPGSaveGame* USaveSubsystem::CreateNewSave()
{
    CurrentSave = Cast<URPGSaveGame>(UGameplayStatics::CreateSaveGameObject(URPGSaveGame::StaticClass()));
    if (!CurrentSave)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateNewSave: Failed to create URPGSaveGame"));
        return nullptr;
    }

    // Можно сразу рандомизировать seed
    CurrentSave->WorldSeed = FMath::RandRange(1, 2000000000);

    UE_LOG(LogTemp, Log, TEXT("CreateNewSave: WorldId=%s Seed=%d"), *CurrentSave->WorldId, CurrentSave->WorldSeed);
    return CurrentSave;
}

bool USaveSubsystem::WriteSave(const FString& SlotName, int32 UserIndex)
{
    if (!CurrentSave)
    {
        UE_LOG(LogTemp, Warning, TEXT("WriteSave: CurrentSave is null, creating new save"));
        CreateNewSave();
    }

    const bool bOk = UGameplayStatics::SaveGameToSlot(CurrentSave, SlotName, UserIndex);
    UE_LOG(LogTemp, Log, TEXT("WriteSave: slot=%s user=%d result=%s"),
        *SlotName, UserIndex, bOk ? TEXT("OK") : TEXT("FAIL"));
    return bOk;
}

URPGSaveGame* USaveSubsystem::LoadOrCreate(const FString& SlotName, int32 UserIndex)
{
    if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    {
        USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);
        CurrentSave = Cast<URPGSaveGame>(Loaded);

        if (CurrentSave)
        {
            UE_LOG(LogTemp, Log, TEXT("LoadOrCreate: Loaded slot=%s WorldId=%s Seed=%d"),
                *SlotName, *CurrentSave->WorldId, CurrentSave->WorldSeed);
            return CurrentSave;
        }

        UE_LOG(LogTemp, Warning, TEXT("LoadOrCreate: Slot existed but cast failed, creating new"));
    }

    return CreateNewSave();
}
