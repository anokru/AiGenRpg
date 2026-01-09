#include "SaveSubsystem.h"

#include "RPGSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // Default behavior: ensure we always have a save in memory.
    // If you want a different slot/user later — call LoadOrCreate from Blueprint/GameInstance.
    LoadOrCreate(TEXT("Slot_0"), 0);

    UE_LOG(LogTemp, Log, TEXT("SaveSubsystem Initialized"));
}

URPGSaveGame* USaveSubsystem::CreateNewSave()
{
    CurrentSave = Cast<URPGSaveGame>(
        UGameplayStatics::CreateSaveGameObject(URPGSaveGame::StaticClass())
    );

    if (!CurrentSave)
    {
        UE_LOG(LogTemp, Error, TEXT("CreateNewSave: failed to create SaveGame object"));
        return nullptr;
    }

    // Keep WorldId simple for now; seed is the important part.
    if (CurrentSave->WorldId.IsEmpty())
        CurrentSave->WorldId = TEXT("World_001");

    if (CurrentSave->WorldSeed == 0)
        CurrentSave->WorldSeed = FMath::Rand();

    UE_LOG(LogTemp, Log, TEXT("CreateNewSave: WorldId=%s Seed=%d"),
        *CurrentSave->WorldId, CurrentSave->WorldSeed);

    return CurrentSave;
}

bool USaveSubsystem::WriteSave(const FString& SlotName, int32 UserIndex)
{
    if (!CurrentSave)
    {
        UE_LOG(LogTemp, Warning, TEXT("WriteSave: no CurrentSave, creating new"));
        CreateNewSave();
    }

    if (!CurrentSave)
        return false;

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

        UE_LOG(LogTemp, Warning, TEXT("LoadOrCreate: slot existed but cast failed, creating new"));
    }

    // Create and persist immediately so the seed is stable next run.
    URPGSaveGame* NewSave = CreateNewSave();
    if (NewSave)
        WriteSave(SlotName, UserIndex);

    return NewSave;
}
