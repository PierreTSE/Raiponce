#include "globalClock.hpp"
#include<algorithm>


sf::Time globalClock::restart() noexcept {
    sf::Time elapsed = clock.restart();

    if (running) {
        frame = elapsed * (float) factor;
        global += frame;
        for (auto&[time, fun] : callbacks) {
            time -= frame;
            if (time < sf::Time::Zero)
                fun();
        }
        callbacks.erase(std::remove_if(callbacks.begin(),
                                       callbacks.end(),
                                       [](auto const& p) { return p.first < sf::Time::Zero; }),
                        callbacks.end());
    } else {
        frame = sf::Time::Zero;
    }

    return frameTime();
}

sf::Time globalClock::frameTime() const noexcept {
    return frame;
}

void globalClock::stop() noexcept {
    running = false;
}

void globalClock::start() noexcept {
    running = true;
}

void globalClock::changeSpeed(double speed) noexcept {
    factor = speed;
}

sf::Time globalClock::timeSinceStartup() const noexcept {
    return global;
}

globalClock& globalClock::getClock() {
    static globalClock instance;
    return instance;
}

void globalClock::executeIn(sf::Time delay, std::function<void()> fun) {
    callbacks.emplace_back(delay, std::move(fun));
}
