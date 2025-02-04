#include "ProceduralTerrain.h"
#include "Kismet/KismetMathLibrary.h"

AProceduralTerrain::AProceduralTerrain()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
    RootComponent = MeshComponent;
}

void AProceduralTerrain::BeginPlay()
{
    Super::BeginPlay();
    GenerateTerrain();
}

void AProceduralTerrain::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProceduralTerrain::GenerateTerrain()
{
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector2D> UVs;
    TArray<FVector> Normals;
    TArray<FProcMeshTangent> Tangents;

    for (int Y = 0; Y <= GridSize; Y++)
    {
        for (int X = 0; X <= GridSize; X++)
        {
            float WorldX = X * Scale;
            float WorldY = Y * Scale;
            float WorldZ = GetPerlinNoise(WorldX, WorldY) * HeightMultiplier;

            Vertices.Add(FVector(WorldX, WorldY, WorldZ));
            UVs.Add(FVector2D((float)X / GridSize, (float)Y / GridSize));
            Normals.Add(FVector(0, 0, 1));
            Tangents.Add(FProcMeshTangent(1, 0, 0));
        }
    }

    for (int Y = 0; Y < GridSize; Y++)
    {
        for (int X = 0; X < GridSize; X++)
        {
            int Index = Y * (GridSize + 1) + X;

            Triangles.Add(Index);
            Triangles.Add(Index + GridSize + 1);
            Triangles.Add(Index + 1);

            Triangles.Add(Index + 1);
            Triangles.Add(Index + GridSize + 1);
            Triangles.Add(Index + GridSize + 2);
        }
    }

    MeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, {}, Tangents, true);
    MeshComponent->SetMaterial(0, nullptr);  // Set your own material if needed
}

float AProceduralTerrain::GetPerlinNoise(float X, float Y)
{
    return UKismetMathLibrary::PerlinNoise2D(FVector2D(X * NoiseScale, Y * NoiseScale));
}
