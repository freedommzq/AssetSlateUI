#include "MeshImportPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Images/SImage.h"
#include "AssetToolsModule.h"
#include "DetailWidgetRow.h"
#include "EditorDirectories.h"
#include "KismetProceduralMeshLibrary.h"
#include "CustomAsset.h"
#include "Engine/StaticMesh.h"
#include <fstream>

#define LOCTEXT_NAMESPACE "FMeshImportDetail"

ASSETSLATEUI_API TWeakObjectPtr<UCustomAsset> CustomAssetInstance = nullptr;

void FMeshImportDetail::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow & HeaderRow, IPropertyTypeCustomizationUtils & CustomizationUtils)
{
	HeaderRow
	.NameContent()
	[
		SAssignNew(EditableTextBox, SEditableTextBox)
		.OnTextCommitted(this, &FMeshImportDetail::OnLabelsRootTextCommited)
	]
	.ValueContent()
	.MinDesiredWidth(125.0f)
	.MaxDesiredWidth(325.0f)
	[
		SNew(SButton)
		.OnClicked(this, &FMeshImportDetail::HandleImportClicked)
		.Text(LOCTEXT("Import", "Import Mesh"))
	];
}

void FMeshImportDetail::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder & ChildBuilder, IPropertyTypeCustomizationUtils & CustomizationUtils)
{
	HandleMeshSavePath = PropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FMeshImport, MeshSavePath));//�������е����������

	// ���´�ʱ�ܹ���ʾ֮ǰʹ�õ�·��
	if (EditableTextBox.IsValid())
	{
		FText EventValueStr;
		HandleMeshSavePath->GetValue(EventValueStr);

		if (HandleMeshSavePath.IsValid())
		{
			EditableTextBox->SetText(EventValueStr);
		}
	}
}

TSharedRef<IPropertyTypeCustomization> FMeshImportDetail::MakeInstance()
{
	return MakeShareable(new FMeshImportDetail);
}

FReply FMeshImportDetail::HandleImportClicked()
{
	//FString MeshNewPath = TEXT("/Game");	
	
	//��ȡ��·��
	FText EventValueStr;
	HandleMeshSavePath->GetValue(EventValueStr);
	parseCubeFile(TCHAR_TO_UTF8(*EventValueStr.ToString()));

	//if (EventValueStr.IsEmpty())
	//{
	//	FAssetToolsModule &AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");//��ȡ��Դģ��
	//	AssetToolsModule.Get().ImportAssetsWithDialog(MeshNewPath);

	//	//LastPath = D:\UE4\CTest\Content\RustedCar.obj
	//	FString LastPath = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT);

	//	FString L, R, N, S;
	//	LastPath.Split("/", &L, &R, ESearchCase::IgnoreCase, ESearchDir::FromEnd);//L = D:\UE4\CTest\Content, R = RustedCar.obj
	//	R.Split(".", &N, &S);//N = RustedCar, S = obj
	//	MeshNewPath.Append("/" + N);//MeshNewPath = /Game/RustedCar
	//}
	//else
	//{
	//	MeshNewPath += (TEXT("/") + EventValueStr.ToString());
	//}

	//if (CustomAssetInstance.IsValid()) 
	//{
	//	//��ȡģ���ļ�����
	//	UStaticMesh *ObjectMesh = Cast<UStaticMesh>(StaticLoadObject(UObject::StaticClass(), NULL, *MeshNewPath));
	//	if (ObjectMesh) 
	//	{
	//		for (int32 LOD = 0; LOD < ObjectMesh->RenderData->LODResources.Num(); ++LOD)
	//		{
	//			FCustomMeshLOD CustomMeshLOD;
	//			for (int32 Section = 0; Section < ObjectMesh->RenderData->LODResources[LOD].Sections.Num(); ++Section)
	//			{
	//				FCustomMeshSection CustomMeshSection;

	//				UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(
	//					ObjectMesh,
	//					LOD,
	//					Section,
	//					CustomMeshSection.Vertices,
	//					CustomMeshSection.Triangles,
	//					CustomMeshSection.Normals,
	//					CustomMeshSection.UV0,
	//					CustomMeshSection.Tangents
	//				);//��ָ������LOD��ָ������Section��ģ�����ݵ���

	//				CustomMeshLOD.Sections.Add(CustomMeshSection);
	//			}
	//			CustomAssetInstance->LODs.Add(CustomMeshLOD);
	//		}
	//	}
	//}

	return FReply::Handled();
}

void FMeshImportDetail::OnLabelsRootTextCommited(const FText & InText, ETextCommit::Type InCommitType) const
{
	if (HandleMeshSavePath.IsValid())
	{
		// ͨ��Handle�����ݽ��и���
		HandleMeshSavePath->SetValue(InText);
	}
}

void FMeshImportDetail::parseCubeFile(const std::string & path)
{
	CustomAssetInstance->LODs.Empty();
	
	std::fstream fs;
	fs.open(path.c_str(), std::ios_base::in);
	if (!fs.is_open())
		return;

	FCustomMeshLOD CustomMeshLOD;
	FCustomMeshSection CustomMeshSection;

	std::string str;
	while (fs.good())
	{
		fs >> str;

		if (str.empty())
			continue;

		if (str == "v") {
			float x, y, z;
			fs >> x >> y >> z;
			CustomMeshSection.Vertices.Add(FVector(x, y, z));
		}
		else if (str == "t") {
			int p1, p2, p3;
			fs >> p1 >> p2 >> p3;
			CustomMeshSection.Triangles.Add(p1);
			CustomMeshSection.Triangles.Add(p2);
			CustomMeshSection.Triangles.Add(p3);
		}
	}

	CustomMeshLOD.Sections.Add(CustomMeshSection);
	CustomAssetInstance->LODs.Add(CustomMeshLOD);

	fs.close();
}

#undef LOCTEXT_NAMESPACE