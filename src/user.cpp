#include "user.h"

#include <fstream> // for ifstream
#include <sstream> //for istringstream
#include <algorithm> //for std::sort
#include <iostream>
#include <vector>

User::User(std::string username):
			username(username)
{
  record = FindRecord(username);
  newUser = (record == 0)?true:false;
}

User::User(std::string username, int record): 
          username(username), record(record), newUser(false){}

int User::FindRecord(std::string& username)
{
  std::ifstream file;
  file.open("scoreboard.txt");
  /* file scoreboard.txt contain information about players
  *and have such structure:
  * username record
  * username2 record2
  *where record is the best score of player.
  *all lines are sorted in descending order relatively to record 
  */
  int record;
  std::string line;
  std::string name;
  
  if(!file)
  {
    std::cout << "File scoreboard.txt is inaccessible. New one will be created." << std::endl;
    //no file, whick mean no record
    return 0;
  }
  else
  {
    while(getline(file, line))
    {
      std::istringstream stream(line);
      stream >> name;
      //searching the player and returning his best score
      if(name == username)
      {
        stream >> record;
        return record;
      }
    }
    //return 0 if we didn't find name of user in file
    return 0;
  }
}

void User::SetRecord(const int &score)
{
  record = score;
}

void User::WriteResult()
{
  std::vector<User> users;
  
  int record;
  std::string name;
  std::string line;
  
  std::ifstream file;
  file.open("scoreboard.txt");
  
  //read off lines from scoreboard.txt 
  //and put them into vector of users.
  //also it update the record
  if(file)
  {
    while(getline(file, line))
    {
      std::istringstream stream(line);
      stream >> name;
      if(name == this->username)
      	record = this->record;
      else
        stream >> record;
      users.push_back(User(name, record));
     }
  }
  //close file after reading all information
  file.close();

  if(this->newUser)
    users.push_back(User(this->username, this->record)); 

  //sort in descending order relatively to record
  std::sort(users.begin(), users.end(), 
    [](const User a, const User & b) -> bool{ 
    return a.record > b.record; });

  //open scoreboard.txt in trunc mode to delete all information from file
  //in order to create an up-to-date scoreboard
  std::ofstream fileOut;
  fileOut.open("scoreboard.txt", std::ofstream::trunc);
  for(auto &user: users)
  {
    fileOut << user.username << " " << std::to_string(user.record) << std::endl;
  }
	fileOut.close();
}

int User::Record() const { return record; }
std::string User::Name() const { return username;}