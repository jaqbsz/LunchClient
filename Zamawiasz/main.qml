import QtQuick 2.4
import QtQuick.Window 2.2
  import QtQuick.Controls 1.4

import "QmlObj"

Window
{
    id: mainWindow
    visible: true

    minimumHeight: 500
    minimumWidth: 500

    function signalConnected(state)
    {
      console.log("Connected - "+state)
      topBar.tb_connected(state)
    }

    Rectangle
    {
      id: mainRect
      color: "grey"
      anchors.fill: parent
    }

    TopBar
    {
      id: topBar
      objectName: "topBar"
      tb_height: 60
    }

    ButtonsBar
    {
      id: buttonsBar
      bb_width: 60
      anchors.top: topBar.bottom

      onBb_buttPressed:
        {
          console.log(bu_name)
          mainView.mv_changed(bu_name)
        }

    }

    MainView
    {
      id: mainView
      anchors.top: topBar.bottom
      anchors.left: buttonsBar.right
    }

}
