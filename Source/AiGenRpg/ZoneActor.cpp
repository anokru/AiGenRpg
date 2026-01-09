#include "ZoneActor.h"

#include "Components/BoxComponent.h"
#include "PCGComponent.h"
#include "Misc/Crc.h"

AZoneActor::AZoneActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    SetRootComponent(Box);
    Box->SetBoxExtent(FVector(5000.f, 5000.f, 500.f));

    PCG = CreateDefaultSubobject<UPCGComponent>(TEXT("PCG"));
    PCG->SetupAttachment(Box);
}

UPCGComponent* AZoneActor::GetPCG() const
{
    return PCG;
}

int32 AZoneActor::GetResolvedSeedOffset() const
{
    if (SeedOffset != INT32_MIN)
        return SeedOffset;

    // Детерминированный оффсет от ZoneId (не зависит от сессии)
    return StableHashToOffset(ZoneId.ToString());
}

int32 AZoneActor::StableHashToOffset(const FString& S)
{
    // CRC32 стабильный между запусками
    const uint32 Crc = FCrc::StrCrc32(*S);

    // Делаем оффсет “не слишком маленький” и в int32
    // Можно менять диапазон как угодно
    return int32(Crc % 1000000u);
}
