#include <iostream>
#include <stdint.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

static const int GRID_POINTS_COUNT = 165;
static const int ROW_COUNT = 11;
static const int COL_COUNT = 15;

enum STATE_CURRENT_PLAYER
{
	BLUE,
	RED
};

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


int pointsRed[GRID_POINTS_COUNT] =
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


const uint8_t upperPoint(int row, int col)
{
	return points[(row - 1) * COL_COUNT + col];
}

const uint8_t lowerPoint(int row, int col)
{
	return points[(row + 1) * COL_COUNT + col];
}

const uint8_t leftPoint(int row, int col)
{
	return points[row * COL_COUNT + (col - 1)];
}

const uint8_t rightPoint(int row, int col)
{
	return points[row * COL_COUNT + (col + 1)];
}

const uint8_t rightDiagonalPoint(int row, int col)
{
	return points[(row + 1) * COL_COUNT + (col + 1)];
}



const uint8_t upperRedPoint(int row, int col)
{
	return pointsRed[(row - 1) * COL_COUNT + col];
}

const uint8_t lowerRedPoint(int row, int col)
{
	return pointsRed[(row + 1) * COL_COUNT + col];
}

const uint8_t leftRedPoint(int row, int col)
{
	return pointsRed[row * COL_COUNT + (col - 1)];
}

const uint8_t rightRedPoint(int row, int col)
{
	return pointsRed[row * COL_COUNT + (col + 1)];
}

const uint8_t rightRedDiagonalPoint(int row, int col)
{
	return pointsRed[(row + 1) * COL_COUNT + (col + 1)];
}



bool checkForLine(int arrIndex)
{
	if(points[arrIndex] && points[arrIndex - COL_COUNT])
	{
		return true;
	}
	if(points[arrIndex] && points[arrIndex + COL_COUNT])
	{
		return true;
	}
	if(points[arrIndex] && points[arrIndex - 1])
	{
		return true;
	}
	if(points[arrIndex] && points[arrIndex + 1])
	{
		return true;
	}

    return false;
}

bool checkForRedLine(int arrIndex)
{
	if(pointsRed[arrIndex] && pointsRed[arrIndex - COL_COUNT])
	{
		return true;
	}
	if(pointsRed[arrIndex] && pointsRed[arrIndex + COL_COUNT])
	{
		return true;
	}
	if(pointsRed[arrIndex] && pointsRed[arrIndex - 1])
	{
		return true;
	}
	if(pointsRed[arrIndex] && pointsRed[arrIndex + 1])
	{
		return true;
	}

    return false;
}


bool checkForSquare(int arrIndex)
{
	/*		-----------
	 * 		|	 |	  |
	 * 		|	 |	  |
	 * 		-----*-----
	 * 		|	 |	  |
	 * 		|	 |	  |
	 * 		-----------
	 * 		check for the current index (point) for left, right lowerLeft or lowerRight square formed
	 */

	bool leftSquare = points[arrIndex] && points[arrIndex - COL_COUNT] && points[arrIndex - 1] && points[(arrIndex - COL_COUNT) - 1];
	bool rightSquare = points[arrIndex] && points[arrIndex - COL_COUNT] && points[arrIndex - 1] && points[(arrIndex - COL_COUNT) - 1];

	bool lowerRightSquare = points[arrIndex] && points[arrIndex + COL_COUNT] && points[arrIndex + 1] && points[(arrIndex + COL_COUNT) + 1];
	bool lowerLeftSquare = points[arrIndex] && points[arrIndex + COL_COUNT] && points[arrIndex - 1] && points[(arrIndex + COL_COUNT) - 1];

    return leftSquare || rightSquare || lowerRightSquare || lowerLeftSquare;
}


