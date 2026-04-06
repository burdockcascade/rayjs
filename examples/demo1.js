// main.js

// 1. Initialize the window
const screenWidth = 800;
const screenHeight = 450;
Raylib.InitWindow(screenWidth, screenHeight, "Raylib meets QuickJS! 🚀");

// 2. Set FPS
Raylib.SetTargetFPS(60);

let circleX = screenWidth / 2;
const circleY = screenHeight / 2;
let velocity = 3;

// 3. Main game loop
// We use the global functions we bound in C++
while (!Raylib.WindowShouldClose()) {
    // --- Update Logic ---
    circleX += velocity;
    if (circleX > screenWidth - 50 || circleX < 50) {
        velocity *= -1; // Reverse direction
    }

    // --- Drawing Logic ---
    Raylib.BeginDrawing();
    
    // ClearBackground uses a pre-defined color 'RAYWHITE' 
    // that we exposed from C++
    Raylib.ClearBackground(Raylib.RAYWHITE); 
    
    Raylib.DrawText("Hello from JavaScript!", 20, 20, 20, Raylib.BLUE);
    
    // DrawCircle uses a custom color object we create here in JS
    const customColor = new Color(230, 41, 55, 255); // A nice red
    Raylib.DrawCircle(circleX, circleY, 50, customColor);

    Raylib.EndDrawing();
}

// NOTE: We don't call CloseWindow(). Raylib's InitWindow() registers
// an 'atexit' handler in C, so when our C++ main() function finishes,
// Raylib will clean up and close the window automatically.