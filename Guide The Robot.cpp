///////////////////////////////////////////////////////////////////////LIBRARIES////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/audio.hpp>
#include <fstream>
#include <Windows.h>

///////////////////////////////////////////////////////////////////////GLOBAL VARIABLES AND MACRO CONSTANTS////////////////////////////////////////////////////////////////////////////////////

#define N1 2
#define N2 1
#define N3 1
#define N4 38
#define N4_1 21
#define nLevels 3
int game_state = 1;

///////////////////////////////////////////////////////////////////////NAMESPACES////////////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace sf;

namespace fonts
{
	string f[1] = { "C://Media/Comic Sans.ttf" };
}

namespace add1
{
	string A[N1] = { "C://Media/Title Wallpaper.png", "C://Media/Title Proceed.png" };
}

namespace add2
{
	string A[N2] = { "C://Media/Menu Wallpaper.png" };
}

namespace add3
{
	string A[N3] = { "C://Media/Instructions.png" };
}

namespace add4
{
	string A[N4] = { "C://Media/Robot Empty.png", "C://Media/Block.png", "C://Media/Play.png", "C://Media/Up.png", "C://Media/Left.png", "C://Media/Right.png", "C://Media/Clock.png", "C://Media/Close.png", "C://Media/Open.png", "C://Media/Forward.png", "C://Media/A C.png", "C://Media/C.png", "C://Media/Red.png", "C://Media/Blue.png", "C://Media/Yellow.png", "C://Media/Empty Red.png", "C://Media/Empty Blue.png", "C://Media/Empty Yellow.png", "C://Media/Menu.png", "C://Media/Retry.png", "C://Media/Menu Exit B.png", "C://Media/Robot Red.png", "C://Media//Robot Blue.png", "C://Media/Robot Yellow.png", "C://Media/Red Full.png", "C://Media/Blue Full.png", "C://Media/Yellow Full.png", "C://Media/Up H.png", "C://Media/Left H.png", "C://Media/Right H.png", "C://Media/Clock H.png", "C://Media/Close H.png", "C://Media/Open H.png", "C://Media/Play H.png", "C://Media/Menu H.png", "C://Media/Retry H.png", "C://Media/explosion.png", "C://Media/Menu Exit.png" };
}

namespace no_go
{
	int arr[25][15] = {};
}

namespace level
{
	int arr_place[25][15] = {};
}

namespace levelFiles
{
	string A[nLevels] = { "C://Media/level 1.txt", "C://Media/level 2.txt", "C://Media/level 3.txt" };
}

///////////////////////////////////////////////////////////////////////FUNCTIONS////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////GAME CLASS////////////////////////////////////////////////////////////////////////////////////

class Game
{
public:
	virtual void run() = 0;

protected:
	void processEvents();
	void update();
	void render();
	void place_sprite(RenderWindow &, Sprite &, int, int, int, int);
	void place_sprite(RenderWindow &, Sprite &, int);
};

void Game::place_sprite(RenderWindow &window, Sprite &sprite, int a, int b, int no_go_p, int origin_c)
{
	window.draw(sprite);
	if (origin_c == 1)
		sprite.setOrigin(25, 25);
	else
		sprite.setOrigin(0, 0);
	sprite.setPosition(a, b);
	if (no_go_p == 1)
		no_go::arr[(a - 25) / 50][(b - 25) / 50] = 1;
}

void Game::place_sprite(RenderWindow &window, Sprite &sprite, int type)
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (level::arr_place[i][j] == type){
				window.draw(sprite);

				if (type != 1 && type != 10 && type != 11 && type != 12)
					no_go::arr[i][j] = 1;

				if (type == 21)
					no_go::arr[i][j] = 2;
			}
			sprite.setOrigin(25, 25);
			sprite.setPosition((i * 50) + 25, (j * 50) + 25);

		}
	}
}

///////////////////////////////////////////////////////////////////////TITLE WINDOW////////////////////////////////////////////////////////////////////////////////////

class TitleWindow : public Game
{
public:
	TitleWindow();
	void run();

protected:
	void processEvents();
	void update();
	void render();

private:
	RenderWindow window;
	Texture texture[N1];
	Sprite sprite[N1];
	Vector2i mouse_pos;
};

