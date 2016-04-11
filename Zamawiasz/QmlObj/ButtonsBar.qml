import QtQuick 2.0

Item
{
  id: buttonsBar
  anchors { left: parent.left; top: parent.top; bottom: parent.bottom; margins: 3 }

  Rectangle
  {
    id: buttonsRect
    anchors.fill: parent
    color: "#483c3c"
    radius: 2
  }

  property alias bb_width: buttonsBar.width
}
