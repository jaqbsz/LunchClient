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

    Image
    {
      id: tbdIcon
      anchors.centerIn: parent
      width: 200
      height: 200
      source: "../images/under_construction.jpg"
      opacity: 0.5
    }

  }
}
