#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const short areaWidth = 30;
const short areaHeight = 20;

short area[areaWidth][areaHeight];
bool areaStatus[areaWidth][areaHeight];
bool areaMarker[areaWidth][areaHeight];

bool gameEnd = false;

void restart() {
	for (int j = 0; j < areaHeight; j++)
		for (int i = 0; i < areaWidth; i++) {
			area[i][j] = 0;
			areaStatus[i][j] = 0;
			areaMarker[i][j] = 0;
		}
	for (int j = 0; j < areaHeight; j++)
		for (int i = 0; i < areaWidth; i++) {
			if (rand() % 10 == 1) {
				area[i][j] = 1;
				if (i + 1 < areaWidth)                       if (area[i + 1][j] != 1)     if (area[i + 1][j] == 0)     area[i + 1][j] = 2;     else area[i + 1][j]++;
				if (i + 1 < areaWidth && j + 1 < areaHeight) if (area[i + 1][j + 1] != 1) if (area[i + 1][j + 1] == 0) area[i + 1][j + 1] = 2; else area[i + 1][j + 1]++;
				if (j + 1 < areaHeight)                      if (area[i][j + 1] != 1)     if (area[i][j + 1] == 0)     area[i][j + 1] = 2;     else area[i][j + 1]++;
				if (i > 0 && j + 1 < areaHeight)             if (area[i - 1][j + 1] != 1) if (area[i - 1][j + 1] == 0) area[i - 1][j + 1] = 2; else area[i - 1][j + 1]++;
				if (i > 0)                                   if (area[i - 1][j] != 1)     if (area[i - 1][j] == 0)     area[i - 1][j] = 2;     else area[i - 1][j]++;
				if (i > 0 && j > 0)                          if (area[i - 1][j - 1] != 1) if (area[i - 1][j - 1] == 0) area[i - 1][j - 1] = 2; else area[i - 1][j - 1]++;
				if (j > 0)                                   if (area[i][j - 1] != 1)     if (area[i][j - 1] == 0)     area[i][j - 1] = 2;     else area[i][j - 1]++;
				if (i + 1 < areaWidth && j > 0)              if (area[i + 1][j - 1] != 1) if (area[i + 1][j - 1] == 0) area[i + 1][j - 1] = 2; else area[i + 1][j - 1]++;
			}
		}
}

bool zalivka(unsigned short x, unsigned short y) {
	if (area[x][y] > 0 || areaStatus[x][y]) return 0;
	areaStatus[x][y] = 1;
	areaMarker[x][y] = 0;

	if (area[x][y] == 0) {
		if (x + 1 < areaWidth)                       if (!areaStatus[x + 1][y])       if (area[x + 1][y] > 1) { areaStatus[x + 1][y] = 1;     areaMarker[x + 1][y] = 0; }
		if (x + 1 < areaWidth && y + 1 < areaHeight) if (!areaStatus[x + 1][y + 1])   if (area[x + 1][y + 1] > 1) { areaStatus[x + 1][y + 1] = 1; areaMarker[x + 1][y + 1] = 0; }
		if (y + 1 < areaHeight)                      if (!areaStatus[x][y + 1])       if (area[x][y + 1] > 1) { areaStatus[x][y + 1] = 1;     areaMarker[x][y + 1] = 0; }
		if (y > 0 && y + 1 < areaHeight)             if (!areaStatus[x - 1][y + 1])   if (area[x - 1][y + 1] > 1) { areaStatus[x - 1][y + 1] = 1; areaMarker[x - 1][y + 1] = 0; }
		if (x > 0)                                   if (!areaStatus[x - 1][y])       if (area[x - 1][y] > 1) { areaStatus[x - 1][y] = 1;     areaMarker[x - 1][y] = 0; }
		if (x > 0 && y > 0)                          if (!areaStatus[x - 1][y - 1])   if (area[x - 1][y - 1] > 1) { areaStatus[x - 1][y - 1] = 1; areaMarker[x - 1][y - 1] = 0; }
		if (y > 0)                                   if (!areaStatus[x][y - 1])       if (area[x][y - 1] > 1) { areaStatus[x][y - 1] = 1;     areaMarker[x][y - 1] = 0; }
		if (x + 1 < areaWidth && y > 0)              if (!areaStatus[x + 1][y - 1])   if (area[x + 1][y - 1] > 1) { areaStatus[x + 1][y - 1] = 1; areaMarker[x + 1][y - 1] = 0; }
	}
	if (x > 0)              zalivka(x - 1, y);
	if (x + 1 < areaWidth)  zalivka(x + 1, y);
	if (y > 0)              zalivka(x, y - 1);
	if (y + 1 < areaHeight) zalivka(x, y + 1);
	/*
	if (x + 1 < areaWidth && y < 0) zalivka(x + 1, y - 1);
	if (y + 1 < areaHeight && x < 0) zalivka(x - 1, y + 1);
	if (x < 0 && y < 0) zalivka(x - 1, y - 1);
	if (x + 1 < areaWidth && y + 1 < areaHeight) zalivka(x + 1, y + 1);
	*/
	return 1;
}

