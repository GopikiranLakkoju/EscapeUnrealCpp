// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"

#define OUT

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Opens/Close door
	void OpenOrCloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable)
		FOnOpenRequest OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FOnCloseRequest OnCloseRequest;

private:
	/// Properties
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressureSwitch = nullptr;
	UPROPERTY(EditAnywhere)
		AActor* Roamer = nullptr;
	AActor* Owner;
	// 90d
	const float YawAngleOpen = 90.0;
	// -180d
	const float YawAngleClose = -180.0;
	bool CanOpen;
	float TriggerMass = 30.0;


	/// methods
	float MassOfActorsOnPressureSwitch();
	void PrintLogOnOpenLog(FString);
};
