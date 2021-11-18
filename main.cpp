#include "raylib.h"
#include <stdlib.h>

class Player {
public:
	Vector2 playerPosition;
	int score;
	void draw(Vector2 midScreenVec) {
		DrawRectangleV(midScreenVec, {10, 60}, WHITE);
	}
};

Vector2 generateBallSpeed() {
	Vector2 ballSpeed;
	if ((rand() % 2) == 0) {
		ballSpeed.x = 6;
	} else {
		ballSpeed.x = -6;
	}
	if ((rand() % 2) == 0) {
		ballSpeed.y = rand() % -4 + 4;
	} else {
		ballSpeed.y = rand() % 4 - 4;
	}
	return ballSpeed;
}

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "pong");

	SetTargetFPS(60);

	Vector2 ballPosition = {(float)screenWidth / 2 - 5, (float)screenHeight / 2 - 5};
	Vector2 ballSpeed = generateBallSpeed();
	
	int ballRadius = 10;

	Player player1;
	player1.score = 0;
	player1.playerPosition = {60, (float)screenHeight / 2 - 30};
	Player player2;
	player2.score = 0;
	player2.playerPosition = {screenWidth - 60, (float)screenHeight / 2 - 30};

	bool pause = 0;

	while (!WindowShouldClose()) {

		if (IsKeyDown(KEY_SPACE))
			pause = 0;

		if (!pause) {
			if (IsKeyDown(KEY_UP))
				player2.playerPosition.y -= 6.0f;
			if (IsKeyDown(KEY_DOWN))
				player2.playerPosition.y += 6.0f;
			if (IsKeyDown(KEY_W))
				player1.playerPosition.y -= 6.0f;
			if (IsKeyDown(KEY_S))
				player1.playerPosition.y += 6.0f;

			ballPosition.x += ballSpeed.x;
			ballPosition.y += ballSpeed.y;
			if ((ballPosition.y >= (screenHeight - ballRadius)) ||
					(ballPosition.y <= ballRadius))
				ballSpeed.y *= -1.0f;
			if (ballPosition.x >= (screenWidth - ballRadius)) {
				player1.score += 1;
				ballPosition = {(float)screenWidth / 2 - 5, (float)screenHeight / 2 - 5};
				ballSpeed = generateBallSpeed();
				pause = 1;
			}
			else if (ballPosition.x <= -ballRadius) {
				player2.score += 1;
				ballPosition = {(float)screenWidth / 2 - 5, (float)screenHeight / 2 - 5};
				ballSpeed = generateBallSpeed();
				pause = 1;
			}

			if (ballPosition.x >= (player1.playerPosition.x - ballRadius) &&
					ballPosition.x <= (player1.playerPosition.x + 10) &&
					ballPosition.y >= (player1.playerPosition.y - ballRadius) &&
					ballPosition.y <= (player1.playerPosition.y + 60)) {
				ballSpeed.x *= -1.0f;
			}
			if (ballPosition.x >= (player2.playerPosition.x - 10) &&
					ballPosition.x <= (player2.playerPosition.x + ballRadius) &&
					ballPosition.y >= (player2.playerPosition.y - ballRadius) &&
					ballPosition.y <= (player2.playerPosition.y + 60)) {
				ballSpeed.x *= -1.0f;
			}
		}

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("%d || %d", player1.score, player2.score), 20, 20, 28,
						 WHITE);

		player1.draw(player1.playerPosition);
		player2.draw(player2.playerPosition);

		DrawCircleV(ballPosition, ballRadius, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
