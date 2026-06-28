package axiom;

import js.Browser;
import js.html.CanvasElement;
import js.html.CanvasRenderingContext2D;

class Engine {
    public final canvas:CanvasElement;
    public final context:CanvasRenderingContext2D;

    final clearColor:String;
    var scene:Scene;
    var lastTime:Float = 0;

    public function new(config:EngineConfig) {
        canvas = cast Browser.document.getElementById(config.canvasId);
        if (canvas == null) {
            throw 'Axiom canvas not found: ${config.canvasId}';
        }

        if (config.width != null) {
            canvas.width = config.width;
        }
        if (config.height != null) {
            canvas.height = config.height;
        }

        context = canvas.getContext2d();
        clearColor = config.clearColor != null ? config.clearColor : "#181818";
        Input.initialize();
    }

    public function setScene(scene:Scene):Void {
        this.scene = scene;
    }

    public function start():Void {
        lastTime = Browser.window.performance.now();
        Browser.window.requestAnimationFrame(frame);
    }

    function frame(now:Float):Void {
        final delta = Math.min((now - lastTime) / 1000, 0.05);
        lastTime = now;

        context.fillStyle = clearColor;
        context.fillRect(0, 0, canvas.width, canvas.height);

        if (scene != null) {
            scene.update(delta);
            scene.render(context);
        }

        Browser.window.requestAnimationFrame(frame);
    }
}
