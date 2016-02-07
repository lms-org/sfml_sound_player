#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <lms/module.h>
#include <SFML/Audio.hpp>
#include "sound_player/sound_player_utils.h"

class SoundPlayer : public lms::Module {
public:
    bool initialize() override;
    bool cycle() override;
    bool deinitialize() override;
    struct SoundBufferContainer {
        sf::SoundBuffer buffer;
        sf::Sound sound;
        std::string name;
    };
private:
    std::vector<SoundBufferContainer> sounds;
    lms::ReadDataChannel<soundUtils::Sounds> playList;
};

#endif /* SOUND_PLAYER_H */
