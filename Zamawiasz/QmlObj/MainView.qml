import QtQuick 2.0

Item
{
  id: mainView
  signal mv_changed(string name)
  property string nview_dddate: "no data"

  anchors { top: parent.top; left: parent.left; bottom: parent.bottom; right: parent.right; margins: 1 }

  /// set default state for the object
  state: "None"

  /// set state on button pressed
  onMv_changed: state = name

  states:
  [
    State
    {
      name: "None"
      PropertyChanges { target: noneView; visible: true }
      PropertyChanges { target: ordersView; ov_visible: false }
      PropertyChanges { target: usersView; uv_visible: false }
      PropertyChanges { target: statsView; sv_visible: false }
      PropertyChanges { target: settingsView; sev_visible: false }
    },
    State
    {
      name: "Orders"
      PropertyChanges { target: noneView; visible: false }
      PropertyChanges { target: ordersView; ov_visible: true }
      PropertyChanges { target: usersView; uv_visible: false }
      PropertyChanges { target: statsView; sv_visible: false }
      PropertyChanges { target: settingsView; sev_visible: false }
    },
    State
    {
      name: "Users"
      PropertyChanges { target: noneView; visible: false }
      PropertyChanges { target: ordersView; ov_visible: false }
      PropertyChanges { target: usersView; uv_visible: true }
      PropertyChanges { target: statsView; sv_visible: false }
      PropertyChanges { target: settingsView; sev_visible: false }
    },
    State
    {
      name: "Statistics"
      PropertyChanges { target: noneView; visible: false }
      PropertyChanges { target: ordersView; ov_visible: false }
      PropertyChanges { target: usersView; uv_visible: false }
      PropertyChanges { target: statsView; sv_visible: true }
      PropertyChanges { target: settingsView; sev_visible: false }
    },
    State
    {
      name: "Settings"
      PropertyChanges { target: noneView; visible: false }
      PropertyChanges { target: ordersView; ov_visible: false }
      PropertyChanges { target: usersView; uv_visible: false }
      PropertyChanges { target: statsView; sv_visible: false }
      PropertyChanges { target: settingsView; sev_visible: true }
    }
  ]

  Rectangle
  {
    id: noneView
    anchors.fill: parent
    color: "#483c3c"
    radius: 2

    Image
    {
      id: tbdIcon
      anchors.centerIn: parent
      width: 200
      height: 200
      source: "../images/under_construction.jpg"
      opacity: 0.5
    }
  }

  OrdersView
  {
    id: ordersView
  }

  UsersView
  {
    id: usersView
  }

  StatsView
  {
    id: statsView
  }

  SettingsView
  {
    id: settingsView
    objectName: "settings"
  }
}
