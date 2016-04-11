import QtQuick 2.0

Item
{
  id: mainView
  anchors { top: parent.top; left: parent.left; bottom: parent.bottom; right: parent.right; margins: 3 }

  Rectangle
  {
    id: noneView
    anchors.fill: parent
    color: "#483c3c"
    radius: 2
  }
}
