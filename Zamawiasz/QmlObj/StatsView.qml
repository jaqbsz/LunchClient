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
    color: "#4169E1"

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
