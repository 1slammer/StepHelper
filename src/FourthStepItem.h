#include <string>

using namespace std;


class FourthStepItem
{
public:
   string get_person();
   void set_person(string person);
   string get_the_cause();
   void set_the_cause(string cause);
   string get_my_part();
   void set_my_part(string my_part_in);
   string get_threat();
   void set_threat(string threat);
private:
   string person;
   string the_cause;
   string part_threatened;
   string my_part;
   
};
