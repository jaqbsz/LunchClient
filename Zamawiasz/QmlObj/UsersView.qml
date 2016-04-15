import QtQuick 2.0

Item
{
  id: usersView
  property alias uv_visible: usersView.visible

  anchors.fill: parent

  Rectangle
  {
    id: usersRect
    anchors.fill: parent
    color: "green"
    radius: 10
  }
}
