import QtQuick 2.0
import QtQuick.Controls 1.4

Item
{
  id: ordersView
  property alias ov_visible: ordersView.visible

  anchors.fill: parent

  Rectangle
  {
    id: topRect
    anchors {top: parent.top; left: parent.left; right: parent.right }
    height: 50
    color: "#d34d38"
    radius: 2

    Item
    {
      id: addItem
      anchors {top: parent.top; bottom: parent.bottom; right: parent.right }
      width: 50

      Rectangle
      {
        id: addRect
        anchors.fill: parent
        color: "#3e2323"
        opacity: 0.1
      }

      Image
      {
        id: addIcon
        anchors.centerIn: parent
        source: "../images/add.png"
        opacity: 0.5
      }

      MouseArea
      {
        id: addMouseA
        hoverEnabled: true
        anchors.fill: parent
      }

      states:
      [
        State
        {
          name: "hover"
          when: addMouseA.containsMouse
          PropertyChanges { target: addRect; opacity: 0.7 }
          PropertyChanges { target: addIcon; opacity: 0.7 }
        }
      ]
    }
  }

  Rectangle
  {
    id: statusRect
    anchors {bottom: parent.bottom; left: parent.left; right: parent.right }
    height: 50
    color: "#d34d38"
    radius: 2
  }

  Rectangle
  {
    id: ordersRect
    anchors { top: topRect.bottom; left: parent.left; right: parent.right; bottom: statusRect.top }
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
            width: parent.width

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

      rowDelegate: rowDelegate
      itemDelegate: itemDelegate

      TableViewColumn
      {
        role: "u_initials"
        title: "Who"
        resizable: true
        width: parent.width/3
        horizontalAlignment: Text.AlignHCenter
      }

      TableViewColumn
      {
        role: "menu_item"
        title: "What"
        resizable: true
        width: parent.width/3
        horizontalAlignment: Text.AlignHCenter
      }

      TableViewColumn
      {
        role: "price"
        title: "Price"
        resizable: true
        width: parent.width/3
        horizontalAlignment: Text.AlignHCenter
      }

      Component
      {
        id: itemDelegate

        Item
        {
          Text
          {
            id: itemText
            text: styleData.value
            anchors.centerIn: parent
            color:"white"
            font.family: "Verdana"; font.pixelSize: 12
            visible: !styleData.selected
          }

          Text
          {
            id: itemTextSel
            text: styleData.value
            anchors.centerIn: parent
            color:"white"
            font.family: "Verdana"; font.pixelSize: 14
            visible: styleData.selected
          }
        }
      }


      Component
      {
        id: rowDelegate
        Item
        {
          height: 40

          Rectangle
          {
            id: rowRect
            anchors.fill: parent
            color: "grey"
            radius: 2
            opacity: 0.4
            border.width: 0;
          }

          MouseArea
          {
            id: rowMouseA
            hoverEnabled: true
            anchors.fill: parent
          }

          states:
          [
            State
            {
              name: "hover"
              when: rowMouseA.containsMouse
              PropertyChanges { target: rowRect; border.width: 1; }
            }
          ]
        }
      }

      model: ordersModel
    }

    ListModel
    {
      id: ordersModel

      ListElement
      {
        u_initials: "JS"
        menu_item: "23"
        price: "13"
      }
      ListElement
      {
        u_initials: "TST1"
        menu_item: "21"
        price: "13"
      }
      ListElement
      {
        u_initials: "TST2"
        menu_item: "22"
        price: "13"
      }
    }
  }


}
