#include <iostream>
#include <stdint.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

static const int GRID_SQUARES_COUNT = 140;
static const int GRID_POINTS_COUNT = 165;
static const int ROW_COUNT = 11;
static const int COL_COUNT = 15;

int points[GRID_POINTS_COUNT] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0,
};


uint8_t upperPoint(int row, int col)
{
	return points[(row - 1) * COL_COUNT + col];
}

uint8_t lowerPoint(int row, int col)
{
	return points[(row + 1) * COL_COUNT + col];
}

uint8_t leftPoint(int row, int col)
{
	return points[row * COL_COUNT + (col - 1)];
}

uint8_t rightPoint(int row, int col)
{
	return points[row * COL_COUNT + (col + 1)];
}

uint8_t rightDiagonalPoint(int row, int col)
{
	return points[(row + 1) * COL_COUNT + (col + 1)];
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lines Test!");

    sf::Texture background;
    background.loadFromFile("bgr.png");
    sf::Sprite sprite;
    sprite.setTexture(background);

    //65 48 upper left x, upper left y
    sf::Vector2i dotCoordinates(65,48);
    sf::Vector2i dotSize(20,20);

    // 119 60
    sf::Vector2i lineCoordinates(72, 55);
    sf::Vector2i lineSize(46, 4);

    sf::Vector2i linesVerticalCoordinates(72,55);

    sf::Vector2i squaresCoordinates(74, 58);
    sf::Vector2i squareSize(45,48);

    sf::Rect<int> grid[GRID_POINTS_COUNT];

    sf::Rect<int> verticalLinesGrid[150];

    sf::Rect<int> squaresGrid[GRID_SQUARES_COUNT];

    sf::Texture blueDots;
    sf::Texture blueLines;
    sf::Texture blueSquares;
    blueDots.loadFromFile("blue_dots.png");
    blueLines.loadFromFile("blue_lines.png");
    blueSquares.loadFromFile("blue_squares.png");
    sf::Sprite blueDotsSprite[GRID_POINTS_COUNT];
    sf::Sprite blueHorizontalLinesSprite[GRID_POINTS_COUNT];
    sf::Sprite blueVerticalLinesSprite[GRID_POINTS_COUNT];

    sf::Sprite blueSquaresSprite[GRID_SQUARES_COUNT];

    // initializing the squares
    for (int row = 0; row < ROW_COUNT; ++row)
    {
    	for (int col = 0; col < COL_COUNT; ++col)
    	{
        	int squareIndex = row * COL_COUNT + col;

        	if(col != 14){
            	blueSquaresSprite[squareIndex].setTexture(blueSquares);
            	blueSquaresSprite[squareIndex].setTextureRect(sf::IntRect(squaresCoordinates.x, squaresCoordinates.y, squareSize.x, squareSize.y));

            	squaresGrid[squareIndex].left = squaresCoordinates.x;
            	squaresGrid[squareIndex].top = squaresCoordinates.y;

            	squaresGrid[squareIndex].width = squareSize.x;
            	squaresGrid[squareIndex].height = squareSize.y;

            	squaresCoordinates.x += 46;
        	}

        	if(col == 14 && squareIndex != 0)
        	{
        		squaresCoordinates.x = 74;
        		squaresCoordinates.y += 49;
        	}
    	}
    }

    // initialize dots and horizontal lines
    for (int row = 0; row < ROW_COUNT; ++row)
    {
    	for (int col = 0; col < COL_COUNT; ++col)
    	{
        	int arrIndex = row * COL_COUNT + col;
        	// dots
            blueDotsSprite[arrIndex].setTexture(blueDots);
            blueDotsSprite[arrIndex].setTextureRect(sf::IntRect(dotCoordinates.x, dotCoordinates.y, dotSize.x, dotSize.y));


            // horizontal lines
            blueHorizontalLinesSprite[arrIndex].setTexture(blueLines);
            blueHorizontalLinesSprite[arrIndex].setTextureRect(sf::IntRect(lineCoordinates.x, lineCoordinates.y, lineSize.x, lineSize.y));

        	grid[arrIndex].left = dotCoordinates.x;
        	grid[arrIndex].top = dotCoordinates.y;

        	grid[arrIndex].width = dotSize.x;
        	grid[arrIndex].height = dotSize.y;

        	dotCoordinates.x += 46;
        	lineCoordinates.x += 46;

        	if(col == 14 && arrIndex != 0)
        	{
        		dotCoordinates.y += 49;
        		dotCoordinates.x = 65;

        		lineCoordinates.y += 49;
        		lineCoordinates.x = 65;
        	}
    	}
	}

    // initializing the vertical lines
    for (int row = 0; row < ROW_COUNT - 1; ++row)
    {
    	for (int col = 0; col < COL_COUNT; ++col)
    	{
        	int lineIndex = row * COL_COUNT + col;

            // vertical lines
            blueVerticalLinesSprite[lineIndex].setTexture(blueLines);
            blueVerticalLinesSprite[lineIndex].setTextureRect(sf::IntRect(linesVerticalCoordinates.x, linesVerticalCoordinates.y, 3, 50));

        	verticalLinesGrid[lineIndex].left = linesVerticalCoordinates.x;
        	verticalLinesGrid[lineIndex].top = linesVerticalCoordinates.y;

        	verticalLinesGrid[lineIndex].width = 3;
        	verticalLinesGrid[lineIndex].height = 50;

        	linesVerticalCoordinates.x += 46;

        	if(col == 14 && lineIndex != 0)
        	{
        		linesVerticalCoordinates.y += 49;
        		linesVerticalCoordinates.x = 72;
        	}
    	}
    }



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
            	if(event.mouseButton.button == sf::Mouse::Left)
            	{
        	        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
        	        std::cout << "mouse y: " << event.mouseButton.y << std::endl;

        	        for (int row = 0; row < ROW_COUNT; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT; ++col)
        	        	{
            	        	int arrIndex = row * COL_COUNT + col;
                    		if(grid[arrIndex].contains(event.mouseButton.x, event.mouseButton.y))
                    		{
                    			if(points[arrIndex] == 0){
                        			blueDotsSprite[arrIndex].setPosition(grid[arrIndex].left, grid[arrIndex].top);

                        			points[arrIndex] = 1;
                    			}
                    		}
        	        	}
        	        }

        	        // loop for setting the horizontal lines
        	        for (int row = 0; row < ROW_COUNT; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT; ++col)
        	        	{
        	        		int arrIndex = row * COL_COUNT + col;
        	        		if(points[arrIndex] && rightPoint(row, col)){
        	         			blueHorizontalLinesSprite[arrIndex].setPosition(grid[arrIndex].left, grid[arrIndex].top + 7);
        	        		}

        	        	}
        	        }

        	        // loop for setting the vertical lines
        	        for (int row = 0; row < ROW_COUNT - 1; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT; ++col)
        	        	{
        	        		int arrIndex = row * COL_COUNT + col;

        	        		if(points[arrIndex] && lowerPoint(row, col)){
            	        		blueVerticalLinesSprite[arrIndex].setPosition(verticalLinesGrid[arrIndex].left, verticalLinesGrid[arrIndex].top);
        	        		}

        	        	}
        	        }

        	        // loop for setting the squares
        	        for (int row = 0; row < ROW_COUNT; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT; ++col)
        	        	{
        	            	int squareIndex = row * COL_COUNT + col;
        	            	if(points[squareIndex] && lowerPoint(row, col) && rightPoint(row, col) && rightDiagonalPoint(row, col)){

        	            	}
    	            		blueSquaresSprite[squareIndex].setPosition(squaresGrid[squareIndex].left, squaresGrid[squareIndex].top);
        	        	}
        	        }
            	}
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // draw background
        window.draw(sprite);

        // draw dots and lines
        for (int row = 0; row < ROW_COUNT; ++row)
        {
        	for (int col = 0; col < COL_COUNT; ++col)
        	{
        		int arrIndex = row * COL_COUNT + col;
            	if(blueDotsSprite[arrIndex].getPosition() != sf::Vector2f()){
            		window.draw(blueDotsSprite[arrIndex]);
            	}
            	if(blueHorizontalLinesSprite[arrIndex].getPosition() != sf::Vector2f()){
            		window.draw(blueHorizontalLinesSprite[arrIndex]);
            	}
            	if(blueVerticalLinesSprite[arrIndex].getPosition() != sf::Vector2f()){
            		window.draw(blueVerticalLinesSprite[arrIndex]);
            	}

            	if(blueSquaresSprite[arrIndex].getPosition() != sf::Vector2f()){
            		window.draw(blueSquaresSprite[arrIndex]);
            	}
        	}
		}

        // PRINT POINTS ARRAY FOR TEST
        for (int row = 0; row < ROW_COUNT; ++row)
        {
        	for (int col = 0; col < COL_COUNT; ++col)
        	{
        		int arrIndex = row * COL_COUNT + col;
        		std::cout << points[arrIndex] << " ";
        	}
        	std::cout << std::endl;
        }
    	std::cout << "=============================================" << std::endl;

        // draw the squares
        for (int row = 0; row < ROW_COUNT; ++row)
        {
        	for (int col = 0; col < COL_COUNT; ++col)
        	{
            	int squareIndex = row * COL_COUNT + col;

        	}
        }

        window.display();
    }

    return 0;
}
