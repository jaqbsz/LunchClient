import QtQuick 2.0

Item
{
  id: ordersView
  property alias ov_visible: ordersView.visible

  anchors.fill: parent

  Rectangle
  {
    id: ordersRect
    anchors.fill: parent
    color: "blue"
    radius: 10
  }
}
