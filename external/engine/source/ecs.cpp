#include "ECS.h"
#include "Engine.h"

#define RAD2DEG 180.0f / 3.14159265358979f
#define Metres2Pixels = 80.0f
#define Pixels2Metres = 1 / 80.0f

void System::Visual::Update(Registry& reg)
{
    for (std::size_t e = 1; e <= Engine::Get()->GetMaxEntity(); e++)
    {
        if (reg.regGraphics.count(e) && reg.regPhysics.count(e))
        {
            reg.regGraphics[e].Dst.x = Engine::Get()->Box2DSDL(reg.regPhysics[e].body->GetPosition()).x 
            - (reg.regGraphics[e].TextureDimensions.x / 2);
            reg.regGraphics[e].Dst.y = 
            (Engine::Get()->GetWindowSurface()->h - Engine::Get()->Box2DSDL(reg.regPhysics[e].body->GetPosition()).y) - 
            (reg.regGraphics[e].TextureDimensions.y / 2);
            reg.regGraphics[e].Dst.w = reg.regGraphics[e].TextureDimensions.x;
            reg.regGraphics[e].Dst.h = reg.regGraphics[e].TextureDimensions.y;
        }
    }
}

void System::Visual::Render(Registry& reg)
{
    for (std::size_t e = 1; e <= Engine::Get()->GetMaxEntity(); e++)
    {
        if(reg.regGraphics.count(e))
        {
            SDL_RenderCopy(Engine::Get()->GetRenderer(), GetTexturePtr(reg.regGraphics[e].TextureID),
            0, &reg.regGraphics[e].Dst);
        }   
    }
}

const std::size_t& System::Visual::LoadFromFile(const std::size_t& ID, const char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	if (!surface)
		std::cout << "[SDL2]: Image could not be loaded into surface!   : " << SDL_GetError() << std::endl;

	TextureMap[ID] = SDL_CreateTextureFromSurface(Engine::Get()->GetRenderer(), surface);
	if (!TextureMap[ID])
		std::cout << "[SDL2]: Surface could not be loaded into texture!   : " << SDL_GetError() << std::endl;

	SDL_FreeSurface(surface);
	return ID;
}

void System::Visual::RenderTexture(const std::size_t& ID, const SDL_Rect& pDst, const float& angle, SDL_Point* center,
	SDL_RendererFlip flip)
{
	SDL_Rect src = {};
	src.w;
	src.h;

	SDL_QueryTexture(TextureMap[ID], nullptr, nullptr, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = pDst.x;
	dst.y = pDst.y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopyEx(Engine::Get()->GetRenderer(), TextureMap[ID], &src, &dst, angle, center, flip);
}


void System::Visual::SetBlending(const std::size_t& ID, const SDL_BlendMode& blend)
{
	SDL_SetTextureBlendMode(TextureMap[ID], blend);
}
void System::Visual::SetAlpha(const std::size_t& ID, const Uint8& alpha)
{
	SDL_SetTextureAlphaMod(TextureMap[ID], alpha);
}
void System::Visual::Tint(const std::size_t& ID, const SDL_Color& tint)
{
	SDL_SetTextureColorMod(TextureMap[ID], tint.r, tint.g, tint.b);
}

void System::Visual::Drop(const std::size_t& ID)
{
	SDL_DestroyTexture(TextureMap[ID]);
	TextureMap.erase(ID);
}

System::Visual::~Visual()
{
	TextureMap.clear();
}

SDL_Texture* System::Visual::GetTexturePtr(const std::size_t& ID)
{
	return TextureMap[ID];
}

void System::Visual::RenderSprite(const std::size_t& ID, const int& spriteIndex, const b2Vec2& vec2, const double& angle, 
SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect RenderingSurface = {};
	RenderingSurface.x = vec2.x;
	RenderingSurface.y = vec2.y;

	SDL_Rect* Clip = &SpriteMap[ID][spriteIndex];

	if (Clip)
	{
		RenderingSurface.w = Clip->w;
		RenderingSurface.h = Clip->h;
	}
	SDL_RenderCopyEx(Engine::Get()->GetRenderer(), TextureMap[ID], Clip, &RenderingSurface, angle, center, flip);
}

void System::Visual::PlayAnimation(const std::size_t& ID, const SDL_Rect& dst, const int& frames, 
const int& delay, const double& angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Engine::Get()->GetRenderer(), TextureMap[ID], 
	&SpriteMap[ID][static_cast<int>((SDL_GetTicks64() / delay) % frames)], &dst, angle, center, flip);
}

