package axiom;

import js.html.CanvasRenderingContext2D;
import axiom.script.AxiomScript;

class AxiomHaxe {
    static function main():Void {
        final engine = new Engine({
            canvasId: "game",
            width: 960,
            height: 540,
            clearColor: "#181818"
        });

        engine.setScene(new DemoScene());
        engine.start();
    }
}

class DemoScene extends Scene {
    var x:Float = 480;
    var y:Float = 270;
    var time:Float = 0;
    final script = new AxiomScript();

    public function new() {
        super("HaxeDemo");
        script.run("let greeting = \"AxiomScript ready\"\nprint $greeting\nemit boot hx-axiom");
    }

    override public function update(delta:Float):Void {
        time += delta;
        final speed = 260;

        if (Input.down("a") || Input.down("arrowleft")) {
            x -= speed * delta;
        }
        if (Input.down("d") || Input.down("arrowright")) {
            x += speed * delta;
        }
        if (Input.down("w") || Input.down("arrowup")) {
            y -= speed * delta;
        }
        if (Input.down("s") || Input.down("arrowdown")) {
            y += speed * delta;
        }
    }

    override public function render(context:CanvasRenderingContext2D):Void {
        final pulse = 12 + Math.sin(time * 3) * 6;

        context.save();
        context.fillStyle = "rgba(255, 29, 22, 0.18)";
        context.beginPath();
        context.arc(x, y, 58 + pulse, 0, Math.PI * 2);
        context.fill();

        context.fillStyle = "#ff1d16";
        context.font = "700 28px Arial";
        context.textAlign = "center";
        context.textBaseline = "middle";
        context.fillText("hx-axiom", x, y);
        context.restore();
    }
}
