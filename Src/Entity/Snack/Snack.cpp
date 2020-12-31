#include "Snack.h"
#include "../../States/GameState/GameState.h"

Snack::Snack(SnackType type, sf::Vector2i gridPos, GameState* gameState)
    : Entity(gameState, Entities::NotDefined)
{
	animator = new Animator(&body);

    snackType = type;
    if (type == SmallSnack)
    {
        body = sf::RectangleShape(sf::Vector2f(gameState->tileWidth, gameState->tileHeight));
        texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(226, 240, 7, 7));
    }
    else
    {
        body = sf::RectangleShape(sf::Vector2f(gameState->tileWidth, gameState->tileHeight));
        texture.loadFromFile("Resources/PacManSprites.png", sf::IntRect(233, 240, 8, 8));
        SetupAnimation();
        animator->SetAnimationClip(bigSnackFlickerAnimation);
    }
    this->gridPos = gridPos;
    body.setTexture(&texture);
    body.move(sf::Vector2f(gameState->tileWidth * gridPos.x, gameState->tileHeight * gridPos.y));
}

void Snack::Update(const float& deltaTime)
{
    if(snackType == BigSnack)
        animator->Update(deltaTime);
}

void Snack::Draw(sf::RenderWindow& rw)
{
    rw.draw(body);
}

void Snack::SetupAnimation()
{
	sf::Texture spriteOn, spriteOff;
    spriteOn.loadFromFile("Resources/PacManSprites.png", sf::IntRect(233, 240, 8, 8));
    spriteOff.loadFromFile("Resources/PacManSprites.png", sf::IntRect(230, 160, 8, 8));
    std::vector<sf::Texture> leftAnimTextures{ spriteOff, spriteOn };


	bigSnackFlickerAnimation = new Animation(leftAnimTextures, true, 0.2f);
}