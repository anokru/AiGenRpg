#include "WorldStateSubsystem.h"

void UWorldStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UE_LOG(LogTemp, Warning, TEXT("WorldStateSubsystem Initialized"));
}
