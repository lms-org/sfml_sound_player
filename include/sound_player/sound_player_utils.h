#ifndef SOUND_PLAYER_UTILS_H
#define SOUND_PLAYER_UTILS_H
#include <cstring>
#include <vector>
namespace soundUtils{
    struct SoundFile{
        std::string name;
        float volume;
        float pitch;
        bool loop;
    };

    typedef std::vector<SoundFile> Sounds;
}

#endif // SOUND_PLAYER_UTILS_H
