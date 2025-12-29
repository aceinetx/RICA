import rica
from assets.main_scene import *

engine = rica.Engine.getInstance()
engine.set3Dmode(True)

if not engine.init():
	print("Engine init failed")
	exit(1)

render3d = rica.Render3DSystem.getInstance()
render3d.setSkyColor(rica.Color(255, 0, 0, 255))
print(render3d.getSkyColor())

scene = MainScene()
scene.autorelease()
engine.sceneManager.addScene(scene)

engine.mainLoop()
