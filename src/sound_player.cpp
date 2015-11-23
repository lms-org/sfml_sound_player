#include <sound_player.h>
#include <lms/extra/time.h>
#include <SFML/Audio.hpp>
#include <lms/framework.h>
#include <SFML/Audio/SoundSource.hpp>

bool SoundPlayer::initialize() {
    //Set values from config
    std::vector<std::string> soundList = config().getArray<std::string>("sounds");
    for(int i = 0; i < (int)soundList.size();i++){
        SoundBufferContainer container;
        if(!container.buffer.loadFromFile(lms::Framework::configsDirectory + "/" +soundList[i])){
            logger.error("initialize")<<"couldn't load file: "<< soundList[i];
            return false;
        }
        //set default values
        container.sound.setBuffer(container.buffer);
        container.sound.setVolume(100);
        container.sound.setLoop(true);
        container.sound.setPitch(1.0);
        sounds.push_back(container);
    }
    //get playList
    playList = datamanager()->readChannel<soundUtils::Sounds>(this, "PLAYLIST");
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
