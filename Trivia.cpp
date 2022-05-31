/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
//#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T> class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename = DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double,
  // string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double,
  //       string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all
  // subjects in m_subjects and allows use to choose one. Returns value - 1
  // (location in vector) Precondition: A Subject exists. Postcondition: Returns
  // value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the
  // subject passed into function Precondition: A Subject exists. Postcondition:
  // Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();

private:
  Lqueue<Question<T> *>
      *m_questions;          // Holds questions using a specific data type
  vector<string> m_subjects; // Populated as file is loaded
};

/*
** File:    Trivia.cpp
** Project: CMSC 202 Project 5, Spring 2022
** Author:  Ben Maher
** Date:    5/7/22
** Section: 50/52
** E-mail:  bmaher1@umbc.edu
*/

// queue of pointers
// we have a pointer that points at this queue to retrieve data etc
template <class T> Trivia<T>::Trivia(string filename) {
  m_questions = new Lqueue<Question<T> *>();
  DisplayTitle();
  LoadQuestions(filename);
  MainMenu();
}

template <class T> Trivia<T>::~Trivia() {
  // deleting nodes in a queue
  while (!m_questions->IsEmpty()) {
    Question<T> *firstEle = m_questions->Pop();
    delete firstEle;
  }
  delete m_questions;
}

template <class T> bool Trivia<T>::LoadQuestions(string filename) {
  ifstream infile;
  infile.open(filename);
  // check to see if the file loaded
  if (infile.fail()) {
    cout << "Your file didn't work. ";
  } else {
    string fileLine;
    // subject,question,tyeOfAnswer,questionDiff,answer
    // loop through fileline checking for delimiters
    while (getline(infile, fileLine)) {
      int firstCommaIndex = fileLine.find(DELIMITER);
      string subject = fileLine.substr(0, firstCommaIndex);

      int secondCommaIndex = fileLine.find(DELIMITER, firstCommaIndex + 1);
      string question = (fileLine.substr(
          firstCommaIndex + 1, secondCommaIndex - firstCommaIndex - 1));

      int thirdCommaIndex = fileLine.find(DELIMITER, secondCommaIndex + 1);
      string datatype = fileLine.substr(secondCommaIndex + 1,
                                        thirdCommaIndex - secondCommaIndex - 1);

      int fourthCommaIndex = fileLine.find(DELIMITER, thirdCommaIndex + 1);
      int difficulty = stoi(fileLine.substr(
          thirdCommaIndex + 1, fourthCommaIndex - thirdCommaIndex - 1));

      string answer = fileLine.substr(fourthCommaIndex + 1,
                                      fileLine.size() - fourthCommaIndex - 1);

      stringstream ss(answer);

      T ans;

      ss >> ans;
      // Question pointer to store constructor arguments
      Question<T> *newQuestionPtr =
          new Question<T>(subject, question, datatype, difficulty, ans);
      bool isNewSubject = true;
      for (uint i = 0; i < m_subjects.size(); i++) {
        if (subject.compare(m_subjects[i]) == 0) {
          isNewSubject = false;
        }
      }
      if (isNewSubject) {
        m_subjects.push_back(subject);
      }
      // insert file data into m_questions
      m_questions->Push(newQuestionPtr);
    }
  }
  infile.close();
  return true;
}

template <class T> void Trivia<T>::MainMenu() {
  // remains true while the loop is running
  bool continueLoop = true;
  do {
    int userInput;
    cout << "Choose an option." << endl;
    cout << "1. Display Subjects" << endl;
    cout << "2. Start Subject" << endl;
    cout << "3. Quit" << endl;
    cin >> userInput;
    if (userInput <= 0 || userInput > 3) {
      cout << "Please enter a valid option." << endl;
    } else if (userInput == 1) {
      DisplaySubjects();
    } else if (userInput == 2) {
      StartSubject();
    } else if (userInput == 3) {
      cout << "Thank you trying UMBC Trivia!" << endl;
      continueLoop = false;
    }
  } while (continueLoop);
}

template <class T> void Trivia<T>::DisplaySubjects() {
  // loop to display subjects
  if (m_subjects.size() == 0) {
    return;
  }
  cout << "Possible Subjects: " << endl;
  for (uint i = 0; i < m_subjects.size(); i++) {
    cout << i + 1 << ". " << m_subjects[i] << endl;
  }
}

template <class T> void Trivia<T>::StartSubject() {
  int index = ChooseSubject();
  // store the user picked subject
  string subject = m_subjects[index];
  cout << "There are " << QuestionsPerSubject(subject)
       << " questions in this subject." << endl;
  int totalQuestions = 0;
  int totalQuestionsRight = 0;
  for (uint i = m_questions->GetSize(); i > 0; i--) {
    Question<T> *questionPtr = m_questions->Pop();
    // if the queston has not been answered yet
    if (questionPtr->m_subject.compare(subject) == 0) {
      cout << totalQuestions + 1 << ". Question: " << questionPtr->m_question
           << endl;
      cout << "Please answer with a(n) " << questionPtr->m_datatype << ". "
           << endl
           << endl;
      ;
      totalQuestions++;
      T answer;
      cin >> answer;
      // increment for each right answer
      if (questionPtr->CheckAnswer(answer)) {
        totalQuestionsRight++;
        cout << "Correct" << endl;
      } else {
        cout << "Incorrect" << endl;
      }
    }
    m_questions->Push(questionPtr);
    if (totalQuestions == QuestionsPerSubject(subject)) {
      break;
    }
  }
  cout << "You got " << totalQuestionsRight << " answers correct." << endl;
  cout << "You got " << totalQuestions - totalQuestionsRight
       << " answers incorrect." << endl;
  // percent of questions correct out of 100%
  float percentCorrect = (float)totalQuestionsRight / totalQuestions;
  // cout << setprecision(2);
  cout << "Which is a " << percentCorrect * 100 << "%." << endl;
}

template <class T> void Trivia<T>::AddSubject(string subject) {
  for (int i = 0; i < m_subjects.size(); i++) {
    // check if they are the same or just return to exit out of the function
    if (m_subjects[i].compare(subject) == 0) {
      return;
    }
  }
  m_subjects.push_back(subject);
}

template <class T> int Trivia<T>::ChooseSubject() {
  int userInput;
  cout << "What subject would you like to attempt? " << endl;
  cout << "Possible Subjects: " << endl;
  //display subjects for user to choose
  for (uint i = 0; i < m_subjects.size(); i++) {
    cout << i + 1 << ". " << m_subjects[i] << endl;
  }
  cin >> userInput;
  return userInput - 1;
}
template <class T> int Trivia<T>::QuestionsPerSubject(string subject) {
  int counter = 0;
  for (int i = 0; i < m_questions->GetSize(); i++) {
    // loop to count the number of subjects
    Question<T> *questionPtr = m_questions->Pop();
    if (questionPtr->m_subject.compare(subject) == 0) {
      counter++;
    }
    m_questions->Push(questionPtr);
  }
  return counter;
}

template <class T> void Trivia<T>::DisplayTitle() {
  cout << "Welcome to UMBC Trivia!" << endl;
}
#endif
