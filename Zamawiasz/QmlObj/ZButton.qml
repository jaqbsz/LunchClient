import QtQuick 2.0

Item
{
  id: buttonItem

  property alias bu_text: buttonText.text
  property alias bu_color: buttonRect.color
  signal bu_pressed()
  signal bu_unpressed()
  property bool pressed
  property string bu_state

  anchors { left: parent.left; right: parent.right }
  height: 60

  onBu_unpressed: state = "normal"
  bu_state: buttonItem.state

  states:
  [
    State
    {
      name: "hover"
      PropertyChanges { target: buttonRect; color: "#503a5a" }
      PropertyChanges { target: buttonItem; bu_state: "hover" }
    },
    State
    {
      name: "pressed"
      PropertyChanges { target: buttonItem; pressed: true; bu_state: "pressed" }
      PropertyChanges { target: buttonRect; color: "#503a5a"; radius: 10 }
    },
    State
    {
      name: "normal"
      PropertyChanges { target: buttonItem; pressed: false; bu_state: "normal" }
      PropertyChanges { target: buttonRect; color: "#755a5a" }
    }
  ]

  Rectangle
  {
    id: buttonRect
    anchors.fill: parent
    color: "#755a5a"
    radius: 2
    border.width: 1
    border.color: "#d5bdbd"

    Text
    {
      id: buttonText
      text: "Button"
      font.family: "Verdana"
      color: "white"
      font.pixelSize: 12
      anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 5 }
    }

    MouseArea
    {
        id: buttonMA
        anchors.fill: parent
        hoverEnabled: true
        onClicked:
          if (buttonItem.state != "pressed")
          {
            buttonItem.state = "pressed"
            buttonItem.bu_pressed()
          }
          else
          {
            buttonItem.state = "normal"
            buttonItem.bu_unpressed()
          }
      onHoveredChanged:
          if ( buttonItem.state != "pressed" )
          {
            if ( buttonMA.containsMouse )
            {
              buttonItem.state = "hover"
            }
            else
            {
              buttonItem.state = "normal"
            }
          }
    }
  }
}
