import QtQuick 2.0

Item
{
  id: buttonsBar

  property alias bb_width: buttonsBar.width
  signal bb_buttPressed(string bu_name)

  anchors { left: parent.left; top: parent.top; bottom: parent.bottom; margins: 1 }

  function sendUnPressed()
  {
    var res = false

    if ( ordersButt.pressed ) res = true
    else if ( usersButt.pressed ) res = true
    else if ( statsButt.pressed ) res = true
    else if ( settingsButt.pressed ) res = true

    if ( !res ) buttonsBar.bb_buttPressed("None")
  }

  function makeButtonsWide()
  {
    ordersButt.bu_widthState = "wide"
    usersButt.bu_widthState = "wide"
    statsButt.bu_widthState = "wide"
    settingsButt.bu_widthState = "wide"
  }

  function makeButtonsNarrow()
  {
    ordersButt.bu_widthState = "narrow"
    usersButt.bu_widthState = "narrow"
    statsButt.bu_widthState = "narrow"
    settingsButt.bu_widthState = "narrow"
  }

  // TODO ugly fix, should be done with states of buttonsBar
  onBb_widthChanged:
      if (buttonsBar.width == 120)
        makeButtonsWide()
      else
        makeButtonsNarrow()

  Rectangle
  {
    id: buttonsRect
    anchors.fill: parent
    color: "#0073e6"

    ZButton
    {
      id: ordersButt
      anchors.top: parent.top
      bu_text: "Orders"
      bu_IconSource: "../images/orders.png"

      onBu_pressed:
        {
          usersButt.bu_unpressed()
          statsButt.bu_unpressed()
          settingsButt.bu_unpressed()
          buttonsBar.bb_buttPressed(bu_text)
        }
      onBu_unpressed: sendUnPressed()
    }

    ZButton
    {
      id: usersButt
      anchors.top: ordersButt.bottom
      bu_text: "Users"
      bu_IconSource: "../images/users.png"

      onBu_pressed:
        {
          ordersButt.bu_unpressed()
          statsButt.bu_unpressed()
          settingsButt.bu_unpressed()
          buttonsBar.bb_buttPressed(bu_text)
        }
      onBu_unpressed: sendUnPressed()
    }

    ZButton
    {
      id: statsButt
      anchors.top: usersButt.bottom
      bu_text: "Statistics"
      bu_IconSource: "../images/stats.png"

      onBu_pressed:
        {
          ordersButt.bu_unpressed()
          usersButt.bu_unpressed()
          settingsButt.bu_unpressed()
          buttonsBar.bb_buttPressed(bu_text)
        }
      onBu_unpressed: sendUnPressed()
    }

    ZButton
    {
      id: settingsButt
      anchors.bottom: parent.bottom
      bu_text: "Settings"
      bu_IconSource: "../images/settings.png"

//      onBu_stateChanged:
//          if (bu_state=="hover")
//            buttonsRect.state = "set_hover"
//          else
//            buttonsRect.state = "normal"

      onBu_pressed:
        {
          ordersButt.bu_unpressed()
          usersButt.bu_unpressed()
          statsButt.bu_unpressed()
          buttonsBar.bb_buttPressed(bu_text)
        }
      onBu_unpressed: sendUnPressed()
    }

//    states:
//    [
//      State
//      {
//        name: "set_hover"
//        PropertyChanges { target: settingsIcon; rotation: 360; }
//      }
//    ]

//    transitions:
//    [
//      Transition
//      {
//        to: "set_hover"
//        NumberAnimation { target: settingsIcon; property: "rotation"; duration: 1000  }
//      }
//    ]
  }
}
