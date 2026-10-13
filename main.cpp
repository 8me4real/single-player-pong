#include <raylib.h>

int player_score = 0;

class Ball
{
public:
	float x, y, radius, speed_x, speed_y;

	void Draw()
	{
		DrawCircle(x, y, radius, MAGENTA);
	}

	void Move()
	{
		x += speed_x;
		y += speed_y;
		if (x + radius >= GetScreenWidth() || x - radius <= 0)
		{
			speed_x *= -1;
		}
		if (y - radius <= 0)
		{
			speed_y *= -1;
		}
		if (y + radius >= GetScreenHeight())
		{
			speed_y *= -1;
			player_score = 0;
		}
	}
};

class Platform
{
public:
	float x, y, width, height, speed;
	
	void Draw()
	{
		Rectangle nais = { x - width / 2, y + height / 2, width, height };
		DrawRectangleRounded(nais, 1.1, 0, MAGENTA);
	}

	void Move()
	{
		if (IsKeyDown(KEY_LEFT) && x - width / 2 - 5 >= 0)
		{
			x -= speed;
		}

		if (IsKeyDown(KEY_RIGHT) && x + width / 2 + 5 <= GetScreenWidth())
		{
			x += speed;
		}
	}
};

Ball ball;
Platform player;

int main() {
	int screen_width = 450;
	int screen_height = 900;
	
	InitWindow(screen_width, screen_height, "idk how its called");
	SetTargetFPS(70);

	ball.x = 40;
	ball.y = 40;
	ball.radius = 20;
	ball.speed_x = 9;
	ball.speed_y = 7;

	player.x = screen_width / 2;
	player.y = screen_height - 25;
	player.width = 75;
	player.height = 10;
	player.speed = 6;

	while (!WindowShouldClose()) 
	{
		BeginDrawing();

		int text_width = MeasureText(TextFormat("%i", player_score), 100);
		int text_x = (screen_width - text_width) / 2;
		int text_y = (screen_height - 100) / 2;
		
		DrawText(TextFormat("%i", player_score), text_x, text_y, 100, WHITE);

		ClearBackground(YELLOW);
		
		ball.Move();
		ball.Draw();

		player.Move();
		player.Draw();

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x - player.width / 2, player.y, player.width, player.height }))
		{
			ball.speed_y *= -1;
			player_score++;
		}
		EndDrawing();
	}

}
