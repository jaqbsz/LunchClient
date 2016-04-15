import QtQuick 2.0

Item
{
  id: statsView
  property alias sv_visible: statsView.visible

  anchors.fill: parent

  Rectangle
  {
    id: statsRect
    anchors.fill: parent
    color: "purple"
    radius: 10
  }
}
