// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
// #include "WorldPosition.generated.h"
#include "Components/PrimitiveComponent.h" // Needed for the for loop of TotalMassOfActors().
#include "Engine/World.h"
#include "GameFrameWork/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// 4-19
	// -------------------
	// float MyFloat = 10.0f; // The f tells it that it is definitely float.

	// FRotator CurrentRotation = GetOwner()->GetActorRotation();
	// CurrentRotation.Yaw = 90.0;
	// GetOwner()->SetActorRotation(CurrentRotation);
	// -------------------
	// Same as the code above.
	// -------------------
	// FRotator OpenDoor = { 0.0, 90.0, 0.0 };
	// GetOwner()->SetActorRotation(OpenDoor);
	// -------------------

	// 4-23
	// With these you don't need to know the absolute value of the degree of which your door is currently at. 
	// -------------------
	// InitialYaw = GetOwner()->GetActorRotation().Yaw;
	// CurrentYaw = InitialYaw;
	// OpenAngle = InitialYaw + 90.0; // + or - will cause door to open inwards or outwards.
	// -------------------

	// 4-25
	// -------------------
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw; 
	// -------------------

	// 4-52
	// -------------------
	FindPressurePlate();
	FindAudioComponent();
	// -------------------

	// 4-31 
	// With this, you can see exactly which actor is the one causing the crash. 
	// -------------------
	// if (!PressurePlate) {
	//	UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressureplate set"), *GetOwner()->GetName());
		// ActorName has the open door component on it, but no pressureplate set. 
	// }
	// -------------------

	// 4-32
	// Now you can go further down the -> into the GetPawn() to get other properties but now this will do. 
	// -------------------
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); // GetPawn() returns a pawn and pawn inherits from actor. ActorThatOpens can be set to this pawn because pawn is a subset of actors.
	// -------------------
}


// 4-52
void UOpenDoor::FindAudioComponent() { // Cannot be const. Otherwise the AudioComponent will have error.
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent) { 
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component!"), *GetOwner()->GetName()); 
	}
}

