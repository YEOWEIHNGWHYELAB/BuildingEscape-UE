// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h" // For the trigger volume. 
#include "OpenDoor.generated.h" // Must be at the bottom.


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPressurePlate();

	// To prevent the sound from continously playing non-stop! To track whether sound have been played once. 
	bool OpenDoorSound = false;
	bool CloseDoorSound = false;

private:
	// float TargetYaw = 90; // 4-21
	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.0;

	UPROPERTY(EditAnywhere) // So we can see TargetYaw in editor. 
	float OpenAngle = 90.0;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr; 

	UPROPERTY(EditAnywhere)
    AActor* ActorThatOpens;

	float DoorLastOpened = 0.0; // Please initialize this otherwise it will only be assigned when player enters the trigger volume. 
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 0.8;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.0;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
