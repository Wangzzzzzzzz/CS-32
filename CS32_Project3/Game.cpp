#include "Game.h"
#include "Well.h"
#include "Piece.h"
#include "UserInterface.h"
#include <string>
#include <iostream>
#include <cstdlib>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

const int STATUS_STRING_LENGTH = 19;

Game::Game(int width, int height)
	: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(height, width), m_next_piece(nullptr), m_score(0), m_row_left(5)
{
	if (width < 7 || height < 4) {
		exit(1);
		std::cerr << "Well size is not valid.";
	}
}

Game::~Game() {
	delete m_next_piece;
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]


	//game offically start here
    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
		m_well.discard();
		m_row_left = 5 * m_level;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
	std::string score = std::to_string(m_score);
	std::string rowLeft = std::to_string(m_row_left);
	std::string level = std::to_string(m_level);

	if (m_next_piece != nullptr) {
		m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
		m_screen.printString("Next Piece:");
		for (int i = 0; i < 4; i++) {
			m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + i);
			m_screen.printStringClearLine(m_next_piece->get_graph()[i]);
		}
	}
	//print the score;
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printStringClearLine("Score:");
	m_screen.gotoXY(SCORE_X + STATUS_STRING_LENGTH - score.length(), SCORE_Y);
	m_screen.printStringClearLine(score);

	//print the row left
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printStringClearLine("Rows left:");
	m_screen.gotoXY(ROWS_LEFT_X + STATUS_STRING_LENGTH - rowLeft.length(), ROWS_LEFT_Y);
	m_screen.printStringClearLine(rowLeft);

	//print the level
	m_screen.gotoXY(LEVEL_X,LEVEL_Y);
	m_screen.printStringClearLine("Level:");
	m_screen.gotoXY(LEVEL_X + STATUS_STRING_LENGTH - level.length(), LEVEL_Y);
	m_screen.printStringClearLine(level);

	m_screen.refresh();
}

bool Game::playOneLevel()
{
	bool gameGoOn = true;
	int linesCleaned;
	if (m_next_piece != nullptr) {
		delete m_next_piece;
	}
	drawPiece();
	m_well.updatePiece(m_next_piece);
	drawPiece();
	m_well.addPiece();
	while (true) {
		m_well.display(m_screen, WELL_X, WELL_Y);
		displayStatus();
		Timer gravity;
		while (gravity.elapsed() < maximun((1000 - (100 * (m_level - 1))), 100)) {
			char ch;
			if (getCharIfAny(ch)) {
				if (ch == ARROW_DOWN)
					break;
				else if (ch == ' ') {
					while (m_well.moveDown());
					m_well.fix();
					m_well.display(m_screen, WELL_X, WELL_Y);
					linesCleaned = m_well.clean();
					m_row_left = (m_row_left - linesCleaned < 0 ? 0 : m_row_left - linesCleaned);
					m_score += get_score(linesCleaned);
					displayStatus();
					if (m_row_left == 0)
						return true;
					m_well.updatePiece(m_next_piece);
					gameGoOn = m_well.addPiece();
					drawPiece();
					m_well.display(m_screen, WELL_X, WELL_Y);
					displayStatus();
					if (!gameGoOn)
						return false;
					gravity.start();
					continue;
				}
				else if (ch == ARROW_LEFT) {
					m_well.moveLeft();
					m_well.display(m_screen, WELL_X, WELL_Y);
					displayStatus();
				}
				else if (ch == ARROW_RIGHT) {
					m_well.moveRight();
					m_well.display(m_screen, WELL_X, WELL_Y);
					displayStatus();
				}
				else if (ch == ARROW_UP) {
					m_well.rotate();
					m_well.display(m_screen, WELL_X, WELL_Y);
					displayStatus();
				}
				else if (ch == 'q') {
					return false;
				}
				else{}
			}
		}
		if (!m_well.moveDown()) {
			m_well.fix();
			m_well.display(m_screen, WELL_X, WELL_Y);
			linesCleaned = m_well.clean();
			m_row_left = (m_row_left - linesCleaned < 0 ? 0 : m_row_left - linesCleaned);
			m_score += get_score(linesCleaned);
			displayStatus();
			if (m_row_left == 0)
				return true;
			m_well.updatePiece(m_next_piece);
			gameGoOn = m_well.addPiece();
			drawPiece();
			m_well.display(m_screen, WELL_X, WELL_Y);
			if (!gameGoOn)
				return false;
		}
	}
}

void Game::drawPiece() {
	switch (chooseRandomPieceType()) {
	case PIECE_CRAZY:
		m_next_piece = new PieceCrazy(&m_well);
		break;
	case PIECE_FOAM:
		m_next_piece = new PieceFoam(&m_well);
		break;
	case PIECE_I:
		m_next_piece = new PieceI(&m_well);
		break;
	case PIECE_J:
		m_next_piece = new PieceJ(&m_well);
		break;
	case PIECE_L:
		m_next_piece = new PieceL(&m_well);
		break;
	case PIECE_O:
		m_next_piece = new PieceO(&m_well);
		break;
	case PIECE_S:
		m_next_piece = new PieceS(&m_well);
		break;
	case PIECE_T:
		m_next_piece = new PieceT(&m_well);
		break;
	case PIECE_VAPOR:
		m_next_piece = new PieceVapor(&m_well);
		break;
	case PIECE_Z:
		m_next_piece = new PieceZ(&m_well);
		break;
	default:
		break;
	}
}

int Game::get_score(int linesCleaned) {
	switch (linesCleaned) {
	case 0:
		return 0;
	case 1:
		return 100;
	case 2:
		return 200;
	case 3:
		return 400;
	case 4:
		return 800;
	case 5:
		return 1600;
	default:
		return 0;
	}
}

int maximun(int comp1, int comp2) {
	return (comp1 > comp2 ? comp1 : comp2);
}

