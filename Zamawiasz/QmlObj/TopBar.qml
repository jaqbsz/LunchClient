import QtQuick 2.0

Item
{
  id: topBar

  property alias tb_height: topBar.height

  anchors { top: parent.top; left: parent.left; right: parent.right; margins: 3 }

  Rectangle
  {
    id: barRect
    anchors.fill: parent
    color: "#483c3c"
    height: parent.height
    radius: 2

    Text
    {
      text: "Zamawiasz"; color: "white"
      anchors { left: parent.left; margins: 30; verticalCenter: parent.verticalCenter }
      font.family: "Verdana"; font.pixelSize: 26
    }

//    Image
//    {
//      source: "../images/notconnected.png"
//      width: 15
//      height: 15
//      anchors { right: parent.right; margins: 10; top: parent.top }
//    }
  }
}

