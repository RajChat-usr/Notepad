#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Define the size of the grid
const int GRID_SIZE = 20;
const int TILE_SIZE = 20;

// Directions
enum Direction { UP, DOWN, LEFT, RIGHT };

// Snake and Food struct
struct Snake {
    int length;
    Vector2 body[100];
    Direction direction;
};

struct Food {
    Vector2 position;
};

void InitGame(Snake& snake, Food& food) {
    snake.length = 1;
    snake.body[0] = {10 * TILE_SIZE, 10 * TILE_SIZE};
    snake.direction = RIGHT;
    food.position = {rand() % GRID_SIZE * TILE_SIZE, rand() % GRID_SIZE * TILE_SIZE};
}

void DrawSnake(const Snake& snake) {
    for (int i = 0; i < snake.length; i++) {
        // Draw each part of the snake as a colored square
        Color snakeColor = (i == 0) ? DARKGREEN : GREEN; // Head is darker
        DrawRectangle(snake.body[i].x, snake.body[i].y, TILE_SIZE, TILE_SIZE, snakeColor);
    }
}

void DrawFood(const Food& food) {
    DrawRectangle(food.position.x, food.position.y, TILE_SIZE, TILE_SIZE, RED);
}

void MoveSnake(Snake& snake) {
    // Move snake body
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }

    // Move snake head
    switch (snake.direction) {
        case UP: snake.body[0].y -= TILE_SIZE; break;
        case DOWN: snake.body[0].y += TILE_SIZE; break;
        case LEFT: snake.body[0].x -= TILE_SIZE; break;
        case RIGHT: snake.body[0].x += TILE_SIZE; break;
    }
}

bool CheckCollision(Snake& snake, Food& food) {
    // Check if snake eats food
    if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y) {
        snake.length++;
        food.position = {rand() % GRID_SIZE * TILE_SIZE, rand() % GRID_SIZE * TILE_SIZE}; // Respawn food
        return true;
    }
    return false;
}

bool CheckSelfCollision(Snake& snake) {
    // Check if snake bites itself
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            return true;
        }
    }
    return false;
}

bool CheckWallCollision(Snake& snake) {
    // Check if snake hits the walls
    if (snake.body[0].x < 0 || snake.body[0].x >= GRID_SIZE * TILE_SIZE || snake.body[0].y < 0 || snake.body[0].y >= GRID_SIZE * TILE_SIZE) {
        return true;
    }
    return false;
}

int main() {
    // Initialize the window
    const int screenWidth = GRID_SIZE * TILE_SIZE;
    const int screenHeight = GRID_SIZE * TILE_SIZE;
    InitWindow(screenWidth, screenHeight, "Nokia Snake Game with Raylib");

    // Set random seed
    srand(time(NULL));

    Snake snake;
    Food food;

    InitGame(snake, food);

    SetTargetFPS(10);  // Set FPS to slow down the game (feel free to adjust)

    // Main game loop
    while (!WindowShouldClose()) {
        // Update direction based on input
        if (IsKeyPressed(KEY_UP) && snake.direction != DOWN) snake.direction = UP;
        if (IsKeyPressed(KEY_DOWN) && snake.direction != UP) snake.direction = DOWN;
        if (IsKeyPressed(KEY_LEFT) && snake.direction != RIGHT) snake.direction = LEFT;
        if (IsKeyPressed(KEY_RIGHT) && snake.direction != LEFT) snake.direction = RIGHT;

        // Move the snake and check if it eats food
        MoveSnake(snake);

        if (CheckCollision(snake, food)) {
            // Snake eats food, increase length and spawn new food
        }

        if (CheckSelfCollision(snake) || CheckWallCollision(snake)) {
            // Game Over condition
            break;
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawSnake(snake);
        DrawFood(food);

        DrawText("Snake Game", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
