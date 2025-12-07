const screenWidth = 800;
const screenHeight = 450;

Raylib.InitWindow(screenWidth, screenHeight, "Raylib meets QuickJS! 🚀");

let fps = 60;
Raylib.SetTargetFPS(fps);

const red = new Raylib.Color(230, 41, 55, 255);
const blue = new Raylib.Color(0, 121, 241, 255);

const currentScreenWidth = Raylib.GetScreenWidth();
const currentScreenHeight = Raylib.GetScreenHeight();

Raylib.SetWindowTitle(`Current Size: ${currentScreenWidth} x ${currentScreenHeight}`);

while (!Raylib.WindowShouldClose()) {
    Raylib.BeginDrawing();
    Raylib.ClearBackground(blue);
    Raylib.EndDrawing();
}