TitleWindow::TitleWindow() : window(VideoMode(1280, 720), "Title Window"), texture(), sprite()
{
	for (int i = 0; i < N1; i++)
	{
		if (!texture[i].loadFromFile(add1::A[i]))
		{
			cout << "The filename " << add1::A[i] << " could not be loaded" << endl;
		}
		sprite[i].setTexture(texture[i]);
	}
}

void TitleWindow::run()
{

	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void TitleWindow::processEvents()
{
	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			game_state = 0;

		mouse_pos = Mouse::getPosition(window);

		if ((mouse_pos.x > 550 && mouse_pos.x < (710) && mouse_pos.y>600 && mouse_pos.y < 716) && Mouse::isButtonPressed(Mouse::Left))
			game_state = 2;
	}
}

void TitleWindow::update()
{
	if (game_state != 1)
		window.close();
}

void TitleWindow::render()
{
	window.clear();
	place_sprite(window, sprite[0], 0, 0, 0, 0);
	place_sprite(window, sprite[1], 550, 600, 0, 0);
	window.display();
}


///////////////////////////////////////////////////////////////////////MAINMENU////////////////////////////////////////////////////////////////////////////////////

class MainMenu : public Game
{
public:
	MainMenu();
	void run();

protected:
	void processEvents();
	void update();
	void render();

private:
	Font font;
	Text text;
	RenderWindow window;
	Texture texture[N2];
	Sprite sprite[N2];
	Vector2i mouse_pos;

	bool condition;
};

MainMenu::MainMenu() : window(VideoMode(1280, 720), "MainMenu"), texture(), sprite(), font(), text()
{
	for (int i = 0; i < N2; i++)
	{
		if (!texture[i].loadFromFile(add2::A[i]))
		{
			cout << "The filename " << add2::A[i] << " could not be loaded" << endl;
		}
		sprite[i].setTexture(texture[i]);
	}

	if (!font.loadFromFile(fonts::f[0]))
	{
		cout << "The filename " << fonts::f[0] << " could not be loaded" << endl;
	}
	text.setFont(font);
	text.setString("WELCOME TO: \nGUIDE THE ROBOT");
	text.setPosition(10, 0);
	text.setCharacterSize(28);
}

void MainMenu::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void MainMenu::processEvents()
{
	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			game_state = 0;

		mouse_pos = Mouse::getPosition(window);

		if ((mouse_pos.x >= 0 && mouse_pos.x <= 99 && mouse_pos.y >= 619 && mouse_pos.y <= 719) && Mouse::isButtonPressed(Mouse::Left))
			game_state = 3;

		if ((mouse_pos.x >= 100 && mouse_pos.x <= 199 && mouse_pos.y >= 619 && mouse_pos.y <= 719) && Mouse::isButtonPressed(Mouse::Left))
			game_state = 4;

		if ((mouse_pos.x >= 1204 && mouse_pos.x <= 1279 && mouse_pos.y >= 644 && mouse_pos.y < 719) && Mouse::isButtonPressed(Mouse::Left))
			game_state = 0;
	}
}

void MainMenu::update()
{
	if (game_state != 2)
	{
		window.close();
	}
}

void MainMenu::render()
{
	window.clear();
	place_sprite(window, sprite[0], 0, 0, 0, 0);
	window.draw(text);
	window.display();
}

///////////////////////////////////////////////////////////////////////INSTRUCTIONS MENU////////////////////////////////////////////////////////////////////////////////////

class Instructions : public Game
{
public:
	Instructions();
	void run();

protected:
	void processEvents();
	void update();
	void render();

private:
	RenderWindow window;
	Texture texture[N3];
	Sprite sprite[N3];
};

Instructions::Instructions() : window(VideoMode(700, 529), "Title Window"), texture(), sprite()
{
	for (int i = 0; i < N3; i++)
	{
		if (!texture[i].loadFromFile(add3::A[i]))
		{
			cout << "The filename " << add3::A[i] << " could not be loaded" << endl;
		}
		sprite[i].setTexture(texture[i]);
	}
}

void Instructions::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Instructions::processEvents()
{
	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			game_state = 2;
	}
}

void Instructions::update()
{
	if (game_state != 3)
		window.close();
}

void Instructions::render()
{
	window.clear();
	place_sprite(window, sprite[0], 0, 0, 0, 0);
	window.display();
}


///////////////////////////////////////////////////////////////////////GAMEPLAY////////////////////////////////////////////////////////////////////////////////////

