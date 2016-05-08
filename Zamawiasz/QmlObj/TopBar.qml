import QtQuick 2.0

Item
{
  id: topBar

  signal tb_connect()
  signal tb_disconnect()
  signal tb_connected(bool state)

  property alias tb_height: topBar.height

  anchors { top: parent.top; left: parent.left; right: parent.right; margins: 1 }

  onTb_connected:
  {
    if ( state )
      connectedItem.state = "connected"
    else
      connectedItem.state = "notconnected"
  }

  Rectangle
  {
    id: barRect
    anchors.fill: parent
    color: "#0073e6"
    height: parent.height

    Text
    {
      id: appNameText
      text: "Zamawiasz"; color: "white"
      anchors { left: parent.left; leftMargin: 50; verticalCenter: parent.verticalCenter }
      font.family: "Verdana"; font.pixelSize: 26
    }

    Image
    {
      id: logoIcon
      visible: true
      width: 30
      height: 30
      anchors.verticalCenter: parent.verticalCenter;
      anchors { right: appNameText.left }
      source: "../images/logo.png"
    }

    Item
    {
      id: connectedItem

      anchors {top: parent.top; bottom: parent.bottom; right: parent.right }
      width: 15

      state: "notconnected"

      states:
      [
        State
        {
          name: "connected"
          PropertyChanges { target: connectedRect; color: "green" }
          PropertyChanges { target: connectedText; text: "Connected" }
        },
        State
        {
          name: "notconnected"
          PropertyChanges { target: connectedRect; color: "#af0a0a" }
          PropertyChanges { target: connectedText; text: "Not connected" }
        }
      ]

      Rectangle
      {
        id: connectedRect
        color: "#af0a0a"
        anchors.fill: parent

        Text
        {
          id: connectedText
          text: "Not connected"; color: "white"
          anchors { left: parent.left; top: parent.top; margins: 5 }
          font.family: "Arial"; font.pixelSize: 10
          visible: false
        }

        MouseArea
        {
          id: connectedMA
          anchors.fill: parent
          hoverEnabled: true
          onClicked:
          {
            if ( connectedItem.state == "connected" )
              topBar.tb_disconnect()
            else if ( connectedItem.state == "notconnected" )
              topBar.tb_connect()
          }
        }

        states:
        [
          State
          {
            name: "hover"
            when: connectedMA.containsMouse
            PropertyChanges { target: connectedItem; width: connectedText.width+connectedText.anchors.margins+5 }
            PropertyChanges { target: connectedText; visible: true }
          }
        ]

        transitions:
        [
          Transition
          {
            NumberAnimation { target: connectedItem; property: "width"; duration: 200  }
          }
        ]
      }
    }
  }
}

