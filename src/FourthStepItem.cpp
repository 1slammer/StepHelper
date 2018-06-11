#include "FourthStepItem.h"


string FourthStepItem::get_person(){
	return this->person;
}
void FourthStepItem::set_person(string person){
	this->person = person;
}
string FourthStepItem::get_the_cause(){
	return this->the_cause;
}
void FourthStepItem::set_the_cause(string cause){
	this->the_cause = cause;
}
string FourthStepItem::get_my_part(){
	return this->my_part;
}
void FourthStepItem::set_my_part(string my_part_in){
	this->my_part = my_part_in;
}
string FourthStepItem::get_threat(){
	return this->part_threatened;
}
void FourthStepItem::set_threat(string threat){
	this->part_threatened = threat;
}