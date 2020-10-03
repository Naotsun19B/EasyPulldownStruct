// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetailCustomizations.h"
#include "IPropertyTypeCustomization.h"

class IPropertyUtilities;
class IPropertyHandle;
class FDetailWidgetRow;
class IDetailChildrenBuilder;
class STextComboBox;
enum class ECheckBoxState : uint8;

/**
 * プルダウンメニューのカスタム詳細設定の基底クラス.
 */
class EASYPULLDOWNSTRUCTED_API IEPS_PulldownDetail : public IPropertyTypeCustomization
{
private:
	TSharedPtr<IPropertyHandle> StructPropertyHandle;
	TSharedPtr<IPropertyHandle> KeyHandle;
	TSharedPtr<STextComboBox> KeyComboBox;
	TSharedPtr<IPropertyUtilities> PropertyUtilities;

protected:
	TArray<TSharedPtr<FString>> DisplayStrings;

public:
	// Create a new instance with a list of strings.
	static TSharedRef<IPropertyTypeCustomization> MakeInstance(const TArray<TSharedPtr<FString>>& InDisplayStrings);

	// IPropertyTypeCustomization interface.
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	// End of IPropertyTypeCustomization interface.

protected:
	// Called when the value of the combo box in the pull-down menu changes.
	virtual void OnStateValueChanged(TSharedPtr<FString> ItemSelected, ESelectInfo::Type SelectInfo);
};
