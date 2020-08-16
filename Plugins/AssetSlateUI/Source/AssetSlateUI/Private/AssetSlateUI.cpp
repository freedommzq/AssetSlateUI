// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AssetSlateUI.h"
#include "AssetToolsModule.h"
#include "CustomAssetActons.h"
#include "MeshImportPanel.h"

#define LOCTEXT_NAMESPACE "FAssetSlateUIModule"

void FAssetSlateUIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools &AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisteredAssetTypeActions.Add(MakeShareable(new FCustomAssetActions()));
	AssetTools.RegisterAssetTypeActions(RegisteredAssetTypeActions[RegisteredAssetTypeActions.Num() - 1]);

	FPropertyEditorModule &PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");//ģ�����
	RegisterPropertyTypeCustomizations();//ע��
	PropertyModule.NotifyCustomizationModuleChanged();//ˢ��
}

void FAssetSlateUIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAssetToolsModule *AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (AssetToolsModule != nullptr)
	{
		IAssetTools &AssetTools = AssetToolsModule->Get();
		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
}

void FAssetSlateUIModule::RegisterPropertyTypeCustomizations()
{
	//����MeshImport�������ƺʹ������а�
	// DataAttribute��DetailsView������Objectʱ��⵽CustomAsset���Object����MeshImport�����MeshImportDetail�Ĵ���ʵ������
	RegisterCustomPropertyTypeLayout("MeshImport", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMeshImportDetail::MakeInstance));
}

void FAssetSlateUIModule::RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate)
{
	check(PropertyTypeName != NAME_None);

	// �洢�����ӵ����ԣ�Ϊʹ����Ϻ����ж��
	RegisteredPropertyTypes.Add(PropertyTypeName);

	FPropertyEditorModule &PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(PropertyTypeName, PropertyTypeLayoutDelegate);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetSlateUIModule, AssetSlateUI)