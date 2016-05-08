import QtQuick 2.0


Item
{
  id: buttonItem

  /// aliases
  // label of the button
  property alias bu_text: buttonText.text

  /// custom properties
  // button pressed signal
  signal bu_pressed()

  // button unpressed signal
  signal bu_unpressed()

  // holds information wheter the button is pressed
  property bool pressed

  // holds information about current state of the button
  // possible values: "normal", "hover", "pressed"
  property string bu_state

  // holds buttons icon source
  property string bu_IconSource

  //
  property string bu_widthState

  // style object
  property var bStyle:
  {
    'bColor_hover': "#1a8cff",
    'bColor_pressed': "#004d99",
    'bColor_normal': "#0073e6"
  }
  // -----

  anchors { left: parent.left; right: parent.right }
  height: 40

  onBu_unpressed: state = "normal"
  bu_state: buttonItem.state

  onBu_widthStateChanged: buttonRect.state = bu_widthState

  states:
  [
    State
    {
      name: "hover"
      PropertyChanges { target: buttonRect; color: bStyle.bColor_hover }
      PropertyChanges { target: buttonItem; bu_state: "hover" }
    },
    State
    {
      name: "pressed"
      PropertyChanges { target: buttonItem; pressed: true; bu_state: "pressed" }
      PropertyChanges { target: buttonRect; color: bStyle.bColor_pressed }
    },
    State
    {
      name: "normal"
      PropertyChanges { target: buttonItem; pressed: false; bu_state: "normal" }
      PropertyChanges { target: buttonRect; color: bStyle.bColor_normal }
    }
  ]

  Rectangle
  {
    id: buttonRect
    anchors.fill: parent
    color: bStyle.bColor_normal
    state: "narrow"

    Text
    {
      id: buttonText
      text: "Button"
      font.family: "Verdana"
      color: "white"
      font.pixelSize: 12
      anchors { verticalCenter: parent.verticalCenter; left: buttonIcon.right; leftMargin: 10 }
    }

    Image
    {
      id: buttonIcon
      width: 25
      height: 25
      anchors { verticalCenter: buttonRect.verticalCenter; leftMargin: 10 }
      source: buttonItem.bu_IconSource
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

    states:
    [
      State
      {
        name: "narrow"
        PropertyChanges {target: buttonIcon }
        AnchorChanges   {target: buttonIcon; anchors { horizontalCenter: buttonRect.horizontalCenter } }
        PropertyChanges {target: buttonText; visible: false}
      },
      State
      {
        name: "wide"
        PropertyChanges {target: buttonIcon }
        AnchorChanges   {target: buttonIcon; anchors { left: buttonRect.left; } }
        PropertyChanges {target: buttonText; visible: true}
      }
    ]
  }
}
