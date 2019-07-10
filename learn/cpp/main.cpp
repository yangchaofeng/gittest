#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include<windows.h>
using namespace std;

#include <iostream>
#include <memory>
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
	
	int Init() {std::cout << "Resource init\n";}
	int textout(std::string s) {std::cout << s << "\n";}
	 
	friend std::ostream& operator<<(std::ostream& out, const Resource &res)
	{
		out << "I am a resource\n";
		return out;
	}
};


int main(int argc, char** argv) {
	printf("yangchaofeng add for test begin ----------------------------------\n");
	
	auto ptr = std::make_unique<Resource>();
	ptr->textout("abcdef");
	ptr->Init();
	
	printf("%s %d yangchaofeng add for test ----------------------------------\n\n\n",__func__, __LINE__);
	std::unique_ptr<Resource> res(new Resource);
	res->textout("123456");
	
	auto backend = std::unique_ptr<Resource>{ std::make_unique<Resource>() };
	backend->textout("yangchaofeng");
	 
	Sleep(3000);
	printf("%s %d sleep 3 second ----------------------------------\n\n\n",__func__, __LINE__);
	
	printf("yangchaofeng add for test end ----------------------------------\n");
	return 0;
}

yangchaofeng add for test begin ----------------------------------
Resource acquired
abcdef
Resource init
main 34 yangchaofeng add for test ----------------------------------


Resource acquired
123456
Resource acquired
yangchaofeng
main 42 sleep 3 second ----------------------------------


yangchaofeng add for test end ----------------------------------
Resource destroyed
Resource destroyed
Resource destroyed




int main(int argc, char** argv) {
	printf("yangchaofeng add for test begin ----------------------------------\n");
	
	auto ptr = std::make_unique<Resource>();
	ptr->textout("abcdef");
	ptr->Init();
	
	printf("%s %d yangchaofeng add for test ----------------------------------\n\n\n",__func__, __LINE__);
	std::unique_ptr<Resource> res(new Resource);
	res->textout("123456");
	
	ptr = std::unique_ptr<Resource>{ std::make_unique<Resource>() };
	ptr->textout("yangchaofeng");
	 
	Sleep(3000);
	printf("%s %d sleep 3 second ----------------------------------\n\n\n",__func__, __LINE__);
	
	printf("yangchaofeng add for test end ----------------------------------\n");
	return 0;
}



yangchaofeng add for test begin ----------------------------------
Resource acquired
abcdef
Resource init
main 34 yangchaofeng add for test ----------------------------------


Resource acquired
123456
Resource acquired
Resource destroyed
yangchaofeng
main 42 sleep 3 second ----------------------------------


yangchaofeng add for test end ----------------------------------
Resource destroyed
Resource destroyed


