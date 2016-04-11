import QtQuick 2.0

Item
{
  id: topBar
  anchors { top: parent.top; left: parent.left; right: parent.right; margins: 3 }

  Rectangle
  {
    id: barRect
    anchors.fill: parent
    color: "#483c3c"
    height: parent.height
    radius: 2
  }

  property alias tb_height: topBar.height
}

