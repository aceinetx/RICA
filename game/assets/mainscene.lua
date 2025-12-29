local MainScene = {}

function MainScene:new()
	o = {}
	setmetatable(o, self)
	self.__index = self
	return Scene.from(o)
end

function MainScene:constructor()
	print("In constructor of MainScene")
end

function MainScene:onUpdate(delta)
	print(delta)
	print(self.super:onUpdate(delta))
end

return MainScene
