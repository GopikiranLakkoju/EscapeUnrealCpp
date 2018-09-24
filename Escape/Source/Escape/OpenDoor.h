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
	void OpenOrCloseDoor(int);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/// Properties
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressureSwitch;
	UPROPERTY(EditAnywhere)
		AActor* Roamer;
	AActor* Owner;
	const float YawAngleOpen = -180.0;
	const float YawAngleClose = 90.0;

	/// methods
	float MassOfActorsOnPressureSwitch();
	void PrintLogOnOpenLog(FString);
};
