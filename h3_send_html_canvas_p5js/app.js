const TOTAL_WIDTH = 32
const TOTAL_HEIGHT = 32
const TARGET_FPS = 30 // frames per second

let p5jsCanvas

function setup() {
	p5jsCanvas = createCanvas(TOTAL_WIDTH, TOTAL_HEIGHT)
	frameRate(TARGET_FPS)
	pixelDensity(1)
}

function draw() {
	background(0)

	translate(TOTAL_WIDTH / 2, TOTAL_HEIGHT / 2)
	rotate(frameCount * 0.03)

	const round = 5
	noFill()
	stroke(255)
	rect(-12, -4, 24, 8, round)
	rect(-4, -12, 8, 24, round)

	// Write data to the serial port
	serialPortWriterLoop(p5jsCanvas.canvas.getContext('2d'))
}