bool checkForRedSquare(int arrIndex)
{
	/*		-----------
	 * 		|	 |	  |
	 * 		|	 |	  |
	 * 		-----*-----
	 * 		|	 |	  |
	 * 		|	 |	  |
	 * 		-----------
	 * 		check for the current index (point) for left, right lowerLeft or lowerRight square formed
	 */

	bool leftSquare = pointsRed[arrIndex] && pointsRed[arrIndex - COL_COUNT] && pointsRed[arrIndex - 1] && pointsRed[(arrIndex - COL_COUNT) - 1];
	bool rightSquare = pointsRed[arrIndex] && pointsRed[arrIndex - COL_COUNT] && pointsRed[arrIndex - 1] && pointsRed[(arrIndex - COL_COUNT) - 1];

	bool lowerRightSquare = pointsRed[arrIndex] && pointsRed[arrIndex + COL_COUNT] && pointsRed[arrIndex + 1] && pointsRed[(arrIndex + COL_COUNT) + 1];
	bool lowerLeftSquare = pointsRed[arrIndex] && pointsRed[arrIndex + COL_COUNT] && pointsRed[arrIndex - 1] && pointsRed[(arrIndex + COL_COUNT) - 1];

    return leftSquare || rightSquare || lowerRightSquare || lowerLeftSquare;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lines Test!");

    sf::Texture background;
    background.loadFromFile("src/bgr.png");
    sf::Sprite sprite;
    sprite.setTexture(background);

    //65 50 upper left x, upper left y
    sf::Vector2i dotCoordinates(65,50);
    sf::Vector2i dotSize(16,16);

    sf::Vector2i lineHorizontalCoordinates(72, 57);
    sf::Vector2i linesVerticalCoordinates(72,55);
    sf::Vector2i lineSize(46, 3);

    sf::Vector2i squaresCoordinates(75, 60);
    sf::Vector2i squareSize(43,46);

    sf::Rect<int> grid[GRID_POINTS_COUNT];
    sf::Rect<int> horizontalLinesGrid[GRID_POINTS_COUNT];
    sf::Rect<int> verticalLinesGrid[GRID_POINTS_COUNT];
    sf::Rect<int> squaresGrid[GRID_POINTS_COUNT];

    sf::Texture blueDots;
    sf::Texture blueLines;
    sf::Texture blueSquares;
    blueDots.loadFromFile("src/blue_dots.png");
    blueLines.loadFromFile("src/lines_blue_2.png");
    blueSquares.loadFromFile("src/blue_squares.png");
    sf::Sprite blueDotsSprite[GRID_POINTS_COUNT];
    sf::Sprite blueHorizontalLinesSprite[GRID_POINTS_COUNT];
    sf::Sprite blueVerticalLinesSprite[GRID_POINTS_COUNT];
    sf::Sprite blueSquaresSprite[GRID_POINTS_COUNT];



    sf::Texture redDots;
    sf::Texture redLines;
    sf::Texture redSquares;
    redDots.loadFromFile("src/red_dots.png");
    redLines.loadFromFile("src/lines_red_2.png");
    redSquares.loadFromFile("src/red_squares.png");
    sf::Sprite redDotsSprite[GRID_POINTS_COUNT];
    sf::Sprite redHorizontalLinesSprite[GRID_POINTS_COUNT];
    sf::Sprite redVerticalLinesSprite[GRID_POINTS_COUNT];
    sf::Sprite redSquaresSprite[GRID_POINTS_COUNT];

    STATE_CURRENT_PLAYER playerState = BLUE;

    // initializing the squares
    for (int row = 0; row < ROW_COUNT - 1; ++row)
    {
    	for (int col = 0; col < COL_COUNT - 1; ++col)
    	{
        	int squareIndex = row * COL_COUNT + col;
			blueSquaresSprite[squareIndex].setTexture(blueSquares);
			blueSquaresSprite[squareIndex].setTextureRect(sf::IntRect(squaresCoordinates.x, squaresCoordinates.y, squareSize.x, squareSize.y));

			redSquaresSprite[squareIndex].setTexture(redSquares);
			redSquaresSprite[squareIndex].setTextureRect(sf::IntRect(squaresCoordinates.x, squaresCoordinates.y, squareSize.x, squareSize.y));

			squaresGrid[squareIndex].left = squaresCoordinates.x;
			squaresGrid[squareIndex].top = squaresCoordinates.y;

			squaresGrid[squareIndex].width = squareSize.x;
			squaresGrid[squareIndex].height = squareSize.y;

			squaresCoordinates.x += 46;

        	if(col == 13 && squareIndex != 0)
        	{
        		squaresCoordinates.x = 75;
        		squaresCoordinates.y += 49;
        	}
    	}
    }


    // initialize horizontal lines
    for (int row = 0; row < ROW_COUNT; ++row)
    {
    	for (int col = 0; col < COL_COUNT - 1; ++col)
    	{
        	int arrIndex = row * COL_COUNT + col;

            // horizontal lines
            blueHorizontalLinesSprite[arrIndex].setTexture(blueLines);
            blueHorizontalLinesSprite[arrIndex].setTextureRect(sf::IntRect(lineHorizontalCoordinates.x, lineHorizontalCoordinates.y, lineSize.x, lineSize.y));

            redHorizontalLinesSprite[arrIndex].setTexture(redLines);
            redHorizontalLinesSprite[arrIndex].setTextureRect(sf::IntRect(lineHorizontalCoordinates.x, lineHorizontalCoordinates.y, lineSize.x, lineSize.y));

            horizontalLinesGrid[arrIndex].left = lineHorizontalCoordinates.x;
			horizontalLinesGrid[arrIndex].top =  lineHorizontalCoordinates.y;
			horizontalLinesGrid[arrIndex].width = 46;
			horizontalLinesGrid[arrIndex].height = 3;

			lineHorizontalCoordinates.x += 46;

        	if(col == 13 && arrIndex != 0)
        	{
        		lineHorizontalCoordinates.y += 49;
        		lineHorizontalCoordinates.x = 72;
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
            blueVerticalLinesSprite[lineIndex].setTextureRect(sf::IntRect(linesVerticalCoordinates.x, linesVerticalCoordinates.y, 3, 46));

            redVerticalLinesSprite[lineIndex].setTexture(redLines);
            redVerticalLinesSprite[lineIndex].setTextureRect(sf::IntRect(linesVerticalCoordinates.x, linesVerticalCoordinates.y, 3, 46));

        	verticalLinesGrid[lineIndex].left = linesVerticalCoordinates.x;
        	verticalLinesGrid[lineIndex].top = linesVerticalCoordinates.y;

        	verticalLinesGrid[lineIndex].width = 3;
        	verticalLinesGrid[lineIndex].height = 46;

        	linesVerticalCoordinates.x += 46;

        	if(col == 14 && lineIndex != 0)
        	{
        		linesVerticalCoordinates.y += 49;
        		linesVerticalCoordinates.x = 72;
        	}
    	}
    }

    // initialize dots
    for (int row = 0; row < ROW_COUNT; ++row)
    {
    	for (int col = 0; col < COL_COUNT; ++col)
    	{
        	int arrIndex = row * COL_COUNT + col;
        	// dots
            blueDotsSprite[arrIndex].setTexture(blueDots);
            blueDotsSprite[arrIndex].setTextureRect(sf::IntRect(dotCoordinates.x, dotCoordinates.y, dotSize.x, dotSize.y));

            redDotsSprite[arrIndex].setTexture(redDots);
            redDotsSprite[arrIndex].setTextureRect(sf::IntRect(dotCoordinates.x, dotCoordinates.y, dotSize.x, dotSize.y));

        	grid[arrIndex].left = dotCoordinates.x;
        	grid[arrIndex].top = dotCoordinates.y;

        	grid[arrIndex].width = dotSize.x;
        	grid[arrIndex].height = dotSize.y;

        	dotCoordinates.x += 46;

        	if(col == 14 && arrIndex != 0)
        	{
        		dotCoordinates.y += 49;
        		dotCoordinates.x = 65;
        	}
    	}
	}
	int prevPointIndex = -1;
	int prevPointIndexRed = -1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
            	if(event.mouseButton.button == sf::Mouse::Left)
            	{
        	        //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
        	        //std::cout << "mouse y: " << event.mouseButton.y << std::endl;

        	        for (int row = 0; row < ROW_COUNT; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT; ++col)
        	        	{
            	        	int arrIndex = row * COL_COUNT + col;
                    		if(grid[arrIndex].contains(event.mouseButton.x, event.mouseButton.y))
                    		{
                    			if(points[arrIndex] == 0 || pointsRed[arrIndex] == 0)
                    			{
                    				if(playerState == BLUE)
                    				{
    									blueDotsSprite[arrIndex].setPosition(grid[arrIndex].left, grid[arrIndex].top);
    									points[arrIndex] = 1;

    									// reset the first point if no adjacent point is selected
    									if(prevPointIndex != -1 && (!checkForLine(prevPointIndex)) )
    									{
    										blueDotsSprite[prevPointIndex].setPosition(sf::Vector2f());
    										points[prevPointIndex] = 0;
    									}

    									// then check for a line and change to the next player's turn
    									if(!checkForSquare(arrIndex) && checkForLine(arrIndex))
    									{
    										playerState = RED;
    									}

    									prevPointIndex = arrIndex;
                    				}
                    				else if(playerState == RED)
                    				{
    									redDotsSprite[arrIndex].setPosition(grid[arrIndex].left, grid[arrIndex].top);
    									pointsRed[arrIndex] = 1;

    									// reset the first point if no adjacent point is selected
    									if(prevPointIndexRed != -1 && (!checkForRedLine(prevPointIndexRed)) )
    									{
    										redDotsSprite[prevPointIndexRed].setPosition(sf::Vector2f());
    										pointsRed[prevPointIndexRed] = 0;
    									}

    									// then check for a line and change to the next player's turn
       									if(!checkForRedSquare(arrIndex) && checkForRedLine(arrIndex))
										{
											playerState = BLUE;
										}

       									prevPointIndexRed = arrIndex;
                    				}
                    			}
                    		}
        	        	}
        	        }

        	        // loop for setting the horizontal lines
        	        for (int row = 0; row < ROW_COUNT; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT - 1; ++col)
        	        	{
        	        		int arrIndex = row * COL_COUNT + col;
        	        		if(points[arrIndex] && rightPoint(row, col))
        	        		{
        	         			blueHorizontalLinesSprite[arrIndex].setPosition(horizontalLinesGrid[arrIndex].left, horizontalLinesGrid[arrIndex].top);
        	        		}
        	        		if(pointsRed[arrIndex] && rightRedPoint(row, col))
        	        		{
        	         			redHorizontalLinesSprite[arrIndex].setPosition(horizontalLinesGrid[arrIndex].left, horizontalLinesGrid[arrIndex].top);
        	        		}
        	        	}
        	        }

        	        // loop for setting the vertical lines
        	        for (int row = 0; row < ROW_COUNT - 1; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT; ++col)
        	        	{
        	        		int arrIndex = row * COL_COUNT + col;
        	        		if(points[arrIndex] && lowerPoint(row, col))
        	        		{
            	        		blueVerticalLinesSprite[arrIndex].setPosition(verticalLinesGrid[arrIndex].left, verticalLinesGrid[arrIndex].top);
        	        		}
          	        		if(pointsRed[arrIndex] && lowerRedPoint(row, col))
							{
								redVerticalLinesSprite[arrIndex].setPosition(verticalLinesGrid[arrIndex].left, verticalLinesGrid[arrIndex].top);
							}
        	        	}
        	        }

        	        // loop for setting the squares
        	        for (int row = 0; row < ROW_COUNT - 1; ++row)
        	        {
        	        	for (int col = 0; col < COL_COUNT - 1; ++col)
        	        	{
        	            	int squareIndex = row * COL_COUNT + col;
        	            	if(row == ROW_COUNT - 1 || col == COL_COUNT - 1) break;

        	            	if(points[squareIndex] && lowerPoint(row, col) && rightPoint(row, col) && rightDiagonalPoint(row, col))
        	            	{
        	            		// no red points previously set
        	            		if( !pointsRed[squareIndex] && !lowerRedPoint(row, col) && !rightRedPoint(row, col) && !rightRedDiagonalPoint(row, col) )
        	            		{
            	            		blueSquaresSprite[squareIndex].setPosition(squaresGrid[squareIndex].left, squaresGrid[squareIndex].top);
        	            		}
        	            	}

           	            	if(pointsRed[squareIndex] && lowerRedPoint(row, col) && rightRedPoint(row, col) && rightRedDiagonalPoint(row, col))
							{
        	            		// no blue points previously set
           	            		if( !points[squareIndex] && !lowerPoint(row, col) && !rightPoint(row, col) && !rightDiagonalPoint(row, col) )
           	            		{
    								redSquaresSprite[squareIndex].setPosition(squaresGrid[squareIndex].left, squaresGrid[squareIndex].top);
           	            		}
							}
        	        	}
        	        }
            	}
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

        }

        window.clear();
        // draw background
        window.draw(sprite);

        // draw dots and lines

        for (int row = 0; row < ROW_COUNT - 1; ++row)
        {
        	for (int col = 0; col < COL_COUNT; ++col)
        	{
        		int arrIndex = row * COL_COUNT + col;
            	if(blueVerticalLinesSprite[arrIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(blueVerticalLinesSprite[arrIndex]);
            	}
            	if(redVerticalLinesSprite[arrIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(redVerticalLinesSprite[arrIndex]);
            	}
        	}
        }

        for (int row = 0; row < ROW_COUNT; ++row)
        {
        	for (int col = 0; col < COL_COUNT - 1; ++col)
        	{
        		int arrIndex = row * COL_COUNT + col;
            	if(blueHorizontalLinesSprite[arrIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(blueHorizontalLinesSprite[arrIndex]);
            	}
            	if(redHorizontalLinesSprite[arrIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(redHorizontalLinesSprite[arrIndex]);
            	}
        	}
        }

        for (int row = 0; row < ROW_COUNT; ++row)
        {
        	for (int col = 0; col < COL_COUNT; ++col)
        	{
        		int arrIndex = row * COL_COUNT + col;
            	if(blueDotsSprite[arrIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(blueDotsSprite[arrIndex]);
            	}
            	if(redDotsSprite[arrIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(redDotsSprite[arrIndex]);
            	}
        	}
		}

        for (int row = 0; row < ROW_COUNT - 1; ++row)
        {
        	for (int col = 0; col < COL_COUNT - 1; ++col)
        	{
            	int squareIndex = row * COL_COUNT + col;
            	if(blueSquaresSprite[squareIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(blueSquaresSprite[squareIndex]);
            	}
            	if(redSquaresSprite[squareIndex].getPosition() != sf::Vector2f())
            	{
            		window.draw(redSquaresSprite[squareIndex]);
            	}
        	}
        }

        // PRINT POINTS ARRAY FOR TEST
        /*for (int row = 0; row < ROW_COUNT; ++row)
        {
        	for (int col = 0; col < COL_COUNT; ++col)
        	{
        		int arrIndex = row * COL_COUNT + col;
        		std::cout << points[arrIndex] << " ";
        	}
        	std::cout << std::endl;
        }
    	std::cout << "=============================================" << std::endl;*/

        window.display();
    }

    return 0;
}
