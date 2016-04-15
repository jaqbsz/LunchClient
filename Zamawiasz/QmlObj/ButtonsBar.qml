import QtQuick 2.0

Item
{
  id: buttonsBar

  property alias bb_width: buttonsBar.width
  signal bb_buttPressed(string bu_name)

  anchors { left: parent.left; top: parent.top; bottom: parent.bottom; margins: 3 }

  function sendUnPressed()
  {
    var res = false

    if ( ordersButt.pressed ) res = true
    else if ( usersButt.pressed ) res = true
    else if ( statsButt.pressed ) res = true
    else if ( settingsButt.pressed ) res = true

    if ( !res ) buttonsBar.bb_buttPressed("None")
  }

  Rectangle
  {
    id: buttonsRect
    anchors.fill: parent
    color: "#483c3c"
    radius: 2

    ZButton
    {
      id: ordersButt
      anchors.top: parent.top
      bu_text: "Orders"
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
      anchors.topMargin: -1
      bu_text: "Users"
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
      anchors.topMargin: -1
      bu_text: "Statistics"
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
      onBu_pressed:
        {
          ordersButt.bu_unpressed()
          usersButt.bu_unpressed()
          statsButt.bu_unpressed()
          buttonsBar.bb_buttPressed(bu_text)
        }
      onBu_unpressed: sendUnPressed()
    }
  }
}
