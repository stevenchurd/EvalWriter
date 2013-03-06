import QtQuick 2.0

Rectangle {
    id: sprite
    width: 100
    height: 62

    color: "red"
    Drag.active: true
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10
}
