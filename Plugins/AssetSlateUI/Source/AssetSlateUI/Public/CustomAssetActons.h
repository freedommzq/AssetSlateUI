#pragma once
#include "AssetTypeActions_Base.h"

/*
	�½���Դʵ���Ĳ˵��Լ���Դ�����ʵ��ͼ��
*/

class FCustomAssetActions : public FAssetTypeActions_Base
{
public:
	/*
		����̳еĴ��麯��
	*/
	//ʵ��ͼ��
	virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;

	//��Ӧ����Դ����
	virtual UClass* GetSupportedClass() const override;

	//�˵�ͼ����ɫ
	virtual FColor GetTypeColor() const override;

	//�˵��е���ʾ����
	virtual FText GetName() const;

	//�˵��е�����Ŀ¼
	virtual uint32 GetCategories();

	//˫��ͼ��ʱ���ã��򿪱༭��ʵ��
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/) override;
};