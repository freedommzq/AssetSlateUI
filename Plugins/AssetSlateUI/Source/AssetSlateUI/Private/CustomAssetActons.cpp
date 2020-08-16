#include "CustomAssetActons.h"
#include "Widgets/Images/SImage.h"
#include "CustomAsset.h"
#include "CustomAssetEditorToolkit.h"

#define LOCTEXT_NAMESPACE "CustomAssetActions"

TSharedPtr<class SWidget> FCustomAssetActions::GetThumbnailOverlay(const FAssetData & AssetData) const
{
	return SNew(SImage);
}

UClass * FCustomAssetActions::GetSupportedClass() const
{
	return UCustomAsset::StaticClass();
}

FColor FCustomAssetActions::GetTypeColor() const
{
	return FColor::Red;
}

FText FCustomAssetActions::GetName() const
{
	return LOCTEXT("AssetTypeActions_CustomAsset", "Custom Asset");
}

uint32 FCustomAssetActions::GetCategories()
{
	return EAssetTypeCategories::UI;
}

void FCustomAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto It = InObjects.CreateConstIterator(); It; ++It)
	{
		//获取存储的数据信息
		auto CustomAsset = Cast<UCustomAsset>(*It);
		if (CustomAsset != nullptr)
		{
			//创建对应窗口并使用获取的数据信息初始化
			TSharedRef<FCustomAssetEditorToolkit> EditorToolkit = MakeShareable(new FCustomAssetEditorToolkit());
			EditorToolkit->initialize(CustomAsset, Mode, EditWithinLevelEditor);
		}
	}
}

#undef LOCTEXT_NAMESPACE