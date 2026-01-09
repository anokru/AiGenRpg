#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZoneActor.generated.h"

class UPCGComponent;

UCLASS()
class AIGENRPG_API AZoneActor : public AActor
{
    GENERATED_BODY()

public:
    AZoneActor();

    // Уникальный ID зоны (для логов/детерминизма/будущих систем)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    FName ZoneId = "Zone";

    // Можно отключать зону без удаления
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    bool bEnabled = true;

    // Смещение относительно WorldSeed.
    // Если = INT32_MIN -> будет авто-расчёт по ZoneId (детерминированно)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
    int32 SeedOffset = INT32_MIN;

    // Вернуть PCG компонент (если он не на актёре — вернёт nullptr)
    UPCGComponent* GetPCG() const;

    // Рассчитать авто-offset по ZoneId (детерминированно)
    int32 GetResolvedSeedOffset() const;

private:
    // Хелпер для хеша
    static int32 StableHashToOffset(const FName& Name);
};
