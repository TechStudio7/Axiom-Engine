package axiom.script;

typedef ScriptResult = {
    var output:Array<String>;
    var events:Array<ScriptEvent>;
    var variables:Map<String, String>;
}
