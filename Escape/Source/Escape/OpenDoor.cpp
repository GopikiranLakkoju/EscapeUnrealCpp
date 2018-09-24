// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

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
	// initial pressure load with actor PressureSwitch->IsOverlappingActor(Roamer)
	if (MassOfActorsOnPressureSwitch() >= 30.0)
	{
		OpenOrCloseDoor(YawAngleClose);
	}
	else
	{
		OpenOrCloseDoor(YawAngleOpen);
	}
}

float UOpenDoor::MassOfActorsOnPressureSwitch()
{
	TArray<AActor*> overLappingActors;
	PressureSwitch->GetOverlappingActors(OUT overLappingActors);
	float massInWhole = 0.0;
	for (const AActor* actor : overLappingActors)
	{
		UPrimitiveComponent* component = actor->FindComponentByClass<UPrimitiveComponent>();
		if (component)
		{
			massInWhole += component->GetMass();
		}		
	}
	PrintLogOnOpenLog(FString::SanitizeFloat(massInWhole));
	return massInWhole;
}

void UOpenDoor::PrintLogOnOpenLog(FString printString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *printString);
}