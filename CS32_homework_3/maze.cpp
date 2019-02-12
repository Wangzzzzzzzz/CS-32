// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	if (sr == er && sc == ec)
		return true;
	maze[sr][sc] = 'E'; //mark as explored

	// go north
	if (maze[sr - 1][sc] == '.' && pathExists(maze, sr - 1, sc, er, ec))
		return true;

	//go west
	if (maze[sr][sc - 1] == '.' && pathExists(maze, sr, sc - 1, er, ec))
		return true;

	//go south
	if (maze[sr + 1][sc] == '.' && pathExists(maze, sr + 1, sc, er, ec))
		return true;

	//go east
	if (maze[sr][sc + 1] == '.' && pathExists(maze, sr, sc + 1, er, ec))
		return true;

	return false;
}
