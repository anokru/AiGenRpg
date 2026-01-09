#include "ZoneActor.h"
#include "PCGComponent.h"

AZoneActor::AZoneActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

UPCGComponent* AZoneActor::GetPCG() const
{
    return FindComponentByClass<UPCGComponent>();
}

int32 AZoneActor::StableHashToOffset(const FName& Name)
{
    // Дет. хеш -> offset в диапазоне, чтобы не улетать в огромные числа
    // Можно менять масштаб позже.
    const uint32 H = GetTypeHash(Name);
    return (int32)(H % 100000); // 0..99999
}

int32 AZoneActor::GetResolvedSeedOffset() const
{
    if (SeedOffset != INT32_MIN)
        return SeedOffset;

    return StableHashToOffset(ZoneId);
}
