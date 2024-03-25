#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <limits>

namespace CONSTANTS
{
    constexpr int MAX_SONGS = 30;
    constexpr int MAX_NAME_LENGTH = 64;
    constexpr int MAX_CONTENT_LENGTH = 64;
    constexpr int MAX_GENRE_LENGTH = 100;
    constexpr int MAX_AMOUNT_OF_GENRES = 5;
    constexpr int AMOUNT_OF_BITS_IN_BYTE = 8;
}

using namespace CONSTANTS;

enum Genre : unsigned char 
{
    Pop = 1,       
    Rock = 2,       
    HipHop = 4,    
    Electronic = 8,
    Jazz = 16      
};

void sstrcpy(char* destination, const char* source) 
{
    if (destination == nullptr || source == nullptr) 
    {
        return;
    }

    while (*source != '\0') 
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
}

void strconcat(char* dest, const char* src) 
{
    while (*dest) dest++;
    while (*src) *dest++ = *src++;
    *dest = '\0';
}

size_t sstrlen(const unsigned char* arr)
{
    int ind = 0;
    while (arr[ind] != '\0')
    {
        ind++;
    }
    
    return --ind;
}

struct Song
{
    char name[MAX_NAME_LENGTH];
    int duration; 
    Genre genre;
    unsigned char content[MAX_CONTENT_LENGTH];
    int contentLength;

    Song() : duration(0), genre(Genre(0)), contentLength(0)
    {
        name[0] = '\0';
        duration = 0;
        genre = Genre(0);
        content[0] = '\0';
        contentLength = 0;

    }

    void readContentFromFile(const char* fileName)
    {
        std::ifstream file(fileName, std::ios::binary);

        if (!file.is_open()) 
        {
            std::cout << "Failed to open file: " << fileName << std::endl;
            return;
        }

        contentLength = 0;

        char ch;

        while (file.get(ch) && contentLength < MAX_CONTENT_LENGTH)
        {
            content[contentLength] = ch; 
            ++contentLength; 
        }

        content[contentLength] = '\0';

        file.close();
    }

    void modifyContent(const int &k = 0, const bool &mix = 0, const unsigned char* mixWith = nullptr, const int &mixLength = 0)
    {
        if (mix)
        {
            size_t minLength = contentLength < mixLength ? contentLength : mixLength;

            for (size_t i = 0; i < minLength; ++i)
            {
                content[i] ^= mixWith[i];
            }
        }
        else
        {
            size_t t = contentLength * AMOUNT_OF_BITS_IN_BYTE;

            for (size_t i = 0; i < t ; i += k)
            {
                content[i / AMOUNT_OF_BITS_IN_BYTE] |= 1 << (AMOUNT_OF_BITS_IN_BYTE - 1 - i % AMOUNT_OF_BITS_IN_BYTE);
            }
        }
    }

};

class Playlist
{

private:
    Song songs[MAX_SONGS];
    int songCount;

public:
    Playlist() : songCount(0) {}

    void mix(const char* songName1, const char* songName2)
    {
        Song* song1 = nullptr;
        Song* song2 = nullptr;


        for (int i = 0; i < songCount; ++i) 
        {
            if (strcmp(songs[i].name, songName1) == 0) 
            {
                song1 = &songs[i];
            }
            else if (strcmp(songs[i].name, songName2) == 0) 
            {
                song2 = &songs[i];
            }
        }

        if (!song1 || !song2) 
        {
            std::cout << "One or both songs not found." << std::endl;
            return;
        }

        int mixLength = std::min(sstrlen(song1->content), sstrlen(song2->content));


        for (int i = 0; i < mixLength-1; i++)
        {
            song1->content[i] ^= song2->content[i];
        }

        song1->contentLength = mixLength;

        std::cout << "Mixing complete." << std::endl;
    }

    void save(const char &mixedChar, const char* outputFileName) 
    {
        std::ofstream outputFile(outputFileName, std::ios::binary);

        if (!outputFile) 
        {
            std::cout << "Failed to create file: " << outputFileName << std::endl;
            return;
        }

        outputFile << mixedChar;

        std::cout << "Result saved to " << outputFileName << std::endl;

        outputFile.close();
    }


