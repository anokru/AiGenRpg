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

FName AZoneActor::GetResolvedZoneId() const
{
    if (ZoneId != NAME_None)
        return ZoneId;

#if WITH_EDITOR
    const FString Label = GetActorLabel();
    if (!Label.IsEmpty())
        return FName(*Label);
#endif

    return GetFName();
}

int32 AZoneActor::GetResolvedSeedOffset() const
{
    if (SeedOffset != INT32_MIN)
        return SeedOffset;

    return StableHashToOffset(GetResolvedZoneId().ToString());
}

int32 AZoneActor::StableHashToOffset(const FString& S)
{
    const uint32 Crc = FCrc::StrCrc32(*S);
    // Keep it in a reasonable range to avoid int32 edge weirdness
    return int32(Crc % 1000000u);
}
