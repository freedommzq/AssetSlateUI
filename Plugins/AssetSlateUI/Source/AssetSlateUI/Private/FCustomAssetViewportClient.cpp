#include "FCustomAssetViewportClient.h"
#include "AssetEditorModeManager.h"
#include "ProceduralMeshComponent.h"

FCustomAssetViewportClient::FCustomAssetViewportClient(FPreviewScene &InPreviewScene, UCustomAsset* NewCustomAsset, const TWeakPtr<class SEditorViewport>& InEditorViewportWidget)
	: FEditorViewportClient(NULL, &InPreviewScene, InEditorViewportWidget)
	,CustomAsset(NewCustomAsset)
{
	((FAssetEditorModeManager*)ModeTools)->SetPreviewScene(PreviewScene);
	DrawHelper.bDrawGrid = true;//网格
	DrawHelper.bDrawPivot = true;//中心
	SetRealtime(true);
	SetViewMode(VMI_Lit); //光照模式
	SetViewLocation(FVector(500, 300, 500)); //观察位置

	CreateMeshLOD();

	OnPropertyChanged();
}

void FCustomAssetViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);
	
	//监视是否更新模型的数据数量（一般是更换模型）
	if (CustomAsset)
	{
		if (CustomAsset->IsModified())
		{
			OnPropertyChanged();
		}
		else
		{
			for (int32 LOD = 0; LOD < CustomAsset->LODs.Num(); ++LOD)
			{
				for (int32 Section = 0; Section < CustomAsset->LODs[LOD].Sections.Num(); ++Section)
				{
					if (ProceduralMesh.IsValidIndex(LOD))
					{
						TArray<FColor> VertexColors;					
						ProceduralMesh[LOD]->UpdateMeshSection(
							Section,
							CustomAsset->LODs[LOD].Sections[Section].Vertices,
							CustomAsset->LODs[LOD].Sections[Section].Normals,
							CustomAsset->LODs[LOD].Sections[Section].UV0,
							VertexColors,
							CustomAsset->LODs[LOD].Sections[Section].Tangents
						);
					}
					else
					{
						OnPropertyChanged();
					}
				}
			}
		}
	}

	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);	
}

void FCustomAssetViewportClient::OnPropertyChanged()
{
	if (CustomAsset)
	{
		if (CustomAsset->LODs.Num() == 0)
		{
			for (int32 LOD = 0; LOD < ProceduralMesh.Num(); ++LOD)
			{					
				ProceduralMesh[LOD]->ClearAllMeshSections();
			}
		}
		else
		{
			for (int32 LOD = 0; LOD < CustomAsset->LODs.Num(); ++LOD)
			{
				for (int32 Section = 0; Section < CustomAsset->LODs[LOD].Sections.Num(); ++Section)
				{
					if (ProceduralMesh.IsValidIndex(LOD))
					{
						TArray<FColor> VertexColors;
						ProceduralMesh[LOD]->CreateMeshSection(
							Section,
							CustomAsset->LODs[LOD].Sections[Section].Vertices,
							CustomAsset->LODs[LOD].Sections[Section].Triangles,
							CustomAsset->LODs[LOD].Sections[Section].Normals,
							CustomAsset->LODs[LOD].Sections[Section].UV0,
							VertexColors,
							CustomAsset->LODs[LOD].Sections[Section].Tangents,
							false
						);
					}
					else
					{
						if (CreateMeshLOD((LOD + 1) - ProceduralMesh.Num()))
						{
							TArray<FColor> VertexColors;
							ProceduralMesh[LOD]->CreateMeshSection(
								Section,
								CustomAsset->LODs[LOD].Sections[Section].Vertices,
								CustomAsset->LODs[LOD].Sections[Section].Triangles,
								CustomAsset->LODs[LOD].Sections[Section].Normals,
								CustomAsset->LODs[LOD].Sections[Section].UV0,
								VertexColors,
								CustomAsset->LODs[LOD].Sections[Section].Tangents,
								false
							);
						}
					}
				}
			}
		}

	}
}

bool FCustomAssetViewportClient::CreateMeshLOD(int32 LODNumber)
{
	bool IsSuccess = true;
	for (int32 i = 0; i < LODNumber; ++i)
	{
		UProceduralMeshComponent *ProceduralMeshComponent = NewObject<UProceduralMeshComponent>(PreviewScene->GetWorld(), TEXT("PreviewMesh"));
		if (!ProceduralMeshComponent)
		{
			IsSuccess = false;
			return IsSuccess;
		}
		else
		{
			PreviewScene->AddComponent(ProceduralMeshComponent, FTransform::Identity);
			ProceduralMesh.Add(ProceduralMeshComponent);
		}
	}
	return IsSuccess;
}
