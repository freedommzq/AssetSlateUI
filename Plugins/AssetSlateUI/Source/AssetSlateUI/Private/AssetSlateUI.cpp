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

	FPropertyEditorModule &PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");//模块加载
	RegisterPropertyTypeCustomizations();//注册
	PropertyModule.NotifyCustomizationModuleChanged();//刷新
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
	//导入MeshImport，将名称和代理进行绑定
	// DataAttribute的DetailsView在设置Object时检测到CustomAsset这个Object含有MeshImport则调用MeshImportDetail的创建实例方法
	RegisterCustomPropertyTypeLayout("MeshImport", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMeshImportDetail::MakeInstance));
}

void FAssetSlateUIModule::RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate)
{
	check(PropertyTypeName != NAME_None);

	// 存储新添加的属性，为使用完毕后进行卸载
	RegisteredPropertyTypes.Add(PropertyTypeName);

	FPropertyEditorModule &PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(PropertyTypeName, PropertyTypeLayoutDelegate);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetSlateUIModule, AssetSlateUI)