    void add(const char* name, const int &hours, const int &minutes, const int &seconds, const char* genreStr, const char* fileName)
    {
        if (songCount >= MAX_SONGS)
        {
            std::cout << "Playlist is full" << std::endl;
            return;
        }

        Song& song = songs[songCount++];

        sstrcpy(song.name, name);

        song.duration = hours * 3600 + minutes * 60 + seconds;

        song.genre = parseGenre(genreStr);

        song.readContentFromFile(fileName);
    }

    Genre parseGenre(const char* genreStr) const
    {
        Genre genre = Genre(0);
        while (*genreStr)
        {
            switch (*genreStr++)
            {
                case 'p': genre = Genre(genre | Pop); break;
                case 'r': genre = Genre(genre | Rock); break;
                case 'h': genre = Genre(genre | HipHop); break;
                case 'e': genre = Genre(genre | Electronic); break;
                case 'j': genre = Genre(genre | Jazz); break;
            }
        }
        return genre;
    }

    void print() const
    {
        for (int i = 0; i < songCount; ++i)
        {
            const Song& song = songs[i];

            char genreStr[MAX_GENRE_LENGTH] = "";

            genreToString(song.genre, genreStr);

            std::cout << song.name << ", ";
            std::cout << song.duration / 3600 << ":";
            std::cout << (song.duration % 3600) / 60 << ":";
            std::cout << song.duration % 60 << ", ";
            std::cout << genreStr << std::endl;
        }
    }

    void genreToString(const Genre &genre, char* outStr) const 
    {
        outStr[0] = '\0';

        if (genre & Pop) 
        {
            strconcat(outStr, "Pop");
        }

        if (genre & Rock) 
        {
            if (strlen(outStr) > 0) 
            {
                strconcat(outStr, "&");
            }
            strconcat(outStr, "Rock");
        }

        if (genre & HipHop) 
        {
            if (strlen(outStr) > 0) 
            {
                strconcat(outStr, "&");
            }
            strconcat(outStr, "HipHop");
        }

        if (genre & Electronic) 
        {
            if (strlen(outStr) > 0) 
            {
                strconcat(outStr, "&");
            }
            strconcat(outStr, "Electronic");
        }

        if (genre & Jazz) 
        {
            if (strlen(outStr) > 0) 
            {
                strconcat(outStr, "&");
            }
            strconcat(outStr, "Jazz");
        }
    }

    void find(const char* name) const
    {
        for (int i = 0; i < songCount; i++)
        {
            if (strcmp(songs[i].name, name) == 0)
            {
                const Song& song = songs[i];

                char genreStr[MAX_GENRE_LENGTH] = "";

                genreToString(song.genre, genreStr);

                std::cout << song.name << ", ";
                std::cout << song.duration / 3600 << ":";
                std::cout << (song.duration % 3600) / 60 << ":";
                std::cout << song.duration % 60 << ", ";
                std::cout << genreStr << std::endl;

                return;
            }
        }

        std::cout << "Song not found." << std::endl;
    }

    void findGenre(char genreChar) const
    {
        Genre searchGenre = parseGenre(&genreChar);

        bool found = 0;

        for (int i = 0; i < songCount; ++i)
        {
            if (songs[i].genre & searchGenre)
            {
                const Song& song = songs[i];

                char genreStr[MAX_GENRE_LENGTH] = "";

                genreToString(song.genre, genreStr);

                std::cout << song.name << ", ";
                std::cout << song.duration / 3600 << ":";
                std::cout << (song.duration % 3600) / 60 << ":";
                std::cout << song.duration % 60 << ", ";
                std::cout << genreStr << std::endl;

                found = 1;
            }
        }

        if (!found) 
        {
            std::cout << "No songs found for this genre." << std::endl;
        }
    }

    void sortByName() 
    {
        for (int i = 0; i < songCount - 1; i++) 
        {
            for (int j = 0; j < songCount - i - 1; j++) 
            {
                if (strcmp(songs[j].name, songs[j + 1].name) > 0) 
                {
                    Song temp = songs[j];
                    songs[j] = songs[j + 1];
                    songs[j + 1] = temp;
                }
            }
        }
    }

