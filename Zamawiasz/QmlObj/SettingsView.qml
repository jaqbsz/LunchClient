import QtQuick 2.0

Item
{
  id: settingsView
  property alias sev_visible: settingsView.visible
  property string hostname: "127.0.0.1"
  property int portnr: 9876

  anchors.fill: parent

  Rectangle
  {
    id: settingsRect
    anchors.fill: parent
    color: "#87CEFA"

    Column
    {
      spacing: 15
      anchors.fill: parent
      anchors.margins: 30

      Column
      {
        spacing: 2

        Text
        {
          text: "IP Address"
          color:"white"
          font.family: "Verdana"; font.pixelSize: 10
        }

        Rectangle
        {
          width: 150 ; height: 25
          border.width: 1
          border.color: "#4b4b4b"
          color: "lightsteelblue"
          radius: 2

          TextInput
          {
            id: ipaddrInput
            text: settingsView.hostname
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 10; }
            selectByMouse: true
            KeyNavigation.tab: ipportInput
            onAccepted: { ipaddrInput.focus = false; ipportInput.focus = true; settingsView.hostname = ipaddrInput.text }
          }
        }
      }

      Column
      {
        spacing: 2

        Text
        {
          text: "IP Port"
          color:"white"
          font.family: "Verdana"; font.pixelSize: 10
        }

        Rectangle
        {
          width: 150 ; height: 25
          border.width: 1
          border.color: "#4b4b4b"
          color: "lightsteelblue"
          radius: 2

          TextInput
          {
            id: ipportInput
            text: settingsView.portnr
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 10; }
            selectByMouse: true
            KeyNavigation.tab: ipaddrInput
            onAccepted: { ipportInput.focus = false; settingsView.portnr = ipportInput.text }
          }
        }
      }
    }
  }
}
