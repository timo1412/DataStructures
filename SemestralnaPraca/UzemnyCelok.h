#pragma once
#include <string>
using namespace std;

enum  Type
{
	KRAJINA,KRAJ,OKRES,OBEC
};

 class UzemnyCelok
{
private:

	int number;
	string code;
	string title;
	string medTitle;
	string shortTitle;
	string note;
	Type type;
	int parrentIndex;
public:
	UzemnyCelok(int p_number, string p_code, string p_title, string p_medTitle, string p_shortTitle, string p_note, Type type) :
		number(p_number), code(p_code), title(p_title), medTitle(p_medTitle), shortTitle(p_shortTitle), note(p_note)
	,type(type)
	{
	}
	UzemnyCelok() {};
	int getNumber() { return this->number; }
	string getCode() { return this->code; }
	string getTitle() { return this->title; }
	string getMedTitle() { return this->medTitle; }
	string getShortTitle() { return this->shortTitle; }
	string getNote() { return this->note; }
	Type getType() { return this->type; }
	bool hasType(Type p_type) { return this->type == p_type; }
	bool operator==(const UzemnyCelok other	) const
	{
		return this->code == other.code;
	}
	bool operator!=(const UzemnyCelok other) const
	{
		return this->code != other.code;
	}
};




