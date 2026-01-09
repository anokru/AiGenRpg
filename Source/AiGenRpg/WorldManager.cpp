#include "WorldManager.h"

#include "Kismet/GameplayStatics.h"
#include "SaveSubsystem.h"
#include "RPGSaveGame.h"
#include "PCGComponent.h"

#include "ZoneActor.h"
#include "EngineUtils.h" // TActorIterator

AWorldManager::AWorldManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AWorldManager::BeginPlay()
{
    Super::BeginPlay();
    ApplyWorldSeed();
}

void AWorldManager::ApplyWorldSeed()
{
    USaveSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<USaveSubsystem>();
    if (!SaveSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("WorldManager: SaveSubsystem not found"));
        return;
    }

    const URPGSaveGame* Save = SaveSubsystem->GetCurrentSave();
    if (!Save)
    {
        UE_LOG(LogTemp, Error, TEXT("WorldManager: No current save"));
        return;
    }

    WorldSeed = Save->WorldSeed;
    UE_LOG(LogTemp, Warning, TEXT("WorldManager: WorldSeed=%d"), WorldSeed);

    int32 ZonesFound = 0;
    int32 ZonesGenerated = 0;

    for (TActorIterator<AZoneActor> It(GetWorld()); It; ++It)
    {
        AZoneActor* Zone = *It;
        if (!Zone) continue;

        ZonesFound++;

        if (!Zone->bEnabled)
        {
            UE_LOG(LogTemp, Warning, TEXT("WorldManager: Zone '%s' disabled -> skip"),
                *Zone->ZoneId.ToString());
            continue;
        }

        UPCGComponent* PCG = Zone->GetPCG();
        if (!PCG)
        {
            UE_LOG(LogTemp, Error, TEXT("WorldManager: Zone '%s' has no PCGComponent -> skip"),
                *Zone->ZoneId.ToString());
            continue;
        }

        const int32 Offset = Zone->GetResolvedSeedOffset();
        const int32 FinalSeed = WorldSeed + Offset;

        PCG->Seed = FinalSeed;
        PCG->Cleanup();
        PCG->Generate();

        ZonesGenerated++;

        UE_LOG(LogTemp, Warning, TEXT("WorldManager: Zone '%s' Offset=%d Seed=%d Actor=%s"),
            *Zone->ZoneId.ToString(),
            Offset,
            FinalSeed,
            *Zone->GetName());
    }

    if (ZonesFound == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("WorldManager: No ZoneActor found on level"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("WorldManager: ZonesFound=%d ZonesGenerated=%d"),
            ZonesFound, ZonesGenerated);
    }
}
