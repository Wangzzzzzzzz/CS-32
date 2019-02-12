#include <queue>
#include <iostream>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	queue<Coord> coord;
	int cur_r;
	int cur_c;
	coord.push(Coord(sr, sc));
	maze[sr][sc] = 'E'; //mark as explored
	while (!coord.empty()) {
		if (coord.front().r() == er && coord.front().c() == ec)
			return true;
		cur_r = coord.front().r();
		cur_c = coord.front().c();
		coord.pop();

		// go north
		if (maze[cur_r - 1][cur_c] == '.') {
			coord.push(Coord(cur_r - 1, cur_c));
			maze[cur_r - 1][cur_c] = 'E';
		}

		//go west
		if (maze[cur_r][cur_c - 1] == '.') {
			coord.push(Coord(cur_r, cur_c - 1));
			maze[cur_r][cur_c - 1] = 'E';
		}

		//go south
		if (maze[cur_r + 1][cur_c] == '.') {
			coord.push(Coord(cur_r + 1, cur_c));
			maze[cur_r + 1][cur_c] = 'E';
		}

		//go east
		if (maze[cur_r][cur_c + 1] == '.') {
			coord.push(Coord(cur_r, cur_c + 1));
			maze[cur_r][cur_c + 1] = 'E';
		}
	}
	return false;
}

int main()
{
	
}
