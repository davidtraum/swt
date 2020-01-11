#include "animationmanager.h"

/**
 * @brief AnimationManager::AnimationManager Erzeugt einen leeren Animation Manager.
 */
AnimationManager::AnimationManager()
{

}


/**
 * @brief AnimationManager::tick Führt alle Animationen aus.
 */
void AnimationManager::tick() {
}

/**
 * @brief AnimationManager::animateMovement Startet eine Bewegungsanimation.
 * @param pItem Ein Pixmap-Item.
 * @param pData Ein Pfad als String. Siehe AnimationMovement.
 */
void AnimationManager::animateMovement(QGraphicsPixmapItem * pItem, QString pData) {
    AnimationMovement * anim = new AnimationMovement(pItem);
    anim->parsePath(pData);
    movementAnimations.push_back(anim);
}