    void sortByDuration() 
    {
        for (int i = 0; i < songCount - 1; i++) 
        {
            for (int j = 0; j < songCount - i - 1; j++) 
            {
                if (songs[j].duration > songs[j + 1].duration) 
                {
                    Song temp = songs[j];
                    songs[j] = songs[j + 1];
                    songs[j + 1] = temp;
                }
            }
        }
    }

    void mixSongs(int index1, int index2) 
    {
        if (index1 < 0 || index1 >= songCount || index2 < 0 || index2 >= songCount) 
        {
            std::cout << "Invalid song indexes." << std::endl;
            return;
        }

        songs[index1].modifyContent(0, true, songs[index2].content, songs[index2].contentLength);

        std::cout << "Songs mixed successfully." << std::endl;
    }
};

void menu()
{
    std::cout << "For add, type 1..." << std::endl;
    std::cout << "For sort by name, type 2..." << std::endl;
    std::cout << "For sort by duration, type 3..." << std::endl;
    std::cout << "To find a song, type 4..." << std::endl;
    std::cout << "To find songs with a specific genre, type 5..." << std::endl;
    std::cout << "To see whole playlist, type 6..." << std::endl;
    std::cout << "To exit, type 0..." << std::endl;
}

void errorMessage()
{
    std::cout << "Invalid input. Please provide output according to menu rules." << std::endl;
}

bool errorCapture()
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        errorMessage(); 
        return true;
    }
    return false;
}

char formatGenreName(const char* arr)
{
    if (arr[0] >= 'a' && arr[0] <= 'z') return arr[0];
    return arr[0] - 'A' + 'a';
}

int main()
{
    Playlist p;
    unsigned step = 1, hours=0, minutes=0, seconds=0;
    char g, genre[MAX_GENRE_LENGTH], songName[MAX_NAME_LENGTH], genres[MAX_AMOUNT_OF_GENRES], fileName[MAX_CONTENT_LENGTH];
    

    while (step)
    {
        menu();
        std::cin >> step;

        if (errorCapture())
        {
            errorMessage();
            continue;
        }

        switch (step)
        {

        case 1:
        {

            std::cout << "Write the songname" << std::endl;
            std::cin >> songName;
            std::cout << "Write the hours" <<std::endl;
            std::cin >> hours;
            std::cout << "Write the minutes" << std::endl;
            std::cin >> minutes;
            std::cout << "Write the seconds" << std::endl;
            std::cin >> seconds;
            std::cout << "Write the genre(s) as their lowercase first letters (e.g. Pop & Rock, write 'pr'" << std::endl;
            std::cin >> genres;
            std::cout << "Write the filename where the content is" << std::endl;
            std::cin >> fileName;

            p.add(songName, hours, minutes, seconds, genres, fileName);
            std::cout << "Song successfully added" << std::endl;
            p.print();
            break;
        }

        case 2:
        {
            std::cout << "\nPlaylist Sorted by Name:" << std::endl;
            p.sortByName();
            p.print();
            break;
        }

        case 3:
        {
            std::cout << "Playlist sorted by duration:" << std::endl;
            p.sortByDuration();
            p.print();
            break;
        }

        case 4:
        {
            std::cout << "Please write song name:" << std::endl;
            std::cin >> songName;            
            std::cout << "Finding song by name: "<< songName << std::endl;
            p.find(songName);
            break;
        }
        
        case 5:
        {
            std::cout << "Please write song genre:" << std::endl;
            std::cin >> genre;
            g = formatGenreName(genre);
            std::cout << "Finding song by genre: " << genre << std::endl;
            p.findGenre(g);
            break;

        }

        case 6:
        {
            p.print();
            break;
        }

        default:
        {
            std::cout << "Please enter valid command" << std::endl;
                continue;
        }

        }
    } 

    std::cout << "Thank you for using this program! Come again!" << std::endl;

    return 0;
}



