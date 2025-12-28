local MainScene = {}
function MainScene:onUpdate(delta)
	self.base:onUpdate(delta)
	print(delta)
end

return MainScene
