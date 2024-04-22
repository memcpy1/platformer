//STL
#include "Engine.h"
#include "Collision.h"

void CollisionListener::BeginContact(b2Contact* contact)
{
    UserData FixtureUserData = static_cast<UserData>(contact->GetFixtureA()->GetUserData());
    if (FixtureUserData.GroundCheck)
    {
        std::cout << "a" << '\n';
        Engine::Get()->GetRegistry()->regPlayer[FixtureUserData.ECS_ID].GroundContacts++;
        FixtureUnderPlayer.insert(contact->GetFixtureB());
    }

    FixtureUserData = static_cast<UserData>(contact->GetFixtureB()->GetUserData());
    if (FixtureUserData.GroundCheck)
    {
        Engine::Get()->GetRegistry()->regPlayer[FixtureUserData.ECS_ID].GroundContacts++;
        FixtureUnderPlayer.insert(contact->GetFixtureA());
    }
}

void CollisionListener::EndContact(b2Contact* contact)
{
    UserData FixtureUserData = static_cast<UserData>(contact->GetFixtureA()->GetUserData());
    if (FixtureUserData.GroundCheck)
    {
        Engine::Get()->GetRegistry()->regPlayer[FixtureUserData.ECS_ID].GroundContacts--;
        FixtureUnderPlayer.erase(contact->GetFixtureB());
    }

    FixtureUserData = static_cast<UserData>(contact->GetFixtureB()->GetUserData());
    if (FixtureUserData.GroundCheck)
    {
        Engine::Get()->GetRegistry()->regPlayer[FixtureUserData.ECS_ID].GroundContacts--;
        FixtureUnderPlayer.erase(contact->GetFixtureA());
    }
}