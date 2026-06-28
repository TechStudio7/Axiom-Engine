(function () {
    "use strict";

    const canvas = document.getElementById("game");
    const context = canvas.getContext("2d");
    const fpsLabel = document.getElementById("fps");

    const keys = new Set();
    const player = {
        x: canvas.width * 0.5,
        y: canvas.height * 0.5,
        radius: 22,
        speed: 260
    };

    let lastTime = performance.now();
    let fpsTime = 0;
    let fpsFrames = 0;

    window.addEventListener("keydown", (event) => {
        keys.add(event.key.toLowerCase());
    });

    window.addEventListener("keyup", (event) => {
        keys.delete(event.key.toLowerCase());
    });

    function update(deltaSeconds) {
        let xAxis = 0;
        let yAxis = 0;

        if (keys.has("arrowleft") || keys.has("a")) {
            xAxis -= 1;
        }
        if (keys.has("arrowright") || keys.has("d")) {
            xAxis += 1;
        }
        if (keys.has("arrowup") || keys.has("w")) {
            yAxis -= 1;
        }
        if (keys.has("arrowdown") || keys.has("s")) {
            yAxis += 1;
        }

        if (xAxis !== 0 && yAxis !== 0) {
            xAxis *= Math.SQRT1_2;
            yAxis *= Math.SQRT1_2;
        }

        player.x += xAxis * player.speed * deltaSeconds;
        player.y += yAxis * player.speed * deltaSeconds;
        player.x = Math.max(player.radius, Math.min(canvas.width - player.radius, player.x));
        player.y = Math.max(player.radius, Math.min(canvas.height - player.radius, player.y));
    }

    function render() {
        context.clearRect(0, 0, canvas.width, canvas.height);

        context.fillStyle = "#181818";
        context.fillRect(0, 0, canvas.width, canvas.height);

        context.strokeStyle = "#2a2a2a";
        context.lineWidth = 1;
        for (let x = 0; x <= canvas.width; x += 48) {
            context.beginPath();
            context.moveTo(x, 0);
            context.lineTo(x, canvas.height);
            context.stroke();
        }
        for (let y = 0; y <= canvas.height; y += 48) {
            context.beginPath();
            context.moveTo(0, y);
            context.lineTo(canvas.width, y);
            context.stroke();
        }

        context.fillStyle = "#ff1d16";
        context.beginPath();
        context.arc(player.x, player.y, player.radius, 0, Math.PI * 2);
        context.fill();

        context.fillStyle = "#050505";
        context.font = "700 24px Arial, Helvetica, sans-serif";
        context.textAlign = "center";
        context.textBaseline = "middle";
        context.fillText("A", player.x, player.y + 1);
    }

    function updateFps(deltaSeconds) {
        fpsTime += deltaSeconds;
        fpsFrames += 1;

        if (fpsTime >= 0.5) {
            fpsLabel.textContent = `${Math.round(fpsFrames / fpsTime)} FPS`;
            fpsTime = 0;
            fpsFrames = 0;
        }
    }

    function frame(now) {
        const deltaSeconds = Math.min((now - lastTime) / 1000, 0.05);
        lastTime = now;

        update(deltaSeconds);
        render();
        updateFps(deltaSeconds);

        requestAnimationFrame(frame);
    }

    requestAnimationFrame(frame);
}());
