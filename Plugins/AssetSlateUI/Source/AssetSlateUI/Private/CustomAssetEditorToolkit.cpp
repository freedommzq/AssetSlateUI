#include "CustomAssetEditorToolkit.h"
#include "Widgets/Images/SImage.h"
//#include "Widgets/Docking/SDockTab.h"
#include "SCustomAssetViewport.h"
#include "CustomDataAttribute.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

namespace CustomAssetEditor
{
	static const FName AssetEditorID("CustomAssetEd"); //tab�ı���
	static const FName AppID("CustomAssetEditorApp");
	static const FName CustomPanelID("CustomPanelEd");
}

void FCustomAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{	
	//ע��༭���ڴ��ڵ����
	InTabManager->RegisterTabSpawner(CustomAssetEditor::AssetEditorID, FOnSpawnTab::CreateLambda(
		[&](const FSpawnTabArgs &Args)
		{
		return SNew(SDockTab)
			[
				SNew(SCustomAssetViewport)
				.CustomAsset(CustomTextAsset)
			];
		}
	));

	InTabManager->RegisterTabSpawner(CustomAssetEditor::CustomPanelID, FOnSpawnTab::CreateLambda(
		[&](const FSpawnTabArgs &Args)
	{
		return SNew(SDockTab)
			[
				SNew(SCustomDataAttribute)
				.CustomAsset(CustomTextAsset)
			];
	}
	));

	Super::RegisterTabSpawners(InTabManager);
}

void FCustomAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(CustomAssetEditor::AssetEditorID);
	InTabManager->UnregisterTabSpawner(CustomAssetEditor::CustomPanelID);

	Super::UnregisterTabSpawners(InTabManager);
}

void FCustomAssetEditorToolkit::initialize(UCustomAsset * InTextAsset, const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	CustomTextAsset = InTextAsset;

	//�����༭�����ڣ��Ų�����ʾ���
	const TSharedRef<FTabManager::FLayout> StandloneCustomLayout = FTabManager::NewLayout("StandloneCustomLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(CustomAssetEditor::AssetEditorID, ETabState::OpenedTab) /*��ע��������ڴ˴�����*/
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(CustomAssetEditor::CustomPanelID, ETabState::OpenedTab) /*��ע��������ڴ˴�����*/
			)
		);
	InitAssetEditor(
		Mode,
		InToolkitHost,
		CustomAssetEditor::AppID,
		StandloneCustomLayout,
		true,/*Ĭ��menu*/
		true,/*Ĭ��toolbar*/
		InTextAsset
	);
	RegenerateMenusAndToolbars();
}

FName FCustomAssetEditorToolkit::GetToolkitFName() const
{
	return FName("CustomAssetEditor");
}

FText FCustomAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Custom Asset Editor");
}

FString FCustomAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "CustomAsset ").ToString();
}

FLinearColor FCustomAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

#undef LOCTEXT_NAMESPACE