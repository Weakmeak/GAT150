#include "ContactListener.h"
#include "Framework/Actor.h"
#include <iostream>
#include "Engine.h"

namespace digi {
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();


		if (fixtureA->GetUserData().pointer && fixtureA->GetUserData().pointer) {
			Actor* actA = (Actor*)fixtureA->GetUserData().pointer;
			Actor* actB = (Actor*)fixtureB->GetUserData().pointer;

			if (actA->isDestroyed() || actB->isDestroyed()) return;

			if (actA->GetComponent<CollisionComponent>()) {
				actA->GetComponent<CollisionComponent>()->OnCollisionEnter(actB);
			}
			if (actB->GetComponent<CollisionComponent>()) {
				actB->GetComponent<CollisionComponent>()->OnCollisionEnter(actA);
			}
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();


		if (fixtureA->GetUserData().pointer && fixtureA->GetUserData().pointer) {
			Actor* actA = (Actor*)fixtureA;
			Actor* actB = (Actor*)fixtureB;

			if (actA->isDestroyed() || actB->isDestroyed()) return;

			if (actA->GetComponent<CollisionComponent>()) {
				actA->GetComponent<CollisionComponent>()->OnCollisionExit(actB);
			}
			if (actB->GetComponent<CollisionComponent>()) {
				actB->GetComponent<CollisionComponent>()->OnCollisionExit(actA);
			}
		}
	}
}
