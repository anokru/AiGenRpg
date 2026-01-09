#include "AIGameInstance.h"
#include "Engine/Engine.h"

#include "Subsystems/GameInstanceSubsystem.h" // ← ВАЖНО
#include "SaveSubsystem.h"
#include "RPGSaveGame.h"

void UAIGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("AIGameInstance INIT"));

    if (USaveSubsystem* Save = GetSubsystem<USaveSubsystem>())
    {
        Save->LoadOrCreate(TEXT("Slot_0"), 0);
        Save->WriteSave(TEXT("Slot_0"), 0);
    }
}
