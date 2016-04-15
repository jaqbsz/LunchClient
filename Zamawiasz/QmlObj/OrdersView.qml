import QtQuick 2.0
import QtQuick.Controls 1.4

Item
{
  id: ordersView
  property alias ov_visible: ordersView.visible

  anchors.fill: parent

  Rectangle
  {
    id: ordersRect
    anchors.fill: parent
    color: "#b55454"
    radius: 2

    TableView
    {
      id: ordersTable
      frameVisible: false
      anchors.fill: parent
      backgroundVisible: false
      alternatingRowColors: false

      headerDelegate:
          Item
          {
            height: 40

            Rectangle
            {
              anchors.fill: parent
              color: "grey"
              radius: 2
              opacity: 0.3
            }

            Text
            {
              text: styleData.value
              anchors.centerIn: parent
              color:"white"
              font.family: "Verdana"; font.pixelSize: 12
            }
          }

      TableViewColumn
      {
        role: "title"
        title: "Title"
        resizable: false
        width: parent.width/2
      }

      TableViewColumn
      {
        role: "author"
        title: "Author"
        resizable: false
        width: parent.width/2
      }

      model: ordersModel
    }

    ListModel
    {
      id: ordersModel

      ListElement
      {
        title: "A Masterpiece"
        author: "Gabriel"
      }
      ListElement
      {
        title: "Brilliance"
        author: "Jens"
      }
      ListElement
      {
        title: "Outstanding"
        author: "Frederik"
      }
    }
  }
}
