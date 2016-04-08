import QtQuick 2.4
import QtQuick.Window 2.2

Window
{
    id: mainWindow
    visible: true

    width: 500
    height: 500

    Rectangle
    {
        id: topBar
        color: "#483c3c"
        height: 60
        anchors { top: parent.top; left: parent.left; right: parent.right }

        Image
        {
            id: accountIcon
            x: 5
            y: 5
            width: 50
            height: 50
            source: "images/face.png"

            MouseArea
            {
                anchors.fill: parent
                // todo do animation
            }
        }

        Rectangle
        {
            id: settingsRect
            color: "green"
            height: parent.height
            width: 15
            anchors { top: parent.top; right: parent.right }

            MouseArea
            {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
            }

            Image
            {
                id: settingsIcon
                visible: false
                width: 20
                height: 20
                anchors.left: parent.left
                anchors.leftMargin: 5
                source: "images/settings.png"
                opacity: 0.1
            }

            states:
            [
                State
                {
                    name: "hover"
                    when: mouseArea.containsMouse
                    PropertyChanges { target: settingsIcon; opacity: 1; visible: true }
                    PropertyChanges { target: settingsRect; width: 30 }
                    PropertyChanges { target: settingsIcon; rotation: 360 }
                }
            ]

            transitions:
            [
                Transition
                {
                    to: "hover"
                    NumberAnimation { target: settingsRect; property: "width"; duration: 100  }
                    NumberAnimation { target: settingsIcon; property: "opacity"; duration: 500  }
                    NumberAnimation { target: settingsIcon; property: "rotation"; duration: 1000  }
                }
            ]
        }
    }

    Rectangle
    {
        id: barSep
        color: "black"
        y: topBar.height
        height: 2
        anchors { left: parent.left; right: parent.right }
    }

    Rectangle
    {
        id: botBar
        height: parent.height - topBar.height - barSep.height
        gradient: Gradient {
            GradientStop {
                position: 0.52
                color: "#7d8680"
            }

            GradientStop {
                position: 0
                color: "#2f4235"
            }

            GradientStop {
                position: 0.765
                color: "#829488"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }


        }

        anchors { bottom: parent.bottom; left: parent.left; right: parent.right }
    }
}
