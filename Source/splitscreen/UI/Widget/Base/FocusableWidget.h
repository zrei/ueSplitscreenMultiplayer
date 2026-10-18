// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "FocusableWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFocusableWidgetEvent);

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UFocusableWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFocusableWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnWidgetOpen();

	virtual void NativeOnWidgetClose();

	virtual void NativeOnWidgetReopened();

	virtual void NativeOnWidgetHide();

	UFUNCTION(BlueprintCallable)
	bool TryCloseWidget();

protected:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent) override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeHandleKeyActivated(const FKey& Key);

	virtual void NativeSetCustomNavigation();

	virtual bool NativeCanCloseWidget();

	virtual void NativeConstruct() override;

	virtual void NativeDoScroll(float ScrollAmount);

	virtual void NativeSetInitialFocus();

	virtual void NativeOnSwitchToKBM();

	virtual void NativeOnSwitchToGamepad();

	virtual void NativeOnDelayCompleteEvent(FName Key);

private:
	void CloseWidget();

	void TrySwitchControlMode(bool bIsKBM);

	void OnDelayAnimComplete();

	void SwitchScrollViewInputMode();

protected:
	// blueprint functions that can be called together with the native implementations
	UFUNCTION(BlueprintImplementableEvent)
	void SetInitialFocus();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleKeyActivated(const FKey& Key);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCustomNavigation();

	UFUNCTION(BlueprintNativeEvent)
	bool CanCloseWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void DoScroll(float ScrollAmount);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetOpen();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetClose();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetReopened();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetHide();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSwitchToKBM();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSwitchToGamepad();

	// blueprint functions that are callable
	UFUNCTION(BlueprintCallable)
	void SetDelay(FName Key, float Delay);

	UFUNCTION(BlueprintCallable)
	void CancelCurrDelay();

	UFUNCTION(BlueprintCallable)
	void CancelSpecificDelay(FName DelayKey);

	void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDelayCompleteEvent(FName Key);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool IsKBM;

	// move these to a DA through the UI manager afterwards
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float MouseMoveErrorThresholdSquared = 0.02f;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float AnalogStickMoveErrorThresholdSquared = 0.02f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<FKey> WillNotHandleKeyArray;

	// no FMOD for now
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<USoundBase> OpenSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<USoundBase> CloseSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool PlayOpenSoundOnReopen;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TObjectPtr<UScrollBox>> ScrollBoxes;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool CanManuallyClose;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FKey ManualCloseKey;

private:
	TObjectPtr<UWidgetAnimation> DelayAnimation;

	FName CurrDelayKey;

	FWidgetAnimationHandle DelayAnimationHandle;

	bool HasCancelledDelay;

public:
	UPROPERTY(BlueprintAssignable)
	FFocusableWidgetEvent OnWidgetOpened;

	UPROPERTY(BlueprintAssignable)
	FFocusableWidgetEvent OnWidgetClosed;
};
