#pragma once
#include <string>
using namespace std;
class UzemnyCelok
{
private:
	int number;
	string code;
	string title;
	string medTitle;
	string shortTitle;
	string note;
public:
	UzemnyCelok(int p_number, string p_code, string p_title, string p_medTitle, string p_shortTitle, string p_note) :
		number(p_number), code(p_code), title(p_title), medTitle(p_medTitle), shortTitle(p_shortTitle), note(p_note) {}
	int getNumber() { return this->number; }
	string getCode() { return this->code; }
	string getTitle() { return this->title; }
	string getMedTitle() { return this->medTitle; }
	string getShortTitle() { return this->shortTitle; }
	string getNote() { return this->note; }
};

