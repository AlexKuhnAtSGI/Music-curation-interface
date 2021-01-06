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

#include <iostream>
#include <string>
using namespace std;

#include "subject.h"
#include "observer.h"
#include "playlist.h"
	
Playlist::Playlist(const string & aPlaylistName){
	//cout << "Playlist(string&)" << endl;
	name = aPlaylistName;
	followedPlaylist = this;
	hasFollowed = 0;
}
Playlist::Playlist(const Playlist & aPlaylist){
	cout << "Playlist(const Playlist & aPlaylist)" << endl;
	cout << "ERROR: Playlist(const Playlist & aPlaylist) --should never run" << endl;
}

Playlist::~Playlist(){
	stopFollowing();
	massDettach(); 
	//cout << "~Playlist(void)" << endl;
}
int Playlist::getID(){return -1;}
string Playlist::getName(){return name;}
int Playlist::checkFollowing(){return hasFollowed;}

vector<Track*> & Playlist::getTracks(){
	return tracks;}

Playlist * Playlist::isFollowing() {
//for preventing mutual following situations
	if (hasFollowed != 0) {
		return followedPlaylist;
		}
	else {
		return NULL;
	}
}

vector<Track*>::iterator Playlist::findPosition(Track & aTrack){
	for (vector<Track*>::iterator itr = tracks.begin() ; itr != tracks.end(); ++itr)
		if(*itr == &aTrack) return itr;
	return tracks.end();
}

//The following are the 2 methods that can result in updates to the observers
void Playlist::addTrack(Track & aTrack){
	//add track if it does not already exist
	vector<Track*>::iterator itr = findPosition(aTrack);
	if(itr == tracks.end()) {
		tracks.push_back(&aTrack);
	}
	notify();
}

void Playlist::removeTrack(Track & aTrack){
	vector<Track*>::iterator itr = findPosition(aTrack);
	if(itr != tracks.end()) {
		tracks.erase(itr);
	}
	notify();
}

void Playlist::setTracks(vector<Track*> & newTracks){
//doesn't notify - notifying could cause infinite loop
	tracks.clear();
	for (vector<Track*>::iterator itr = newTracks.begin() ; itr != newTracks.end(); ++itr){
		tracks.push_back(*itr);
	}
}

string Playlist::toString()const {
	string indent = "     ";
	string s;
	s.append(name);
	s.append("\n");
	s.append(indent + indent + "Playlist Tracks:\n");
	for (vector<Track*>::size_type i = 0 ; i < tracks.size(); i++){
		   s.append(indent + indent + to_string(i) + " " + (tracks[i])->toString() + "\n");
	}
	
	return s;
}

void Playlist::follows(Playlist * followP) {
	//a Playlist can only follow one other Playlist
	//this will set it so that a) this Playlist ends its current following relationship, if any
	//b) it is attached to the Playlist provided as argument
	//c) it mirrors that Playlist
	//d) its observers mirror it
	//and finally e) it is now an active observer
	stopFollowing();
	followedPlaylist = followP;
	followedPlaylist->attach(*this);
	setTracks(followedPlaylist->getTracks());
	notify();
	hasFollowed = 1;
}

void Playlist::stopFollowing() {
	//ends observing
	if (hasFollowed == 0) return;
	if (followedPlaylist != NULL) {
		followedPlaylist->dettach(*this);
	}
	else {
		followedPlaylist = this;
	}
	hasFollowed = 0;
}

void Playlist::update(Subject * subject) {
	this->setTracks(followedPlaylist->getTracks());
}

void Playlist::update(Subject * subject, int deletion) {
	stopFollowing();
}

ostream & operator<<(ostream & out, const Playlist & aPlaylist){
	out << aPlaylist.toString() << endl;
	return out;
}
