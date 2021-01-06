/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                   */
/*  Program:  MyTunes Music Player                   */
/*  Contributors: Alexander Kuhn (101023154)	     */
/*  Author:   Louis Nel                              */
/*  Date:     21-SEP-2017                            */
/*                                                   */
/*  (c) 2017 Louis Nel                               */
/*  All rights reserved.  Distribution and           */
/*  reposting, in part or in whole, requires         */
/*  written consent of the author.                   */
/*                                                   */
/*  COMP 2404 students may reuse this content for    */ 
/*  their course assignments without seeking consent */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _Playlist_H
#define _Playlist_H

#include <ostream>
#include <string>
#include <vector>

#include "track.h"
#include "subject.h"
#include "observer.h"


class Playlist: public Subject, public Observer {
	/*
	Playlist represents an user playlist of tracks.
	*/
	public:
	Playlist(const string & aPlaylistName); 
	~Playlist(void);
    int getID();
	string getName();
	int checkFollowing(); //keeps track of whether the playlist is currently observing
	Playlist * isFollowing(); //returns the playlist being observed, or NULL if no playlist is being followed
	void removeTrack(Track & aTrack);
	void addTrack(Track & aTrack);
	vector<Track*> & getTracks();
    string toString() const;
	void update(Subject * subject);
	void update(Subject * subject, int deletion);
	void setTracks(vector<Track*> & newTracks); //when following begins, this copies the tracks from the subject into the observer
	void follows(Playlist * followP); //called by mytunes, establishes subject-observer relationship
	void stopFollowing(); //also called by mytunes, brings subject-observer relationship to an end
	
	private:
	string name;
	int hasFollowed; //either 0 or 1
	vector<Track*> tracks;	
	vector<Track*>::iterator findPosition(Track & aTrack);
	Playlist * followedPlaylist;
	Playlist(const Playlist & aPlaylist); //hide copy constructor in private section
};

ostream & operator<<(ostream & out, const Playlist & aPlaylist);

#endif