test()

--[[
engine = Engine.getInstance()
engine:set3Dmode(true)
render3d = Render3DSystem.getInstance()
render3d:setSkyColor(Color(255, 0, 0, 255))

if not engine:init() then
	print("engine init fail")
	return
end

local scene = Scene.create()
engine.sceneManager:addScene(scene)

print(engine)
]]--
