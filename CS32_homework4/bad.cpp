void removeBad(list<Movie*>& li)
{
	list<Movie*>::iterator p = li.begin();
	for (; p != li.end();) {
		if ((*p)->rating() < 50) {
			delete (*p);
			p = li.erase(p);
		}
		else
			p++;
	}
}