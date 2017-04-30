function setup()
	window.antialias = 8
	window.create(600, 400)
	print('screen width: ' .. window.width)
	print('screen height: ' .. window.height)

	local shape1 = CircleShape.new(10.0)
	shape1:setFillColor(color.White)

	local shape2 = CircleShape.new(30.0)
	shape2:setFillColor(color.Red)

	local shape3 = CircleShape.new(50.0)
	shape3:setFillColor(color.Blue)

	shapes = { shape1, shape2, shape3 }
end

function update()
	local delta = 0.001
	for index = 1, #shapes do
		shapes[index]:move(delta, delta)
	end
end

function draw()
	window.clear()
	update()
	for index = 1, #shapes do
		shapes[index]:draw()
	end
	window.display()
end
