// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrintLogOnOpenLog("Grabber reporting for duty");
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleAndSetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector playerLocation;
	FRotator playerRotation;
	// Gets the  player view point
	World->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);

	// Logs player rotation and location on 3dspace
	//UE_LOG(LogTemp, Warning, TEXT("Player view point location %s rotation %s"), *playerLocation.ToString(), *playerRotation.ToString());

	// Distance between mid of the body and length its extends	
	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * FarReach;
	PhysicsHandler->SetTargetLocation(lineTraceEnd);
}

void UGrabber::FindPhysicsHandleAndSetupInputComponent()
{
	// Look for attached Physics handler
	PhysicsHandler = Player->FindComponentByClass<UPhysicsHandleComponent>();
	// Looks for input component that is attached on begin play
	PawnInput = Player->FindComponentByClass<UInputComponent>();
		
	if (PhysicsHandler || PawnInput)
	{
		PawnInput->BindAction(*GRAB, IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction(*GRAB, IE_Released, this, &UGrabber::Release);
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("%s is missing physics handle Or Input component"), *Player->GetFName().ToString());
	}
}

FHitResult UGrabber::LineTracingThroughObjectChannel()
{
	FVector playerLocation;
	FRotator playerRotation;

	// Gets the  player view point
	World->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);	
	
	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * FarReach;;

	// Debug visual line tracing of viewpoint
	//DrawDebugLine(World, playerLocation, lineTraceEnd, FColor(255, 0, 0), false, 0.0, 0.0, 10.0);

	FHitResult hitResult;
	// collision parameters
	FCollisionQueryParams collisionQueryParams(FName(TEXT("")), false, Player);
	// line tracing (aka ray casting) based on player location and distance of the body to which it collides(Physics enabled bodies)
	World->LineTraceSingleByObjectType(OUT hitResult, playerLocation, lineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), collisionQueryParams);
	
	//AActor* actorThatWasHit = hitResult.GetActor();
	//if (actorThatWasHit)
	//{
	//	// commented just 
	//	//UE_LOG(LogTemp, Warning, TEXT("Actor that was collided %s"), *(actorThatWasHit->GetName()));
	//}
	return hitResult;
}

void UGrabber::Grab()
{
	//UE_LOG(LogTemp, Warning, TEXT("Key press binging working"));
	
	FHitResult hit = LineTracingThroughObjectChannel();
	// if no actor is found it gonna loop to get component and application would crash, learned it in a hard way
	if (hit.GetActor())
	{		UPrimitiveComponent* componentToGrab = hit.GetComponent();
		if (PhysicsHandler)
		{
			PrintLogOnScreen("Key press binging working");
			// attach physics handle
			PhysicsHandler->GrabComponentAtLocationWithRotation(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), componentToGrab->GetOwner()->GetActorRotation());
		}		
	}
}

void UGrabber::Release()
{
	//UE_LOG(LogTemp, Warning, TEXT("Key release binging working"));
	PrintLogOnScreen("Key release binging working");
	if (PhysicsHandler)
	{
		PhysicsHandler->ReleaseComponent();
	}	
}

void UGrabber::PrintLogOnScreen(FString printString)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%s"), *printString));
}

void UGrabber::PrintLogOnOpenLog(FString printString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *printString);
}