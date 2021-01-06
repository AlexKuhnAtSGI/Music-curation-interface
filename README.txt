By Alexander Kuhn (ID 101023154)

Tested on COMP2401B-W17 Linux VM.
I used the A3 sample answer code to build this.
Unzipping/compilation instructions
	-navigate to the a4 directory in cmd
	-use "unzip a4.zip" (no quotes)
	-use "make" (no quotes)
	-run with ./mytunes

The program reads the insert_beatles_tracks_rev1.txt script on startup.
To disable this behaviour comment out the lines:

  //initialize app with input script
  Command cmd = Command(".read insert_beatles_tracks_rev1.txt");
  executeCommand(cmd);

in the run() method at the start of the UI.cpp file.

After it's initialized the database, use the command ".read follow_script.txt" (no quotes) to test it.

Note: I have removed excessive notation (i.e. the "parsed command", "Object(const&attribute)" and "~Object" strings). These can easily be added back in by uncommenting them from command.cpp or from the corresponding object.cpp
files, respectively.
Also, the file the professor has provided to show what our output should look like is not quite accurate to the txt file that populates the database - the adding script adds playlists and playlist tracks not present in the sample
output. The differences are cosmetic, though - the commands are doing what they're supposed to.