import rica
engine = rica.Engine.getInstance()
engine.set3Dmode(True)

if not engine.init():
	print("Engine init failed")
	exit(1)

render3d = rica.Render3DSystem.getInstance()
render3d.setSkyColor(rica.Color(255, 0, 0, 255))

class MainScene(rica.Scene):
	def onUpdate(self, delta):
		print(f"onUpdate {delta}")

scene = MainScene()
scene.autorelease()

engine.sceneManager.addScene(scene)

engine.mainLoop()
