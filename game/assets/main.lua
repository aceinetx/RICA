MainScene = require("assets/mainscene")

engine = Engine.getInstance()
engine:set3Dmode(true)

if not engine:init() then
	print("engine init fail")
	return
end

render3d = Render3DSystem.getInstance()
render3d:setSkyColor(Color(100, 100, 100, 255))

local scene = MainScene:new()

engine.sceneManager:addScene(scene)

engine:mainLoop()
