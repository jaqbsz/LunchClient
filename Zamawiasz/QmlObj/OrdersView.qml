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
        onClicked:
        {
          whoInput.text = ""
          whatInput.text = ""
          priceInput.text = ""

          if ( fillRect.state == "active" )
            fillRect.state = "normal"
          else if ( fillRect.state == "normal" )
            fillRect.state = "active"
        }
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
      enabled: true

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
            font.family: "Verdana"; font.pixelSize: 12
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
            onDoubleClicked:
            {
              if ( fillRect.state == "normal" )
              {
                whoInput.text = ordersModel.get(styleData.row).u_initials
                whatInput.text = ordersModel.get(styleData.row).menu_item
                priceInput.text = ordersModel.get(styleData.row).price
                fillRect.state = "active"
              }
            }
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

  Rectangle
  {
    id: fillRect
    anchors { top: ordersRect.top; right: ordersRect.right; bottom: ordersRect.bottom; topMargin: 5; bottomMargin: 5 }
    color: "#4aad7a"
    radius: 2
    width: 0
    opacity: 0
    state: "normal"


    Column
    {
      spacing: 20
      anchors.fill: parent
      anchors.margins: 50

      Column
      {
        spacing: 2

        Text
        {
          text: "Who"
          color:"white"
          font.family: "Verdana"; font.pixelSize: 12
        }

        Rectangle
        {
          width: 200 ; height: 30
          border.width: 1
          border.color: "#4b4b4b"
          color: "lightsteelblue"
          radius: 2

          TextInput
          {
            id: whoInput
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 12; }
          }
        }
      }

      Column
      {
        spacing: 2

        Text
        {
          text: "What"
          color:"white"
          font.family: "Verdana"; font.pixelSize: 12
        }

        Rectangle
        {
          width: 200 ; height: 30
          border.width: 1
          border.color: "#4b4b4b"
          color: "lightsteelblue"
          radius: 2

          TextInput
          {
            id: whatInput
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 12; }
          }
        }
      }

      Column
      {
        spacing: 2

        Text
        {
          text: "Price"
          color:"white"
          font.family: "Verdana"; font.pixelSize: 12
        }

        Rectangle
        {
          width: 200 ; height: 30
          border.width: 1
          border.color: "#4b4b4b"
          color: "lightsteelblue"
          radius: 2

          TextInput
          {
            id: priceInput
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 12; }
          }
        }
      }

      Row
      {
        spacing: 30

        Button
        {
          text: "Ok"
        }

        Button
        {
          text: "Cancel"
          onClicked:
          {
            whoInput.text = ""
            whatInput.text = ""
            priceInput.text = ""
            fillRect.state = "normal"
          }
        }
      }
    }

    states:
    [
      State
      {
        name: "normal"
        PropertyChanges { target: fillRect; width: 0; opacity: 0 }
        PropertyChanges { target: ordersTable; enabled: true }
      },
      State
      {
        name: "active"
        PropertyChanges { target: fillRect; width: ordersRect.width * 0.8; opacity: 1 }
        PropertyChanges { target: ordersTable; enabled: false }
      }
    ]

    transitions:
    [
      Transition
      {
        NumberAnimation { target: fillRect; property: "width"; duration: 100  }
        NumberAnimation { target: fillRect; property: "opacity"; duration: 200  }
      }
    ]
  }
}
