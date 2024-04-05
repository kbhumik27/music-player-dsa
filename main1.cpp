#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Song {
public:
    Song(const string& title, const string& artist, const string& filePath)
        : title(title), artist(artist), filePath(filePath), next(nullptr) {}

    string getTitle() const { return title; }
    string getArtist() const { return artist; }
    string getFilePath() const { return filePath; }

    Song* getNext() const { return next; }
    void setNext(Song* newNext) { next = newNext; }

private:
    string title;
    string artist;
    string filePath;
    Song* next;
};

class Playlist {
public:
    Playlist() : head(nullptr) {}

    void addSong(const Song& song) {
        Song* newSong = new Song(song.getTitle(), song.getArtist(), song.getFilePath());
        if (!head) {
            head = newSong;
        } else {
            Song* current = head;
            while (current->getNext()) {
                current = current->getNext();
            }
            current->setNext(newSong);
        }
    }

    void displaySongs() const {
        Song* current = head;
        while (current) {
            cout << current->getTitle() << " - " << current->getArtist() << endl;
            current = current->getNext();
        }
    }

    void playAllSongs() const {
        Song* current = head;
        while (current) {
            sf::SoundBuffer buffer;
            if (buffer.loadFromFile(current->getFilePath())) {
                sf::Sound sound(buffer);
                sound.play();
                while (sound.getStatus() == sf::Sound::Playing) {
                    // Wait until song finishes playing
                }
            } else {
                cout << "Failed to load sound: " << current->getFilePath() << endl;
            }
            current = current->getNext();
        }
    }

    ~Playlist() {
        Song* current = head;
        while (current) {
            Song* next = current->getNext();
            delete current;
            current = next;
        }
    }

private:
    Song* head;
};

int main() {
    map<string, Playlist> playlists;

    while (true) {cout << "------------------------------------" << endl;
        cout << "            Music Systum              " << endl;
        cout << "------------------------------------" << endl;
        cout << "1. Create Playlist" << endl;
        cout << "2. Add Song to Playlist" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Play Playlist" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            string playlistName;
            cout << "Enter playlist name: ";
            cin >> playlistName;

            playlists[playlistName] = Playlist();
            cout << "Playlist created." << endl;
        } else if (choice == 2) {
            string playlistName;
            cout << "Enter playlist name: ";
            cin >> playlistName;

            if (playlists.find(playlistName) != playlists.end()) {
                string title, artist, filePath;
                cout << "Enter song title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter audio file path: ";
                getline(cin, filePath);

                playlists[playlistName].addSong(Song(title, artist, filePath));
                cout << "Song added to playlist." << endl;
            } else {
                cout << "Playlist not found." << endl;
            }
        } else if (choice == 3) {
            string playlistName;
            cout << "Enter playlist name: ";
            cin >> playlistName;

            if (playlists.find(playlistName) != playlists.end()) {
                cout << "Playlist: " << playlistName << endl;
                playlists[playlistName].displaySongs();
            } else {
                cout << "Playlist not found." << endl;
            }
        } else if (choice == 4) {
            string playlistName;
            cout << "Enter playlist name: ";
            cin >> playlistName;

            if (playlists.find(playlistName) != playlists.end()) {
                playlists[playlistName].playAllSongs();
            } else {
                cout << "Playlist not found." << endl;
            }
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
