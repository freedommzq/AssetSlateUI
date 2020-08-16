// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset.h"

#define CHECK_MESH_ZERO(VariableName)\
if (CustomAssetCache.VariableName != 0)\
{\
	bIsMoified = true;\
	CustomAssetCache.VariableName = 0;\
}

#define CHECK_MESH(VariableName)\
if (mIter.VariableName.Num() != CustomAssetCache.VariableName##Num)\
{\
	bIsMoified = true;\
	CustomAssetCache.VariableName##Num = mIter.VariableName.Num();\
}

UCustomAsset::UCustomAsset()
{
	CreateBox();
}

bool UCustomAsset::IsModified()
{
	bool bIsMoified = false;

	if(LODs.Num() == 0)
	{
		CHECK_MESH_ZERO(VerticesNum)
		CHECK_MESH_ZERO(TrianglesNum)
		CHECK_MESH_ZERO(NormalsNum)
		CHECK_MESH_ZERO(UV0Num)
		CHECK_MESH_ZERO(UV1Num)
		CHECK_MESH_ZERO(UV2Num)
		CHECK_MESH_ZERO(TangentsNum)
	}
	else
	{
		for (auto &nIter : LODs)
		{
			for (auto &mIter : nIter.Sections)
			{
				CHECK_MESH(Vertices)
				CHECK_MESH(Triangles)
				CHECK_MESH(Normals)
				CHECK_MESH(UV0)
				CHECK_MESH(UV1)
				CHECK_MESH(UV2)
				CHECK_MESH(Tangents)
			}
		}
	}

	return bIsMoified;
}

void UCustomAsset::ClearMesh()
{
	//Vertices.Empty();
	//Triangles.Empty();
}

void UCustomAsset::CreateBox()
{
	//Vertices.Add(FVector(0.f, 0.f, 0.f));
	//Vertices.Add(FVector(0.f, 100.f, 0.f));
	//Vertices.Add(FVector(100.f, 100.f, 0.f));
	//Vertices.Add(FVector(100.f, 0.f, 0.f));
	//Vertices.Add(FVector(0.f, 0.f, 100.f));
	//Vertices.Add(FVector(0.f, 100.f, 100.f));
	//Vertices.Add(FVector(100.f, 100.f, 100.f));
	//Vertices.Add(FVector(100.f, 0.f, 100.f));

	//Triangles.Add(0); Triangles.Add(1); Triangles.Add(5);
	//Triangles.Add(0); Triangles.Add(5); Triangles.Add(4);

	//Triangles.Add(1); Triangles.Add(2); Triangles.Add(6);
	//Triangles.Add(1); Triangles.Add(6); Triangles.Add(5);

	//Triangles.Add(2); Triangles.Add(3); Triangles.Add(7);
	//Triangles.Add(2); Triangles.Add(7); Triangles.Add(6);

	//Triangles.Add(3); Triangles.Add(0); Triangles.Add(4);
	//Triangles.Add(3); Triangles.Add(4); Triangles.Add(7);

	//Triangles.Add(5); Triangles.Add(6); Triangles.Add(7);
	//Triangles.Add(5); Triangles.Add(7); Triangles.Add(4);

	//Triangles.Add(1); Triangles.Add(3); Triangles.Add(2);
	//Triangles.Add(1); Triangles.Add(0); Triangles.Add(3);
}
