#include <sound_player.h>
#include <lms/extra/time.h>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundSource.hpp>

bool SoundPlayer::initialize() {

    //Set values from config
    std::vector<std::string> soundList = config().getArray<std::string>("sounds");
    std::vector<std::string> soundListPaths = config().getArray<std::string>("soundPaths");
    sounds.resize(soundList.size());
    for(int i = 0; i < (int)soundList.size();i++){
        SoundBufferContainer &container = sounds[i];
        if(!container.buffer.loadFromFile(soundListPaths[i])){
            logger.error("initialize")<<"couldn't load file: "<< soundList[i];
            return false;
        }
        //set default values
        container.sound.setBuffer(container.buffer);
        container.sound.setVolume(100);
        container.sound.setLoop(true);
        container.name = soundList[i];
        container.sound.setPitch(1.0);
        //add it to the list
        //name is the name of the file
        logger.debug("initialize")<<"added sound: "<<soundList[i];
    }
    //get playList
    playList = readChannel<soundUtils::Sounds>("PLAYLIST");
    return true;
}

bool SoundPlayer::cycle() {
    for(SoundBufferContainer &res : sounds){
        bool used = false;
        for(const soundUtils::SoundFile &toPlay:*playList){
            if(toPlay.name == res.name){
                used = true;
                //set values
                res.sound.setVolume(toPlay.volume);
                res.sound.setLoop(true);
                res.sound.setPitch(1.0);
                //TODO not sure how to restart, pause, stop
                if(res.sound.getStatus() == sf::SoundSource::Status::Playing){
                }else if(res.sound.getStatus() == sf::SoundSource::Status::Stopped){
                    res.sound.play();
                }else if(res.sound.getStatus() == sf::SoundSource::Status::Paused){
                    res.sound.play();
                }
                logger.debug("cycle")<<"playing sound"<<toPlay.name;
            }
        }
        if(!used){
            res.sound.stop();
        }
    }
    return true;
}


bool SoundPlayer::deinitialize() {
    return true;
}
