// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"

#define OUT

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

private:
	/// Variables
	// Distance to stretch the ray casting from the mid of the body in cm
	float FarReach = 100.0;
	UWorld* World = GetWorld();
	AActor* Player = GetOwner();
	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	UInputComponent* PawnInput = nullptr;

	/// Methods
	// Ray-cast and grab what's in the reach
	void Grab();
	// Ray-cast and grab release what's in the reach
	void Release();
	// Line tracing though objects with Physics enabled
	FHitResult LineTracingThroughObjectChannel();
	// Deals with both setting up Physics and input component
	void FindPhysicsHandleAndSetupInputComponent();
	// Screen logging
	void PrintLogOnScreen(FString);
	void PrintLogOnOpenLog(FString);
	
	/// Constants
	const FString GRAB = "Grab";
};