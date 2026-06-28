package axiom.script;

class AxiomScript {
    final variables:Map<String, String> = [];
    final output:Array<String> = [];
    final events:Array<ScriptEvent> = [];

    public function new() {
    }

    public function run(source:String):ScriptResult {
        output.resize(0);
        events.resize(0);

        final lines = source.split("\n");
        for (index in 0...lines.length) {
            executeLine(StringTools.trim(lines[index]), index + 1);
        }

        return {
            output: output.copy(),
            events: events.copy(),
            variables: variables.copy()
        };
    }

    function executeLine(line:String, lineNumber:Int):Void {
        if (line == "" || StringTools.startsWith(line, "#")) {
            return;
        }

        if (StringTools.startsWith(line, "print ")) {
            output.push(resolve(line.substr(6)));
            return;
        }

        if (StringTools.startsWith(line, "let ")) {
            final assignment = line.substr(4);
            final equals = assignment.indexOf("=");
            if (equals < 1) {
                output.push('Line ${lineNumber}: expected let name = value');
                return;
            }

            final name = StringTools.trim(assignment.substr(0, equals));
            final value = resolve(StringTools.trim(assignment.substr(equals + 1)));
            variables.set(name, value);
            return;
        }

        if (StringTools.startsWith(line, "emit ")) {
            final payload = line.substr(5);
            final separator = payload.indexOf(" ");
            final name = separator == -1 ? payload : payload.substr(0, separator);
            final data = separator == -1 ? "" : resolve(payload.substr(separator + 1));
            events.push({name: name, data: data});
            return;
        }

        output.push('Line ${lineNumber}: unknown command "${line}"');
    }

    function resolve(value:String):String {
        final trimmed = StringTools.trim(value);
        if (StringTools.startsWith(trimmed, "$")) {
            final name = trimmed.substr(1);
            return variables.exists(name) ? variables.get(name) : "";
        }

        if (StringTools.startsWith(trimmed, "\"") && StringTools.endsWith(trimmed, "\"")) {
            return trimmed.substr(1, trimmed.length - 2);
        }

        return trimmed;
    }
}
