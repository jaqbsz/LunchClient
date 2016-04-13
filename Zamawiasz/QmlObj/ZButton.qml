import QtQuick 2.0

Item
{
  id: buttonItem

  property alias bu_text: buttonText.text
  property alias bu_color: buttonRect.color
  signal bu_pressed()
  signal bu_unpressed()

  anchors { left: parent.left; right: parent.right }
  height: 60

  onBu_unpressed: state = "normal"

  states:
  [
    State
    {
      name: "hover"
      PropertyChanges { target: buttonRect; color: "#503a5a" }
    },
    State
    {
      name: "pressed"
      PropertyChanges { target: buttonRect; color: "#503a5a"; border.color: "#503a5a" }
    },
    State
    {
      name: "normal"
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

    state: "normal"

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
          {
            buttonItem.bu_pressed();
            buttonItem.state != "pressed" ? buttonItem.state = "pressed" : buttonItem.state = "normal"
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
