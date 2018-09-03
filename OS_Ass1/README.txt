#############################  Terminal File Explorer #############################################

Main File : kakashi.cpp 
Supporting files for Normal Mode: list.h, commandMod.h, termSet.h

This project runs only in Normal Mode. It would enter command mode on pressing ':' (although there are no commands to execute).
To exit from command mode press ESC key.

Functionalities of the Normal Mode are as follows:

1. On executing kakashi.cpp, the directory structure where this file is present would open. This is the root directory.
   Navigation could be done only in direction forward of the root.

2. To scroll in the displayed list of files and directories, use UP and DOWN arrow keys.

3. On pressing "Enter" on a directory, list of directories/files inside that directory opens up. In case of a file, "Enter" 
	would open that file.

4. On pressing Backspace, navigate to parent directory of current directory. No effect is seen if current directory is root.

5. On pressing Left Arrow key, previously visited directory is displayed.

6. On pressing Right Arrow key, next directory among the visited directories stack is displayed.

7. On pressing 'h', Home(Root) directory is reached

8. Press 'q' to exit from the application.
