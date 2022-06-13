#include <rigpp>

extern double attr_value; // @ is 'attr_'
extern Vector attr_position;
extern Vector attr_outputPosition; 

int main()
{
    attr_outputPosition = attr_position.normalized() * attr_value;         
    return 0;
}