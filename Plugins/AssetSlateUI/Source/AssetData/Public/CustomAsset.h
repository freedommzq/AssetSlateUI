// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//���ܷŵ��������ݵ�����
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MeshImport.h"
#include "ProceduralMeshComponent.h"

#include "CustomAsset.generated.h"//��������

//���ģ����������
struct FCustomAssetCache
{
	int32 VerticesNum = 0;
	int32 TrianglesNum = 0;
	int32 NormalsNum = 0;
	int32 UV0Num = 0;
	int32 UV1Num = 0;
	int32 UV2Num = 0;
	int32 TangentsNum = 0;
};

USTRUCT(BlueprintType)
struct FCustomMeshSection
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Section")
	TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Section")
	TArray<int32> Triangles;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Section")
	TArray<FVector> Normals;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Section")
	TArray<FVector2D> UV0;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Section")
	TArray<FVector2D> UV1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Section")
	TArray<FVector2D> UV2;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Section")
	TArray<FProcMeshTangent> Tangents;
};

USTRUCT(BlueprintType)
struct FCustomMeshLOD
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LOD")
	TArray<FCustomMeshSection> Sections;
};

UCLASS()
class ASSETDATA_API UCustomAsset : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Mesh")
	TArray<FCustomMeshLOD> LODs;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CustomAsset")
	FMeshImport MeshImport;

	UCustomAsset();

	//���������Ƿ���
	bool IsModified();

	void ClearMesh();
private:
	void CreateBox();

	FCustomAssetCache CustomAssetCache;
};