class GamePlay : public Game
{
public:
	GamePlay();
	void run();
	void levelLoad(string);

protected:
	void processEvents();
	void processEvents1();
	void processEvents2();
	void update();
	void update2();
	void render();

	void populate(Texture &, int, int, string, string);
	void populate2();
	void forward();
	int proximityCheck(int, int);
	void highLight(Texture &, int, int, int, int, int, int, int);

protected:
	RenderWindow window;
	Texture texture[N4_1];
	Sprite sprite[N4_1];
	Vector2i mouse_pos;
	Font font;
	Text text1;

	int g_state;
	int noE;
	int exit_cond;
	int shift;
	int loaded[4];
	int arr[54];
	int arr_pos;
	int rp_x, rp_y;
	int place_x, place_y;
};

GamePlay::GamePlay() : window(VideoMode(1250, 750), "Guide The Robot"), texture(), sprite()
{
	loaded[0] = 0;
	arr[56] = {};
	arr_pos = 0;
	shift = 0;
	place_x = 1;
	place_y = 2;
	exit_cond = 0;

	for (int i = 0; i < N4_1; i++)
	{
		if (!texture[i].loadFromFile(add4::A[i]))
		{
			cout << "The filename " << add4::A[i] << " could not be loaded" << endl;
		}
		sprite[i].setTexture(texture[i]);
	}
}

void GamePlay::levelLoad(string A)
{
	ifstream readlevel;
	readlevel.open(A);

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			readlevel >> level::arr_place[i][j];
		}
	}
}

void GamePlay::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void GamePlay::processEvents()
{
	Event event1;

	while (window.pollEvent(event1))
	{
		if (event1.type == Event::Closed)
			game_state = 0;

		if (shift == 0)
			processEvents1();
		else if (shift == 1)
			processEvents2();
		else if (shift == 2)
			for (int i = 18; i <= 19; i++)
				highLight(texture[i], 50 + ((i - 18) * 200), 149 + ((i - 18) * 200), 500, 549, i, i + 16, i - 17);
	}
}

void GamePlay::update()
{
	if (game_state != g_state)
		window.close();

	if (shift)
		update2();
}

void GamePlay::render()
{
	window.clear(Color::White);
	for (int i = 0; i < N4_1; i++)
		place_sprite(window, sprite[i], i + 1);
	window.draw(text1);
	window.display();
}

void GamePlay::processEvents1()
{
	for (int i = 1; i <= 6; i++)
		populate(texture[i + 2], i, 13, add4::A[i + 2], add4::A[i + 26]);

	if (place_x>1 || (place_x==1 && place_y>2))
		populate2();

	highLight(texture[2], 150, 249, 500, 549, 2, 33, 0);

	for (int i = 18; i <= 19; i++)
		highLight(texture[i], 50 + ((i - 18) * 200), 149 + ((i - 18) * 200), 500, 549, i, i + 16, i - 17);

	if (shift == 1)
	{
		texture[2].loadFromFile(add4::A[33]);

		for (int i = arr_pos; i < 48; i++)
			arr[i] = 0;

		arr_pos = 0;
	}
}

void GamePlay::processEvents2()
{

}

void GamePlay::update2()
{
	if (arr[arr_pos] == 0){
		texture[0].loadFromFile(add4::A[36]);
		shift = 2;
	}

	Sleep(500);

	int x = arr[arr_pos];

	switch (x)
	{
	case 1:
		forward();
		break;
	case 2:
		sprite[0].rotate(-90);
		break;
	case 3:
		sprite[0].rotate(90);
		break;
	case 4:
		break;
	case 5:
		if (!loaded[0])
		{
			int j = 0;

			for (int i = 0; i < 3; i++)
			{
				if (proximityCheck(i + 13, 1) == 1)
				{
					texture[0].loadFromFile(add4::A[i + 21]);
					loaded[0] = 1;
					loaded[i + 1] = 1;
					j++;
				}

			}

			if (j == 0)
			{
				texture[0].loadFromFile(add4::A[36]);
				for (int i = 0; i < 54; i++)
					arr[i] = 0;
				shift = 2;
			}
		}
		else
		{
			texture[0].loadFromFile(add4::A[36]);
			for (int i = 0; i < 54; i++)
				arr[i] = 0;
			shift = 2;
		}
		break;
	case 6:
		if (loaded[0])
		{
			int j = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((proximityCheck(i + 16, 0) == 1) && loaded[i + 1] == 1)
				{
					texture[0].loadFromFile(add4::A[0]);
					texture[i + 15].loadFromFile(add4::A[i + 24]);
					loaded[0] = 0;
					loaded[i + 1] = 2;
					exit_cond++;
					j++;
				}

			}
			if (j == 0)
			{
				texture[0].loadFromFile(add4::A[36]);
				for (int i = 0; i < 54; i++)
					arr[i] = 0;
				shift = 2;
			}
		}
		else
		{
			texture[0].loadFromFile(add4::A[36]);
			for (int i = 0; i < 54; i++)
				arr[i] = 0;
			shift = 2;
		}
		break;
	}

	if (exit_cond == noE)
	{
		texture[20].loadFromFile(add4::A[37]);
		exit_cond = 15;
	}

	arr_pos++;
}

