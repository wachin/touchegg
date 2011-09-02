/**
 * @file /src/touchegg/gestures/factory/GestureFactory.cpp
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011
 * @class  GestureFactory
 */
#include "GestureFactory.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

GestureFactory* GestureFactory::instance = NULL;

GestureFactory* GestureFactory::getInstance()
{
    if(GestureFactory::instance == NULL)
        GestureFactory::instance = new GestureFactory();

    return GestureFactory::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

Gesture* GestureFactory::createSimpleGesture(GeisGestureType type,
        GeisGestureId id, QHash<QString, QVariant> attrs)
{
    int numFingers = attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();

    // TAP
    if(type == GEIS_GESTURE_PRIMITIVE_TAP) {
        return new Gesture(GestureTypeEnum::TAP, numFingers,
                GestureDirectionEnum::NO_DIRECTION, id, attrs);

    // DRAG
    } else if(type == GEIS_GESTURE_PRIMITIVE_DRAG) {
        // UP
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::UP, id, attrs);

        // DOWN
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::DOWN, id, attrs);

        // LEFT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::LEFT, id, attrs);

        // RIGHT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::DRAG, numFingers,
                    GestureDirectionEnum::RIGHT, id, attrs);

    // PINCH
    } else if(type == GEIS_GESTURE_PRIMITIVE_PINCH) {
        // IN
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_RADIUS_DELTA).toFloat() < 0)
            return new Gesture(GestureTypeEnum::PINCH, numFingers,
                    GestureDirectionEnum::IN, id, attrs);

        // OUT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_RADIUS_DELTA).toFloat() > 0)
            return new Gesture(GestureTypeEnum::PINCH, numFingers,
                    GestureDirectionEnum::OUT, id, attrs);

    // ROTATE
    } else if(type == GEIS_GESTURE_PRIMITIVE_ROTATE) {
        // LEFT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_ANGLE_DELTA).toFloat() < 0)
            return new Gesture(GestureTypeEnum::ROTATE, numFingers,
                    GestureDirectionEnum::LEFT, id, attrs);

        // RIGHT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_ANGLE_DELTA).toFloat() > 0)
            return new Gesture(GestureTypeEnum::ROTATE, numFingers,
                    GestureDirectionEnum::RIGHT, id, attrs);

    // UNKNOWN GESTURE
    } else {
        qDebug() << "[+] Unknown gesture:";
        qDebug() << "\tName -> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
        qDebug() << "\tNumber of fingers-> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();
    }

    return NULL;
}

Gesture* GestureFactory::createComposedGesture(GeisGestureType type,
        GeisGestureId id, QHash<QString, QVariant> attrs)
{
    int numFingers = attrs.value(GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();

    // TAP & HOLD
    if(type == GEIS_GESTURE_PRIMITIVE_DRAG) {

        // UP
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() < 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::UP, id, attrs);

        // DOWN
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() == 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() > 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::DOWN, id, attrs);

        // LEFT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() < 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::LEFT, id, attrs);

        // RIGHT
        if(attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_X).toFloat() > 0
                && attrs.value(GEIS_GESTURE_ATTRIBUTE_DELTA_Y).toFloat() == 0)
            return new Gesture(GestureTypeEnum::TAP_AND_HOLD, numFingers,
                    GestureDirectionEnum::RIGHT, id, attrs);

    // DOUBLE TAP
    } else if(type == GEIS_GESTURE_PRIMITIVE_TAP) {
        return new Gesture(GestureTypeEnum::DOUBLE_TAP, numFingers,
                GestureDirectionEnum::NO_DIRECTION, id, attrs);

    // UNKNOWN GESTURE
    } else {
        qDebug() << "[+] Unknown gesture:";
        qDebug() << "\tName -> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_GESTURE_NAME).toString();
        qDebug() << "\tNumber of fingers-> " << attrs.value(
                GEIS_GESTURE_ATTRIBUTE_TOUCHES).toInt();
    }

    return NULL;
}