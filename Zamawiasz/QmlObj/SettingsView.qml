import QtQuick 2.0

Item
{
  id: settingsView
  property alias sev_visible: settingsView.visible

  anchors.fill: parent

  Rectangle
  {
    id: settingsRect
    anchors.fill: parent
    color: "yellow"
    radius: 10
  }
}
