#include <sound_player.h>

extern "C" {
void* getInstance () {
    return new SoundPlayer();
}
}
