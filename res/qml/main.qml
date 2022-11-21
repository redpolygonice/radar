import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.15
import App.Broker 1.0

ApplicationWindow {
	id: mainWindow
	x: Screen.width / 2 - width / 2
	y: Screen.height / 2 - height / 2
	width: 1200
	height: 800
	visible: true
	title: qsTr("Radar")

	header: ToolBar {
		id: toolbar
		width: parent.width
		height: 40

		RowLayout {
			spacing: 0
			PanelButton {
				id: connectButton
				icon.source: "qrc:/img/start.png"
				ToolTip.text: qsTr("Start")
				onClicked: start()
			}
			PanelButton {
				id: disconnectButton
				icon.source: "qrc:/img/stop.png"
				ToolTip.text: qsTr("Stop")
				onClicked: stop()
			}
			PanelButton {
				id: mapButton
				icon.source: "qrc:/img/quit.png"
				ToolTip.text: qsTr("Quit application")
				onClicked: mainWindow.close()
			}
			ToolSeparator {}
			PanelButton {
				id: homeButton
				icon.source: "qrc:/img/settings.png"
				ToolTip.text: qsTr("Settings ..")
				onClicked: showSettings()
			}
		}
	}

	Image {
		id: map
		anchors.fill: parent
		fillMode: Image.PreserveAspectCrop
		antialiasing: true
		source: "qrc:/img/map.png"

		property int number: 0
		property int xpos: 0
		property int ypos: 0
		property variant frames: null

		Component.onCompleted: {
			broker.onFramesChanged.connect(function() {
				update()
			})
		}

		function update()
		{
			map.frames = broker.frames
			canvas.requestPaint()
		}

		Canvas {
			id: canvas
			anchors.fill: parent

			onPaint: {
				if (map.frames === null)
					return

				var context = getContext("2d");
				context.clearRect(map.x, map.y, map.width, map.height)

				for (var i = 0; i < map.frames.length; i++)
				{
					map.number = map.frames[i]["id"]
					map.xpos = map.frames[i]["x"]
					map.ypos = map.frames[i]["y"]

					if (map.number === 0)
						return

					context.strokeStyle = "red"
					context.fillStyle = "green";
					context.lineWidth = 3;
					context.beginPath();
					context.rect(map.xpos, map.ypos, 18, 30)
					context.stroke();
					context.fill();
					context.closePath();

					context.beginPath();
					context.font = '10px sans-serif';
					context.lineWidth = 1;
					context.strokeStyle = "white"
					context.strokeText(map.number, map.xpos + 6, map.ypos + 18);
					context.stroke();
					context.closePath();
				}
			}
		}
	}

	function start()
	{
		broker.start()
	}

	function stop()
	{
		broker.stop()
	}

	function showSettings()
	{
	}
}
