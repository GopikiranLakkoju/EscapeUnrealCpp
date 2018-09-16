// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// gets sequence World->PlayerController->Pawn
	Roamer = GetWorld()->GetFirstPlayerController()->GetPawn();
	// gets owner
	Owner = GetOwner();
}

void UOpenDoor::OpenOrCloseDoor(int yawValue)
{	
	// pitch=y, yaw=z, roll=x
	FRotator rotator = FRotator(0.00, yawValue, 0.00);
	Owner->SetActorRotation(rotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressureSwitch->IsOverlappingActor(Roamer))
	{
		OpenOrCloseDoor(YawAngleClose);
	}
	else
	{
		OpenOrCloseDoor(YawAngleOpen);
	}
}

