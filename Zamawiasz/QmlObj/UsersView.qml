import QtQuick 2.0
import QtQuick.Controls 1.4

Item
{
  id: usersView
  property alias uv_visible: usersView.visible

  anchors.fill: parent

  onUv_visibleChanged:
      if ( usersView.visible == true )
      {
        usersModel.listUsers();
      }

  Rectangle
  {
    id: topRect
    anchors {top: parent.top; left: parent.left; right: parent.right }
    height: 50
    color: "#d38337"
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
          fnameInput.text = ""
          lnameInput.text = ""
          initialsInput.text = ""

          usersTable.selectedrow = -1

          if ( fillRect.state == "active" )
          {
            console.log("Hide config window");
            usersTable.addnewitem = false
            fillRect.state = "normal"
          }
          else if ( fillRect.state == "normal" )
          {
            console.log("Add new item");
            usersTable.addnewitem = true
            fillRect.state = "active"
          }
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
    color: "#d38337"
    radius: 2
  }

  Rectangle
  {
    id: usersRect
    anchors { top: topRect.bottom; left: parent.left; right: parent.right; bottom: statusRect.top }
    color: "#d38337"
    radius: 2

    TableView
    {
      id: usersTable
      frameVisible: false
      anchors.fill: parent
      backgroundVisible: false
      alternatingRowColors: false
      enabled: true

      property bool addnewitem: false
      property int selectedrow: -1

      headerDelegate:
          Item
          {
            height: 40
            width: parent.width

            Rectangle
            {
              anchors.fill: parent
              color: "#e2750f"
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
        id: u_idCol
        role: "u_id"
        title: "Id"
        resizable: false
        width: 20
        horizontalAlignment: Text.AlignHCenter
      }

      TableViewColumn
      {
        role: "f_name"
        title: "First name"
        resizable: true
        width: (parent.width-u_idCol.width)/3
        horizontalAlignment: Text.AlignHCenter
      }

      TableViewColumn
      {
        role: "l_name"
        title: "Last name"
        resizable: true
        width: (parent.width-u_idCol.width)/3
        horizontalAlignment: Text.AlignHCenter
      }

      TableViewColumn
      {
        role: "initials"
        title: "Initials"
        resizable: true
        width: (parent.width-u_idCol.width)/3
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
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onDoubleClicked:
            {
              if ( fillRect.state == "normal" )
              {
                fnameInput.text = usersModel.getFname(styleData.row)
                lnameInput.text = usersModel.getLname(styleData.row)
                initialsInput.text = usersModel.getInitials(styleData.row)
                usersTable.addnewitem = false
                usersTable.selectedrow = styleData.row
                fillRect.state = "active"
              }
            }

            /// onClicked does not allow to check for pressedButtons
            /// http://stackoverflow.com/questions/22443641/qml-right-click-not-detected-in-mousearea
            onPressed:
                if(pressedButtons & Qt.RightButton)
                {
                  /// TODO add menu popup!!!
                  console.log("Delete user: " + styleData.row )
                  usersModel.deleteUser(styleData.row)
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

      model: usersModel
    }
  }

  Rectangle
  {
    id: fillRect
    anchors { top: usersRect.top; right: usersRect.right; bottom: usersRect.bottom; topMargin: 5; bottomMargin: 5 }
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
          text: "First name"
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
            id: fnameInput
            focus: true
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 12; }
            KeyNavigation.tab: lnameInput
          }
        }
      }

      Column
      {
        spacing: 2

        Text
        {
          text: "Last name"
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
            id: lnameInput
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 12; }
            KeyNavigation.tab: initialsInput
          }
        }
      }

      Column
      {
        spacing: 2

        Text
        {
          text: "Initials"
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
            id: initialsInput
            anchors.fill: parent
            anchors.leftMargin: 10
            verticalAlignment: TextInput.AlignVCenter
            color:"black"
            font { family: "Arial"; pixelSize: 12; }
            KeyNavigation.tab: buttOK
          }
        }
      }

      Row
      {
        spacing: 30

        Button
        {
          id: buttOK
          text: "Ok"
          onClicked:
          {
            console.log("Item ... ")

            if (usersTable.addnewitem)
            {
              console.log("add")
              usersModel.addUser(fnameInput.text, lnameInput.text, initialsInput.text )
            }
            else
            {
              console.log("modify")
              usersModel.modifyUser(usersTable.selectedrow, fnameInput.text, lnameInput.text, initialsInput.text )
            }

            usersTable.selectedrow = -1
            usersTable.addnewitem = false;
            fillRect.state = "normal"
          }
          KeyNavigation.tab: buttCancel
        }

        Button
        {
          id: buttCancel
          text: "Cancel"
          onClicked:
          {
            fnameInput.text = ""
            lnameInput.text = ""
            initialsInput.text = ""
            usersTable.selectedrow = -1
            usersTable.addnewitem = false;
            fillRect.state = "normal"
          }
          KeyNavigation.tab: fnameInput
        }
      }
    }

    states:
    [
      State
      {
        name: "normal"
        PropertyChanges { target: fillRect; width: 0; opacity: 0 }
        PropertyChanges { target: usersTable; enabled: true }
      },
      State
      {
        name: "active"
        PropertyChanges { target: fillRect; width: usersRect.width * 0.8; opacity: 1 }
        PropertyChanges { target: usersTable; enabled: false }
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