bool checkWin() {
	for (int j = 0; j < areaHeight; j++)
		for (int i = 0; i < areaWidth; i++) {
			if ((area[i][j] > 1 || area[i][j] == 0) && areaStatus[i][j] == 0) return 0;//тест на открытые свободные €чейки
		}
	gameEnd = 1;
	return 1;
}

bool checkDefeat(unsigned int x, unsigned int y) {
	if(x > 0 && y > 0 && x < areaWidth && y < areaHeight)
		if (area[x][y] == 1 && areaStatus[x][y]) {
			for (int j = 0; j < areaHeight; j++)
				for (int i = 0; i < areaWidth; i++) {
					if (area[i][j] == 1)areaStatus[i][j] = 1;
				}
			gameEnd = 1;
			return 1;
		}
	return 0;
}

int main()
{
	RenderWindow window(VideoMode(1280, 960), "Minesweeper");
	const short cellSize = 32;
	const short infoSize = 50;

	Image iClosed;
	iClosed.loadFromFile("closed.png");
	Texture tClosed;
	tClosed.loadFromImage(iClosed);
	Sprite sClosed;
	sClosed.setTexture(tClosed);
	sClosed.setScale(cellSize / 32.0, cellSize / 32.0);

	Image iOpened;
	iOpened.loadFromFile("opened.png");
	Texture tOpened;
	tOpened.loadFromImage(iOpened);
	Sprite sOpened;
	sOpened.setTexture(tOpened);
	sOpened.setScale(cellSize / 32.0, cellSize / 32.0);

	Image iBomb;
	iBomb.loadFromFile("bomb.png");
	iBomb.createMaskFromColor(Color::White);
	Texture tBomb;
	tBomb.loadFromImage(iBomb);
	Sprite sBomb;
	sBomb.setTexture(tBomb);
	sBomb.setScale(cellSize / 32.0, cellSize / 32.0);

	Image iMarker;
	iMarker.loadFromFile("marker.png");
	iMarker.createMaskFromColor(Color::White);
	Texture tMarker;
	tMarker.loadFromImage(iMarker);
	Sprite sMarker;
	sMarker.setTexture(tMarker);
	sMarker.setScale(cellSize / 32.0, cellSize / 32.0);

	Font font;
	font.loadFromFile("font.TTF");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::Green);
	text.setCharacterSize(cellSize - 1);

	Vector2i mousePos;
	Vector2i mouseCell;

	srand(time(0));
	restart();
	/*for (int j = 0; j < areaHeight; j++) {
		for (int i = 0; i < areaWidth; i++) {
			cout << area[i][j];
		}
		cout << endl;
	}*/

	while (window.isOpen())
	{
		mousePos = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type = Event::KeyPressed)
				if (Keyboard::isKeyPressed(Keyboard::F2)) {
					restart(); gameEnd = 0;
				}
			if(event.type = Event::MouseButtonPressed)
				if (!gameEnd) {
					mouseCell.x = mousePos.x / cellSize;
					mouseCell.y = (mousePos.y - infoSize) / cellSize;
					if (mouseCell.x < areaWidth && mouseCell.y < areaHeight && mousePos.x >= 0 && mousePos.y >= infoSize) {
						if (Mouse::isButtonPressed(Mouse::Left)) { zalivka(mouseCell.x, mouseCell.y); areaStatus[mouseCell.x][mouseCell.y] = 1; areaMarker[mouseCell.x][mouseCell.y] = 0; if (checkWin()) { cout << "You win!" << endl << "Press F2 to start new game." << endl; } if (checkDefeat(mouseCell.x, mouseCell.y)) { cout << "You defeat!" << endl << "Press F2 to start new game." << endl; } }
						if (Mouse::isButtonPressed(Mouse::Right)) { if (areaMarker[mouseCell.x][mouseCell.y]) areaMarker[mouseCell.x][mouseCell.y] = 0; else if (!areaStatus[mouseCell.x][mouseCell.y]) areaMarker[mouseCell.x][mouseCell.y] = 1; }
					}
				}
		}

		window.clear();
		for (int j = 0; j < areaHeight; j++)
			for (int i = 0; i < areaWidth; i++) {
				if (areaStatus[i][j]) {
					sOpened.setPosition(i * cellSize, j * cellSize + infoSize);
					window.draw(sOpened);
					if (area[i][j] > 1) {
						text.setString(std::to_string(area[i][j] - 1));
						text.setPosition(i * cellSize + 4, j * cellSize + infoSize);
						window.draw(text);
					}
					else if (area[i][j]) {
						sBomb.setPosition(i * cellSize, j * cellSize + infoSize);
						window.draw(sBomb);
					}
				}
				else {
					sClosed.setPosition(i * cellSize, j * cellSize + infoSize);
					window.draw(sClosed);
				}
				if (areaMarker[i][j]) {
					sMarker.setPosition(i * cellSize, j * cellSize + infoSize);
					window.draw(sMarker);
				}
			}

		window.display();
	}

	return 0;
}