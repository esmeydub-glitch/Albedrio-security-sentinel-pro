import QtQuick
import QtQuick.Controls

Window {
    width: 1100
    height: 800
    visible: true
    title: "SALK SOBERANO - GLASS COMMAND CENTER"
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.Window

    Rectangle {
        id: mainBackground
        anchors.fill: parent
        color: "#0a0a0a"
        opacity: 0.9
        radius: 20
        border.color: "#b080ff"
        border.width: 1

        Rectangle {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#ffffff0a" }
                GradientStop { position: 1.0; color: "#00000000" }
            }
            radius: 20
        }

        Rectangle {
            id: sideBar
            width: 300
            height: parent.height - 40
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20
            color: "#1a1a1a"
            opacity: 0.8
            radius: 15
            border.color: "#444"

            Column {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15
                Text { text: "SYSTEM MONITOR"; color: "#00ffff"; font.bold: true; font.pixelSize: 18 }
                Text { text: "CPU LOAD: 14.7%"; color: "white"; font.pixelSize: 14 }
                Rectangle { width: 260; height: 30; color: "#000"; border.color: "#333"
                    Rectangle { width: 40; height: 26; anchors.verticalCenter: parent.verticalCenter; x: 2; color: "#00ffff" }
                }
                Text { text: "RAM: 7.2GB / 64GB"; color: "white"; font.pixelSize: 14 }
                Rectangle { width: 260; height: 30; color: "#000"; border.color: "#333"
                    Rectangle { width: 60; height: 26; anchors.verticalCenter: parent.verticalCenter; x: 2; color: "#b080ff" }
                }
                Text { text: "TOR SHIELD: ENCRYPTED"; color: "#00ff00"; font.bold: true; font.pixelSize: 14 }
                Text { text: "TRAFFIC: 1.2 MB/s"; color: "white"; font.pixelSize: 14 }
                Rectangle { width: 260; height: 80; color: "#000"; border.color: "#333"
                    Text { text: "~~~^~~~^~~~^~~~"; color: "#00ffff"; anchors.centerIn: parent }
                }
                Text { text: "SYSTEM HEALTH: OPTIMAL"; color: "#00ff00"; anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 12 }
            }
        }

        Rectangle {
            id: shellWindow
            width: 700
            height: 400
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 30
            color: "#050505"
            radius: 10
            border.color: "#b080ff"

            Column {
                anchors.fill: parent
                anchors.margins: 15
                Text { text: "[SALK-OS 1.1.2 // THINKPAD-P16V-SALK-001]"; color: "#808080"; font.pixelSize: 14 }
                Text { text: "$ sal_init.sh"; color: "white"; font.pixelSize: 14 }
                Text { text: ">> SOVEREIGN MODE ACTIVE"; color: "#00ffff"; font.pixelSize: 14 }
                Text { text: ">> KERNEL: 6.x-SALK"; color: "#00ffff"; font.pixelSize: 14 }
                Text { text: ">> TOR: OPERATIONAL"; color: "#00ff00"; font.pixelSize: 14 }
                Text { text: ""; color: "white"; font.pixelSize: 14 }
                Text { text: "[root@salk-p16v ~]# _"; color: "white"; font.pixelSize: 14; font.bold: true }
            }
        }

        Text {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 30
            text: "S.A.L.K."
            font.pixelSize: 40
            color: "#b080ff"
            font.bold: true
            opacity: 0.5
        }
    }
}
