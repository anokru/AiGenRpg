#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZoneActor.generated.h"

class UBoxComponent;
class UPCGComponent;
class ULocationTypeDefinition;

UCLASS()
class AIGENRPG_API AZoneActor : public AActor
{
    GENERATED_BODY()

public:
    AZoneActor();

    // Unique zone id (used for deterministic seed offset).
    // If None, will fallback to ActorLabel (Editor) or Actor name (Runtime).
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    FName ZoneId = NAME_None;

    // Enable/disable zone without deleting it.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    bool bEnabled = true;

    // Seed offset relative to WorldSeed.
    // INT32_MIN = auto (stable hash from ZoneId).
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    int32 SeedOffset = INT32_MIN;

    // Location type (forest/hills/plains/water/swamp...). Seasons later.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    TObjectPtr<ULocationTypeDefinition> LocationType = nullptr;

    UFUNCTION(BlueprintCallable, Category = "Zone")
    UPCGComponent* GetPCG() const { return PCG; }

    UFUNCTION(BlueprintCallable, Category = "Zone")
    int32 GetResolvedSeedOffset() const;

    UFUNCTION(BlueprintCallable, Category = "Zone")
    FName GetResolvedZoneId() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zone")
    TObjectPtr<UBoxComponent> Box;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zone")
    TObjectPtr<UPCGComponent> PCG;

private:
    static int32 StableHashToOffset(const FString& S);
};