std::size_t System::Visual::LoadSpriteSheetFromFile(const std::size_t ID, const std::string& filepath, const int& ClipNumber, const int& ClipHeight, const int& ClipWidth, 
	const int& ClipsInARow)
{
	LoadFromFile(ID, filepath.c_str());

	for(int i = 0; i < ClipNumber; i++)
	{
		SpriteMap[ID] = new SDL_Rect[ClipNumber];
	}

	if (TextureMap.count(ID))
	{
		for (int i = 0; i < ClipNumber; i++)
		{
			if (!(i >= ClipsInARow))
			{
				if (i == 0)
				{
					SpriteMap[ID][i].x = 0;
					SpriteMap[ID][i].y = 0;
				}
				else
				{
					SpriteMap[ID][i].x = ClipWidth * i;
					SpriteMap[ID][i].y = 0;
				}

				SpriteMap[ID][i].w = ClipWidth;
				SpriteMap[ID][i].h = ClipHeight;
			}

			else if (!(i > ClipsInARow * (i - ClipsInARow + 1)))
			{
				if (i == ClipsInARow)
				{
					SpriteMap[ID][i].x = 0;
					SpriteMap[ID][i].y = ClipHeight;
				}
				else
				{
					SpriteMap[ID][i].x = ClipWidth * (i - ClipsInARow);
					if (ClipsInARow == 1)
						SpriteMap[ID][i].x = 0;
					SpriteMap[ID][i].y = ClipHeight * (i - ClipsInARow);
					if (ClipsInARow == 1)
						SpriteMap[ID][i].y = i * ClipHeight;
				}

				SpriteMap[ID][i].w = ClipWidth;
				SpriteMap[ID][i].h = ClipHeight;
			}

			std::cout << "Clip Extracted" << std::endl;
			std::cout << SpriteMap[ID][i].x << " " << SpriteMap[ID][i].y << std::endl;
		}
	}

	return ID;
}

void System::Input::Listen(Registry& reg, const std::size_t& ID)
{
    if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_RIGHT))
        reg.regPlayer[ID].MoveState = PlayerMoveX::MOVE_RIGHT;
    else if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_LEFT))
        reg.regPlayer[ID].MoveState = PlayerMoveX::MOVE_LEFT;
    else if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_RIGHT) && Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_LEFT))
        reg.regPlayer[ID].MoveState = PlayerMoveX::STOP;
    else
        reg.regPlayer[ID].MoveState = PlayerMoveX::STOP;
    
    if (Engine::Get()->GetEventHandler()->IsKeyDown(SDL_SCANCODE_C))
    {   
        if (reg.regPlayer[ID].GroundContacts < 1)
        {
            if (reg.regPlayer[ID].DoubleJump != 0 && reg.regPlayer[ID].JumpTime.GetTicks() > 300)
            {
                reg.regPhysics[ID].body->ApplyLinearImpulse(b2Vec2(0, reg.regPlayer[ID].JumpTime.GetTicks() / 1000.0f), 
                reg.regPhysics[ID].body->GetWorldCenter(), 0);
        
                reg.regPlayer[ID].DoubleJump--;
                reg.regPlayer[ID].JumpTime.Start();
            }
            else
                return;
        }

        else
        {
            reg.regPlayer[ID].DoubleJump = 1;
            reg.regPlayer[ID].JumpTime.Start();
            reg.regPhysics[ID].body->ApplyLinearImpulse(b2Vec2(0, reg.regPhysics[ID].body->GetMass() / 9), reg.regPhysics[ID].body->GetWorldCenter(), 0);
        }      
    }
}

void System::Player::Update(const std::size_t& ID, Registry& reg, bool collision, b2World* world, DebugDrawSDL& debug)
{
    b2Vec2 Vel = reg.regPhysics[ID].body->GetLinearVelocity();
    float VelChangeX = reg.regPlayer[ID].MoveState * 0.44f - Vel.x;


        
            

    

    reg.regPhysics[ID].body->ApplyLinearImpulse(b2Vec2((VelChangeX * reg.regPhysics[ID].body->GetMass()), 0), 
    reg.regPhysics[ID].body->GetWorldCenter(), 0);
}

#pragma region PHYSICS
System::Physics::Physics(const float& timestepFixed, const float& gravity)
    : TimestepAccumulator(0), TimestepAccumulatorRatio(0), VelocityIterations(6), PositionIterations(2)
{
    FixedTimestep = timestepFixed;

    World = new b2World(b2Vec2(0, -gravity));
    World->SetAutoClearForces(0);
}

void System::Physics::Update(float& Dt, Registry& reg) //should refactor
{  
    if (Dt > 0.03f)
        Dt = 0.03f;
    
    TimestepAccumulator += Dt;
    while (TimestepAccumulator >= Dt)
    {    
        World->Step(Dt, VelocityIterations, PositionIterations);
        TimestepAccumulator -= Dt;
    }

    const double Alpha = TimestepAccumulator / Dt;
    Interpolate(reg, Alpha);
}

void System::Physics::Interpolate(Registry& reg, const double& alpha)
{
    
}

#pragma endregion PHYSICS

void Component::Physics::Actor::b2BodyToInterpolation(b2Body*& body)
{
    PreviousPosition = body->GetPosition();
}
