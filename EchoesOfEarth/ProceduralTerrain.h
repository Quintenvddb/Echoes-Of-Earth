#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralTerrain.generated.h"

UCLASS()
class YOURGAME_API AProceduralTerrain : public AActor
{
    GENERATED_BODY()

public:
    AProceduralTerrain();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Terrain")
    UProceduralMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Terrain")
    int32 GridSize = 100;  // Number of vertices in X and Y direction

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Terrain")
    float Scale = 100.0f;  // Scale of the terrain grid

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Terrain")
    float HeightMultiplier = 200.0f;  // Max height variation

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedural Terrain")
    float NoiseScale = 0.1f;  // Perlin noise scale

private:
    void GenerateTerrain();
    float GetPerlinNoise(float X, float Y);
};