void GamePlay::populate(Texture &texture, int x, int y, string nor, string hig)
{
	int p1 = (x * 50) + 25, p2 = ((y - 1) * 50) + 25;
	mouse_pos = Mouse::getPosition(window);

	if (mouse_pos.x >= (p1 - 24) && mouse_pos.x <= (p1 + 24) && mouse_pos.y >= (p2 - 24) && mouse_pos.y <= (p2 + 24))
	{
		texture.loadFromFile(hig);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			level::arr_place[place_x][place_y] = x + 3;

			place_x++;
			if (place_x > 6)
			{
				place_y++;
				place_x = 1;
			}

			if (place_y > 10)
			{
				shift = 1;
				texture.loadFromFile(nor);
			}

			arr[arr_pos] = x;
			arr_pos++;
		}
	}
	else
		texture.loadFromFile(nor);
}

void GamePlay::populate2()
{
	int x = place_x - 1, y = place_y;

	if (x < 1)
	{
		x = 6;
		y = place_y - 1;
	}

	int p1 = (x * 50) + 25, p2 = ((y - 1) * 50) + 25;

	if (mouse_pos.x >= (p1 - 24) && mouse_pos.x <= (p1 + 24) && mouse_pos.y >= (p2 - 24) && mouse_pos.y <= (p2 + 24))
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			level::arr_place[x][y] = 0;

			place_x = x;
			place_y = y;

			arr[--arr_pos] = 0;

		}
	}
}

void GamePlay::forward(){

	int tempx = rp_x, tempy = rp_y;

	level::arr_place[rp_x][rp_y] = 0;

	int angle = sprite[0].getRotation();

	int temp;

	switch (angle)
	{
	case 0:
		temp = level::arr_place[rp_x][rp_y - 1];
		level::arr_place[rp_x][--rp_y] = 1;
		break;
	case 90:
		temp = level::arr_place[rp_x + 1][rp_y];
		level::arr_place[++rp_x][rp_y] = 1;
		break;
	case 180:
		temp = level::arr_place[rp_x][rp_y + 1];
		level::arr_place[rp_x][++rp_y] = 1;
		break;
	case 270:
		temp = level::arr_place[rp_x - 1][rp_y];
		level::arr_place[--rp_x][rp_y] = 1;
		break;
	}

	if (no_go::arr[rp_x][rp_y] == 1)
	{
		texture[0].loadFromFile(add4::A[36]);
		for (int i = 0; i < 54; i++)
			arr[i] = 0;
		shift = 2;
		level::arr_place[rp_x][rp_y] = temp;
		rp_x = tempx;
		rp_y = tempy;
		level::arr_place[rp_x][rp_y] = 1;
	}
	else if (no_go::arr[rp_x][rp_y] == 2 && exit_cond == 15)
	{
		game_state++;
	}
}

int GamePlay::proximityCheck(int code, int cond)
{
	int angle = sprite[0].getRotation();

	switch (angle)
	{
	case 0:
		if (level::arr_place[rp_x][rp_y - 1] == code)
		{
			if (cond == 1)
			{
				level::arr_place[rp_x][rp_y - 1] = 0;
				no_go::arr[rp_x][rp_y - 1] = 0;
			}
			return 1;
		}

		break;
	case 90:
		if (level::arr_place[rp_x + 1][rp_y] == code)
		{
			if (cond == 1)
			{
				level::arr_place[rp_x + 1][rp_y] = 0;
				no_go::arr[rp_x + 1][rp_y] = 0;
			}
			return 1;
		}

		break;
	case 180:
		if (level::arr_place[rp_x][rp_y + 1] == code)
		{
			if (cond == 1)
			{
				level::arr_place[rp_x][rp_y + 1] = 0;
				no_go::arr[rp_x][rp_y + 1] = 0;
			}
			return 1;
		}
		break;
	case 270:
		if (level::arr_place[rp_x - 1][rp_y] == code)
		{
			if (cond == 1)
			{
				level::arr_place[rp_x - 1][rp_y] = 0;
				no_go::arr[rp_x - 1][rp_y] = 0;
			}
			return 1;
		}
		break;
	}
	return 0;
}

