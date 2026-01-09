#include "WorldManager.h"

#include "SaveSubsystem.h"
#include "RPGSaveGame.h"
#include "ZoneActor.h"
#include "LocationTypeDefinition.h"

#include "PCGComponent.h"
#include "EngineUtils.h"
#include "Misc/Crc.h"

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
    USaveSubsystem* SaveSubsystem = GetGameInstance()
        ? GetGameInstance()->GetSubsystem<USaveSubsystem>()
        : nullptr;

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

    // WorldId is FString
    UE_LOG(LogTemp, Warning, TEXT("WorldManager: WorldId=%s Seed=%d"),
        *Save->WorldId, WorldSeed);

    int32 Applied = 0;

    for (TActorIterator<AZoneActor> It(GetWorld()); It; ++It)
    {
        AZoneActor* Zone = *It;
        if (!Zone || !Zone->bEnabled)
            continue;

        UPCGComponent* PCG = Zone->GetPCG();
        if (!PCG)
        {
            UE_LOG(LogTemp, Warning, TEXT("WorldManager: %s has no PCGComponent"), *Zone->GetName());
            continue;
        }

        const int32 Offset = Zone->GetResolvedSeedOffset();

        // 1) Авто-назначение LocationType (если не задан руками)
        if (Zone->LocationType == nullptr && DefaultLocationTypes.Num() > 0)
        {
            const int32 PickSeed = CombineSeeds(WorldSeed, Offset, SeasonSalt);
            const int32 Index = int32(uint32(PickSeed) % uint32(DefaultLocationTypes.Num()));

            if (DefaultLocationTypes[Index] != nullptr)
            {
                Zone->LocationType = DefaultLocationTypes[Index];
            }
        }

        // 2) Итоговый seed зоны = WorldSeed + Offset + salt от типа
        const int32 TypeSalt =
            (Zone->LocationType != nullptr)
            ? StableSaltFromName(Zone->LocationType->LocationTypeId)
            : 0;

        const int32 FinalSeed = CombineSeeds(WorldSeed, Offset, TypeSalt + SeasonSalt);

        PCG->Seed = FinalSeed;
        PCG->Generate();

        UE_LOG(LogTemp, Warning,
            TEXT("WorldManager: Zone=%s ZoneId=%s Offset=%d Type=%s FinalSeed=%d"),
            *Zone->GetName(),
            *Zone->GetResolvedZoneId().ToString(),
            Offset,
            Zone->LocationType ? *Zone->LocationType->LocationTypeId.ToString() : TEXT("None"),
            FinalSeed
        );

        Applied++;
    }

    UE_LOG(LogTemp, Warning, TEXT("WorldManager: Applied seed to zones: %d"), Applied);
}

int32 AWorldManager::StableSaltFromName(const FName& Name)
{
    return int32(FCrc::StrCrc32(*Name.ToString()));
}

int32 AWorldManager::CombineSeeds(int32 A, int32 B, int32 C)
{
    uint32 X = uint32(A);
    X ^= (uint32(B) + 0x9e3779b9u + (X << 6) + (X >> 2));
    X ^= (uint32(C) + 0x9e3779b9u + (X << 6) + (X >> 2));
    return int32(X);
}
