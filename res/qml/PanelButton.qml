import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.15

ToolButton {
	id: control
	Layout.preferredHeight: 40
	Layout.preferredWidth: 40
	ToolTip.visible: hovered
	ToolTip.delay: Qt.styleHints.mousePressAndHoldInterval
	padding: 2

	background: Rectangle {

		color: {
			if (mouseArea.containsMouse)
				return "#aaaaaa"
			else if (control.checked || control.down)
				return "#aaaaaa"
			else
				return "transparent"
		}

		MouseArea {
			id: mouseArea
			anchors.fill: parent
			hoverEnabled: true
			cursorShape: Qt.PointingHandCursor
			onClicked: control.clicked()
		}
	}
}
