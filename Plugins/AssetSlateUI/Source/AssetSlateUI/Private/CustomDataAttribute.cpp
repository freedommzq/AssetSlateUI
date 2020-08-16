#include "CustomDataAttribute.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "CustomAsset.h"

extern ASSETSLATEUI_API TWeakObjectPtr<UCustomAsset> CustomAssetInstance;

void SCustomDataAttribute::Construct(const FArguments &InArgs)
{
	CustomAsset = InArgs._CustomAsset.Get();

	auto &PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;

	ConfigPanel = PropertyModule.CreateDetailView(DetailsViewArgs);

	ConfigPanel->SetObject(CustomAsset);//��ʱFMeshImportDetail��ʵ���������
	CustomAssetInstance = CustomAsset; // ͨ��ȫ�ֱ���ʹFMeshImportDetail��ȡ��CustomAsset

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			.WidthOverride(300)
			.MinDesiredWidth(300)
			.MaxDesiredWidth(300)
			[
				SNew(SBorder)
				[
					ConfigPanel.ToSharedRef()
				]
			]
		]
	];
}