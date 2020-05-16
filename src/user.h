#ifndef USER_H
#define USER_H

#include <string>

//class which represent basic information about user
class User
{
public:
	//constructor
    User(std::string username);
    User(std::string username, int record);
    
    //setters, getters
    int Record() const; 		// return record of current user
    std::string Name() const; 	// return name of current user
    void SetRecord(const int& score);
    
    //other functions
    
    //this function update file scoreboard.txt or create it if it was not created before
    void WriteResult();

private:

	/*this function search in file scoreboard.txt if this user have a previous record,
    *return 0 in 2 cases: file is inaccessible or record is 0
    *in other case return record of user
    */
	int FindRecord(std::string& username);

    bool newUser;
	std::string username;

    //best score from the previous games
    int record;
    
};
#endif