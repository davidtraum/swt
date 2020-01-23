#include "mousedecor.h"

MouseDecor::MouseDecor()
{

}

/**
 * @brief MouseDecor::setType Setzt den Decor-Typ.
 */
void MouseDecor::setType(MouseDecor::TYPE pType)
{
    type = pType;
}

/**
 * @brief MouseDecor::setValue Setzt den Wert.
 * @param pValue Der neue Wert.
 */
void MouseDecor::setValue(int pValue ){
    value = pValue;
}

/**
 * @brief MouseDecor::getValue Gibt den aktuellen Wert.
 * @return Gibt den aktuellen Wert.
 */
int MouseDecor::getValue(){
    return value;
}


/**
 * @brief MouseDecor::getType Gibt den Decor-Typ zurück.
 * @return Der Typ.
 */
MouseDecor::TYPE MouseDecor::getType(){
    return type;
}
