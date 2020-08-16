#include "CustomAssetEditorToolkit.h"
#include "Widgets/Images/SImage.h"
//#include "Widgets/Docking/SDockTab.h"
#include "SCustomAssetViewport.h"
#include "CustomDataAttribute.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

namespace CustomAssetEditor
{
	static const FName AssetEditorID("CustomAssetEd"); //tab的标题
	static const FName AppID("CustomAssetEditorApp");
	static const FName CustomPanelID("CustomPanelEd");
}

void FCustomAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{	
	//注册编辑器内窗口等组件
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

	//弹出编辑器窗口，排布并显示组件
	const TSharedRef<FTabManager::FLayout> StandloneCustomLayout = FTabManager::NewLayout("StandloneCustomLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(CustomAssetEditor::AssetEditorID, ETabState::OpenedTab) /*将注册的内容在此处添加*/
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(CustomAssetEditor::CustomPanelID, ETabState::OpenedTab) /*将注册的内容在此处添加*/
			)
		);
	InitAssetEditor(
		Mode,
		InToolkitHost,
		CustomAssetEditor::AppID,
		StandloneCustomLayout,
		true,/*默认menu*/
		true,/*默认toolbar*/
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