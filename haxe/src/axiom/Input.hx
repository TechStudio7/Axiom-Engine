package axiom;

import js.Browser;
import js.html.KeyboardEvent;

class Input {
    static final keys:Map<String, Bool> = [];
    static var ready:Bool = false;

    public static function initialize():Void {
        if (ready) {
            return;
        }

        Browser.window.addEventListener("keydown", function(event:KeyboardEvent) {
            keys.set(event.key.toLowerCase(), true);
        });

        Browser.window.addEventListener("keyup", function(event:KeyboardEvent) {
            keys.remove(event.key.toLowerCase());
        });

        ready = true;
    }

    public static function down(key:String):Bool {
        return keys.exists(key.toLowerCase());
    }
}