// 4-52/4-31
void UOpenDoor::FindPressurePlate() {
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component on it, but no pressureplate set"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 4-21
	// -------------------
	// FRotator CurrentRotation = GetOwner()->GetActorRotation();
	// CurrentRotation.Yaw = 90.0;
	// FRotator OpenDoor = { 0.0, 90.0, 0.0 };
	// GetOwner()->SetActorRotation(OpenDoor);
	// -------------------
	// 
	// -------------------
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Yaw is :%f"), GetOwner()->GetActorRotation().Yaw);
	
	// float CurrrentYaw = GetOwner()->GetActorRotation().Yaw;
	// FRotator OpenDoor(0.0, OpenAngle, 0.0);
	// OpenDoor.Yaw = FMath::Lerp(CurrrentYaw, OpenAngle, 0.1); // The last Param is the rate of door opening.
	// OpenDoor.Yaw = FMath::FInterpConstantTo(CurrrentYaw, OpenAngle, DeltaTime, 45); // Linearly.
	// OpenDoor.Yaw = FMath::FInterpTo(CurrrentYaw, OpenAngle, DeltaTime, 2); // Exponentially.
	// GetOwner()->SetActorRotation(OpenDoor);

	// FMath::Lerp(/*Starting Yaw, Targert Yaw, 0-1*/);
	// -------------------

	// 4-23
	// Relative Instead of using Absolute.
	// Which means you can rotate the entire door to a particular degree without knowing what degree it is, it will always rotate the same way. 
	// -------------------
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, 0.02);
	// FRotator DoorRotation = GetOwner()->GetActorRotation(); 
	// DoorRotation.Yaw = CurrentYaw; // Assign the changing value of CurrentYaw to the DoorRotation.Yaw in order to rotate it. 
	// GetOwner()->SetActorRotation(DoorRotation);
	// -------------------

	// 4-27
	// Now instead of previously, the CurrentYaw is being open with respect to the DeltaTime which effectively cancel out the issues due to differing frame rate.
	// -------------------
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Yaw is :%f"), GetOwner()->GetActorRotation().Yaw);
	// 
	// float rateOpen = 1.0;
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * rateOpen); // Just change the rateOpen in order to change the rate of door opening. 
	// FRotator DoorRotation = GetOwner()->GetActorRotation();
	// DoorRotation.Yaw = CurrentYaw; // Assign the changing value of CurrentYaw to the DoorRotation.Yaw in order to rotate it. 
	// GetOwner()->SetActorRotation(DoorRotation);
	// ------------------- 

	// 4-29
	// -------------------
	// Can cause crashing due to NULL Pointer, dereferencing a NULL Pointer can cause random crashes. 
	// if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
	// 	OpenDoor(DeltaTime);
	// }
	
	// OpenDoor(DeltaTime); // For Testing that the door opens. 
	// -------------------

	// 4-31
	// Lazy Evaluation prevention of crashing. 
	// -------------------
	// if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) { // Now even when you add the OpenDoor Component to the sphere, it won't crash UnReal.
	// 	OpenDoor(DeltaTime);
	// }

	// else {
	// 	CloseDoor(DeltaTime);
	// }
	// -------------------

	// 4-34
	// -------------------
	// if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) { // Now even when you add the OpenDoor Component to the sphere, it won't crash UnReal.
	// 	OpenDoor(DeltaTime);

		// DoorLastOpened = When the door was open.
	//	DoorLastOpened = GetWorld()->GetTimeSeconds();
	// }

	// else {
		// If the door has been open longer than DoorCloseDelta...
	//	if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay) {
	//		CloseDoor(DeltaTime);
	//	}
	// }
	// -------------------
	
	// 4-50
	// -------------------
	if (TotalMassOfActors() > MassToOpenDoor) { // Only when the mass on the pressure plate is more than 50kg then it will open the door. 
		OpenDoor(DeltaTime);

		// DoorLastOpened = When the door was open.
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}

	else {
		// If the door has been open longer than DoorCloseDelta...
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay) {
			CloseDoor(DeltaTime);
		}
	}
	// -------------------
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	// 4-29
	// -------------------
	// float rateOpen = 1.0;
	// CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * rateOpen); // Just change the rateOpen in order to change the rate of door opening. 
	// FRotator DoorRotation = GetOwner()->GetActorRotation();
	// DoorRotation.Yaw = CurrentYaw; // Assign the changing value of CurrentYaw to the DoorRotation.Yaw in order to rotate it. 
	// GetOwner()->SetActorRotation(DoorRotation);
	// -------------------

	// 4-35
	// -------------------
	// AudioComponent->Play();
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed); // Just change the rateOpen in order to change the rate of door opening. 
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw; // Assign the changing value of CurrentYaw to the DoorRotation.Yaw in order to rotate it. 
	GetOwner()->SetActorRotation(DoorRotation);

	// -------------------
	// 4-52
	// -------------------
	CloseDoorSound = false;

	if (!AudioComponent) { return; }

	if (!OpenDoorSound) {
		AudioComponent->Play(); // To play the sound. 
		OpenDoorSound = true;
		// UE_LOG(LogTemp, Warning, TEXT("Audio Played\n")); // The reason it is not playing is that it is being play so fast that it is probably repeatedly executing the first like microsecond of the music only. 
	}
	// -------------------
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// 4-33
	// -------------------
	// float rateClose = 1.3;
	// CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * rateClose); // Just change the rateOpen in order to change the rate of door opening. 
	// FRotator DoorRotation = GetOwner()->GetActorRotation();
	// DoorRotation.Yaw = CurrentYaw; // Assign the changing value of CurrentYaw to the DoorRotation.Yaw in order to rotate it. 
	// GetOwner()->SetActorRotation(DoorRotation);
	// -------------------

	// 4-35
	// -------------------
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed); // Just change the rateOpen in order to change the rate of door opening. 
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw; // Assign the changing value of CurrentYaw to the DoorRotation.Yaw in order to rotate it. 
	GetOwner()->SetActorRotation(DoorRotation);
	// -------------------
	
	// 4-52
	// -------------------
	OpenDoorSound = false; // Reset back the door opening check. 

	if (!AudioComponent) { return; }

	if (!CloseDoorSound) {
		AudioComponent->Play(); // To play the sound. 
		CloseDoorSound = true;
	}
	// -------------------
}

// 4-50
float UOpenDoor::TotalMassOfActors() const {
	float TotalMass = 0.0;

	// Find all overlapping actors. 
	TArray<AActor*> OverlappingActors; // To store things. Its a pointer to that actors.
	if (!PressurePlate) { return TotalMass; } // To prevent crashing. 
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	
	// Add up their Masses with for loop.
	for (AActor* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		// UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate!"), *Actor->GetName()); // To check what is on the pressure plate. 
	}

	return TotalMass;
}