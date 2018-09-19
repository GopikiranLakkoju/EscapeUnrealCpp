// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector playerLocation;
	FRotator playerRotation;
	UWorld* world = GetWorld();
	// Gets the  player view point
	world->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Player view point location %s rotation %s"), *playerLocation.ToString(), *playerRotation.ToString());

	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * FarReach;

	// Debug visual line tracing of viewpoint
	DrawDebugLine(world, playerLocation, lineTraceEnd, FColor(255, 0, 0), false, 0.0, 0.0, 10.0);
}

