#ifndef FUNCTIONS
#define FUNCTIONS

	// Convert canonical mode to non-canonical mode
	struct termios canon_to_NC();

	// Convert non-canonical mode to canonical mode
	void NC_to_canon(struct termios term_p);

	// Store the list of files/directories in current directory in a vector
	int list_store(DIR *cur_dir,const char * path, vector <struct dirent*> directories);

	// Display the list of files/directories from the stored vector
	int list_display(int upper, int lower, vector <struct dirent*> directories);


#endif