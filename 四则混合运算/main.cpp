#include"expression_evaluator.h"
void my_test()
{	
std::vector<std::string> test (25); 
 test[0]="((3+45)/2";    
 test[1]="(2+3)>";        
 test[2]="2*0.34/0.00+2"; 
 test[3]="1+3.0/0";
 test[4]="((4.34))"; 
 test[5]="*23.92+45.23-2";
 test[6]=")3+2-9";        
 test[7]="(1.23+3.45)*";   
 test[8]="(1.23+4)/(3.44++6)";  
 test[9]="(3.4-2)(2.3+4)";
 test[10]="(3.4-2)5(2.3+4)"; 
 test[11]="(3.4-2)5";
 test[12]="(3.55)";       
 test[13]="(3+2)/(*2)";  
 test[14]="3*2.3+0..3/3*6";  
 test[15]="3.+24/12";     
 test[16]="0.23.45+1/5.2"; 
 test[17]="23+8-2.1+2-1-0.34"; 
 test[18]="3*2.3+2.3/2*6-2.3";      
 test[19]="(2+0.25*2)/(10/8)";
 test[20]="1/(1.0+8/2)";
 test[21]="(((3+2)*0.5)+(2-1.5)/0.5)+3";
 test[22]="(((3+2/5)))";
 test[23]="((2/45+2)+1.23-3.23)/2*(3.2/0.05)+(((0.5-0.25)*10-3))"; 
 test[24]="2+1+(1+1)*(2-(3*2))"; 
 
 for(auto &x:test){
    std::vector<char>_test; 
    std::stack<char>pre; 
    int i=check_and_convert(x,pre,_test);
    if(!i) 
	    std::cout<<"ILLEGAL"<<std::endl;  
    else {
	    float result=calculate(_test);
        std::cout<<"The result is : "<<result<<std::endl;	
    }
 }
}
int main()
{
	std::string your_input;
	std::vector<char>_test;
    std::stack<char>pre;
    
	my_test();
    std::cout<<"Input : "<<std::endl;
    std::cin>>your_input;
    
    int i=check_and_convert(your_input,pre,_test);
    if(!i) 
	    std::cout<<"ILLEGAL"<<std::endl;  
    else {
	    float result=calculate(_test);
        std::cout<<"Your result is : "<<result<<std::endl;	
    }
	return 0;	
}
