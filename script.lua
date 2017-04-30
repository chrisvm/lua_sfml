function setup()
	window.antialias = 8
	window.create(600, 400)
	print('screen width: ' .. window.width)
	print('screen height: ' .. window.height)

	shape = CircleShape.new(50.0)
	shape:setFillColor(color.White)
end

function update()
	local delta = 0.001
	shape:move(delta, delta)
end

function draw()
	window.clear()
	update()
	shape:draw()
	window.display()
end
