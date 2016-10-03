// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/PatrollingGuard.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get Patrol Points
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = AIOwner->GetPawn();
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	TArray<AActor*> PatrolPoint = PatrollingGuard->PatrolPointsCPP;

	// Set Next Waypoint
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName); // Finds name of index key in Behavior Tree
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoint[Index]);
	
	// Cycle The Index
	int32 NextIndex = (Index + 1) % PatrolPoint.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
