// WHYELAB 2021

#include "DrawDebugHelpers.h" // For DrawDebugLine()
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber1.h" // Should be below.

#define OUT

// Sets default values for this component's properties
UGrabber1::UGrabber1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber1::BeginPlay()
{
	Super::BeginPlay();

	// 4-47
	// -----------------------
	FindPhysicsHandle();
	SetupInputComponent();
	// -----------------------
	 
	// 4-38
	// -----------------------
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting for Duty!"));
	// -----------------------

	// 4-44
	// Checking for Physics Handle Component.
	// -----------------------
	// PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); // Get Owner, then find components by class then since only got 1 Physics handle...
	
	// if (PhysicsHandle) {
		// PhysicsHandle is Found.
	// }

	// else {
	// 	UE_LOG(LogTemp, Error, TEXT("NO PHYSICS HANDLE COMPONENT FOUND ON %s!"), *GetOwner()->GetName());
	// }
	// -----------------------

	// 4-45
	// -----------------------
	// InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	// if (InputComponent) { // Will always trigger since we already set there to be input component in the project settings. 
	// 	UE_LOG(LogTemp, Warning, TEXT("Input component found: %s"), *GetOwner()->GetName());
	// 	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber1::Grab); // IE is Input Event. Notice that Grab does not have () even though it is a function, because we are not actually calling the function but we are telling it where to go in order to call it when button is pressed.  
	//	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber1::Release);
	// }

	// else {
	//	UE_LOG(LogTemp, Warning, TEXT("Input component not found: %s"), *GetOwner()->GetName());
	// }
	// -----------------------
}

// Refactoring the code to a function. 
void UGrabber1::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input component found: %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber1::Grab); 
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber1::Release);
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("Input component not found: %s"), *GetOwner()->GetName());
	}
}

// Refactoring the code to a function. 
void UGrabber1::FindPhysicsHandle() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); 

	if (PhysicsHandle) { // PhysicsHandle is not null ptr.
		// PhysicsHandle is Found.
	}

	else { // PhysicsHandle is null ptr.
		UE_LOG(LogTemp, Error, TEXT("NO PHYSICS HANDLE COMPONENT FOUND ON %s!"), *GetOwner()->GetName());
	}
}

void UGrabber1::Grab() {
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Press"));

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // The 2 param are so called out params.

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);


	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	// Only Raycast when key is pressed. 
	// Try and reach any actors with physics body collision channel set. 
	// If we hit sth then attach the physics handle.
	// if (HitResult.GetActor()) {// If Actor is hit, attache the a Physics Handle.
	//	PhysicsHandle->GrabComponentAtLocation(
	//		ComponentToGrab,
	//		NAME_None, // We aren't using any skeletal mesh that have bones.
	//		LineTraceEnd // We need the LineTraceEnd we made previously. 
	//	);
	// }

	// 4-49
	// -----------------------
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit) {// If Actor is hit, attache the a Physics Handle.
		if (PhysicsHandle == nullptr) { return; } // To protect yourself.
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None, // We aren't using any skeletal mesh that have bones.
			GetPlayersReach() // We need the LineTraceEnd we made previously. 
		);
	}
	// -----------------------
}   

FVector UGrabber1::GetPlayersReach() const {
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Press"));

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // The 2 param are so called out params.

	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
	
	return LineTraceEnd;
}

void UGrabber1::Release() {
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));
	// Remove or release the physics handle.
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 4-49
	// -----------------------
	if (PhysicsHandle->GrabbedComponent) { // If we grabbed sth.
		// Set Target Location.
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}
	// ----------------------- 

	// 4-48
	// -----------------------	
	// FVector PlayerViewPointLocation;
	// FRotator PlayerViewPointRotation;

	// GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // The 2 param are so called out params.

	// FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	// if (PhysicsHandle->GrabbedComponent) { // If we grabbed sth.
		// Set Target Location.
	//	PhysicsHandle->SetTargetLocation(LineTraceEnd);
	// }
	// -----------------------

	// 4-39
	// Get Players' Viewpoint
	// -----------------------
	// FVector PlayerViewPointLocation;
	// FRotator PlayerViewPointRotation;

	// GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // The 2 param are so called out params.
	
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	// Logging out to test. 
	// -----------------------

	// 4-40
	// -----------------------
	// FVector PlayerViewPointLocation;
	// FRotator PlayerViewPointRotation;

	// GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // The 2 param are so called out params.

	// FVector LineTraceEnd = PlayerViewPointLocation + FVector(0.0, 0.0, 100.0); // Refer to the notes to see the vetor diagram. 
	// FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	// You will notice a green line on top of the player's head. 
	// DrawDebugLine(
		// GetWorld(), // It needs to know where it live so just GetWorld()...
		// PlayerViewPointLocation, // Line will Start from the top of our player
		// LineTraceEnd, // Will go 1 meter above the player straight up as the LineTraceEnd is set like that...
		// FColor(0, 255, 0), // Green Line.
		// false, 
		// 0.0, 
		// 0, 
		// 5.0); // 5 Pixel in Width.
	// -----------------------

	// 4-43
	// Ray-Cast out to a certain distance (Reach)
	// -----------------------
	// FHitResult Hit;
	// FCollisionQueryParams TraceParams(FName(TEXT("")), false,  GetOwner()); // Look at UNREAL Documentation to see what are the params. 

	// GetWorld()->LineTraceSingleByObjectType(
	//	OUT Hit,
	//	PlayerViewPointLocation, // Similar to DrawDebugLin()
	//	LineTraceEnd,
	//	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // ECollisonChannel is an enum.
	//	TraceParams
	//  );

	// See What it Hits.
	// AActor* ActorHit = Hit.GetActor();
	// if (ActorHit) {
	//	UE_LOG(LogTemp, Error, TEXT("Line Trace has Hit: %s"), *(ActorHit->GetName()));
	// }
	// -----------------------

	// If the physics handle is attached, move the object we are holding. 
}

FHitResult UGrabber1::GetFirstPhysicsBodyInReach() const{
	// FVector PlayerViewPointLocation;
	// FRotator PlayerViewPointRotation;

	// GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // The 2 param are so called out params.
	
	// FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
	
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner()); // Look at UNREAL Documentation to see what are the params. 

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPos(), // Similar to DrawDebugLin()
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // ECollisonChannel is an enum.
		TraceParams
	);

	// See What it Hits.
	// AActor* ActorHit = Hit.GetActor();
	// if (ActorHit) {
	//	UE_LOG(LogTemp, Error, TEXT("Line Trace has Hit: %s"), *(ActorHit->GetName()));
	// }
	
	return Hit;
}

FVector UGrabber1::GetPlayerWorldPos() const {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // The 2 param are so called out params.

	return PlayerViewPointLocation;
}