void GamePlay::highLight(Texture &texture, int xi, int xf, int yi, int yf, int nor, int hig, int cond)
{
	mouse_pos = Mouse::getPosition(window);

	if (mouse_pos.x >= xi && mouse_pos.x <= xf && mouse_pos.y >= yi && mouse_pos.y <= yf)
	{
		texture.loadFromFile(add4::A[hig]);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (cond)
			{
			case 0:
				shift = 1;
				break;
			case 1:
				game_state = 2;
				break;
			case 2:
				window.close();
			default:
				break;
			}
		}

	}
	else
		texture.loadFromFile(add4::A[nor]);
}

///////////////////////////////////////////////////////////////////////LEVEL 1////////////////////////////////////////////////////////////////////////////////////

class LevelOne : public GamePlay
{
public:
	LevelOne();
};

LevelOne::LevelOne()
{
	noE = 0;
	g_state = 4;

	if (!font.loadFromFile(fonts::f[0]))
	{
		cout << "The filename " << fonts::f[0] << " could not be loaded" << endl;
	}
	text1.setFont(font);
	text1.setString("LEVEL 1");
	text1.setColor(Color::Black);
	text1.setPosition(10, 0);
	text1.setCharacterSize(34);

	levelLoad(levelFiles::A[0]);

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (level::arr_place[i][j] == 1)
			{
				rp_x = i;
				rp_y = j;
				break;

			}

			if (level::arr_place[i][j] >= 13 && level::arr_place[i][j] <= 15)
			{
				noE++;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////LEVEL 2////////////////////////////////////////////////////////////////////////////////////

class LevelTwo : public GamePlay
{
public:
	LevelTwo();
};

LevelTwo::LevelTwo()
{
	noE = 0;
	g_state = 5;

	if (!font.loadFromFile(fonts::f[0]))
	{
		cout << "The filename " << fonts::f[0] << " could not be loaded" << endl;
	}
	text1.setFont(font);
	text1.setString("LEVEL 2");
	text1.setColor(Color::Black);
	text1.setPosition(10, 0);
	text1.setCharacterSize(34);

	levelLoad(levelFiles::A[1]);

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (level::arr_place[i][j] == 1)
			{
				rp_x = i;
				rp_y = j;
				break;
			}

			if (level::arr_place[i][j] >= 13 && level::arr_place[i][j] <= 15)
			{
				noE++;
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////LEVEL 3////////////////////////////////////////////////////////////////////////////////////

class LevelThree : public GamePlay
{
public:
	LevelThree();
};

LevelThree::LevelThree()
{
	noE = 0;
	g_state = 6;

	if (!font.loadFromFile(fonts::f[0]))
	{
		cout << "The filename " << fonts::f[0] << " could not be loaded" << endl;
	}
	text1.setFont(font);
	text1.setString("LEVEL 3");
	text1.setColor(Color::Black);
	text1.setPosition(10, 0);
	text1.setCharacterSize(34);

	levelLoad(levelFiles::A[0]);

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (level::arr_place[i][j] == 1)
			{
				rp_x = i;
				rp_y = j;
				break;

			}
			if (level::arr_place[i][j] >= 13 && level::arr_place[i][j] <= 15)
			{
				noE++;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////////////////////

int main()
{

	Game* game;

	while (game_state)
	{
		switch (game_state)
		{
		case 1:
			game = new TitleWindow();
			game->run();
			break;
		case 2:
			game = new MainMenu();
			game->run();
			break;
		case 3:
			game = new Instructions();
			game->run();
			break;
		case 4:
			game = new LevelOne();
			game->run();
			break;
		case 5:
			game = new LevelTwo();
			game->run();
			break;
		case 6:
			game = new LevelThree();
			game->run();
			break;
		case 7:
			break;
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////THE END////////////////////////////////////////////////////////////////////////////////////
