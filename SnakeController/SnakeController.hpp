#pragma once

#include <list>
#include <memory>
#include <stdexcept>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;

namespace Snake
{
struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    struct Segment
    {
        int x;
        int y;
        int ttl;
    };

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;

    Direction m_currentDirection;
    std::list<Segment> m_segments;

    void HandleToEatFood();
    void set_direction(const Direction &direction);
    void FoodRespPosition(const FoodResp &requestedFood);
    void CheckSnakeEatsFood(const FoodInd &receivedFood);
    void MoveSnake();
    void placeNewHead(const Segment& newHead);
    void GenerateNewHead(const Segment &currentHead, Segment& newHead);
    void ConfigurationGame(std::string const& p_config);
    void ChooseDirection(char &d);
    bool CollisionWithMyself(const Segment &newhead);
    bool ControllWhereWeAre(const Segment& newHead);
    bool CheckHitFood(const Segment& newHead);
    bool CheckWeHitCornerOfMap(const Segment& newHead);
};

} // namespace Snake
