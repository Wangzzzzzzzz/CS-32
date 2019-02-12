void listAll(string path, const File* f)  // two-parameter overload
{
	if (f == nullptr)
		return;
	path = path + "/" + f->name();
	cout << path << endl;
	const vector<File*>* temp = f->files();
	//base case : plain file
	if (temp == nullptr)
		return;
	vector<File*>::const_iterator p = temp->begin();
	for(; p != temp->end(); p++ )
		listAll(path, *p);
}