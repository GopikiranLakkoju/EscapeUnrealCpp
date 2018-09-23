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

	// Look for attached Physics handler
	PhysicsHandler = Player->FindComponentByClass<UPhysicsHandleComponent>();
	// Looks for input component that is attached on begin play
	PawnInput = Player->FindComponentByClass<UInputComponent>();

	if (PhysicsHandler || PawnInput)
	{
		PawnInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing physics handle Or Input component"), *Player->GetFName().ToString());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Key press binging working"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector playerLocation;
	FRotator playerRotation;
	// Gets the  player view point
	World->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Player view point location %s rotation %s"), *playerLocation.ToString(), *playerRotation.ToString());

	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * FarReach;
		
	// Debug visual line tracing of viewpoint
	DrawDebugLine(World, playerLocation, lineTraceEnd, FColor(255, 0, 0), false, 0.0, 0.0, 10.0);

	/// line trace(aka ray casting) out to reach distance
	FHitResult hit;
	// collision parameters
	FCollisionQueryParams collisionQueryParams(FName(TEXT("")), false, Player);
	World->LineTraceSingleByObjectType(OUT hit, playerLocation, lineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), collisionQueryParams);
	AActor* actorThatWasHit = hit.GetActor();
	if (actorThatWasHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor that was collided %s"), *(actorThatWasHit->GetName()));
	}	
}

