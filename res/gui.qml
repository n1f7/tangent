import QtQuick 2.6
import QtQuick.Controls 1.4

Rectangle {
	width: 800
	height: 600

	Text {
		id: help
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		text: "Touch circles by clicking LMB inside a window"
		font.pointSize: 20
	}

	Slider {
		z: 2
		value: 25.0
		id: slider
		minimumValue: 10.0
		maximumValue: 150.0
		anchors.top: help.bottom
		anchors.horizontalCenter: help.horizontalCenter
	}

	Canvas {
		z: 0
		id: canvas
		anchors.fill: parent
	}

	function clear_context() {
		var ctx = canvas.getContext("2d")
		ctx.reset()
	}
	
	function draw() {
		canvas.requestPaint()
	}

	function draw_circle(x, y, r) {
		var ctx = canvas.getContext("2d")
		ctx.lineWidth = 2
		ctx.strokeStyle = "black"
		ctx.beginPath()
		ctx.arc(x, y, r, 0, Math.PI * 2, false)
		ctx.stroke();
	}

	function draw_line(a_x, a_y, b_x, b_y) {
		var ctx = canvas.getContext("2d")
		ctx.lineWidth = 2
		ctx.strokeStyle = "black"
		ctx.beginPath()
		ctx.moveTo(a_x, a_y)
		ctx.lineTo(b_x, b_y)
		ctx.stroke();
	}


	MouseArea {
		z: 1
		anchors.fill: parent
		propagateComposedEvents: true
		onClicked: {
			controller.add_circle(mouseX, mouseY, slider.value);
		}
	}
}
