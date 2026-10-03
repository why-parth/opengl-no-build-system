#ifndef GLH_Util_Header
#define GLH_Util_Header

#define COLr "\033[31m"
#define COLg "\033[32m"
#define COLy "\033[33m"
#define COLb "\033[34m"
#define COLp "\033[35m"
#define COLc "\033[36m"
#define COLw "\033[37m"
#define COLnone "\033[39m"

#define LOG if (__log__) std::cout << "\n \033[43m \033[49m " << 
#define LOGb if (__log__) std::cout << "\n \033[1;43m \033[49m " << 
#define LOGi if (__log__) std::cout << "\n \033[3;43m \033[49m " << 
#define LOGbi if (__log__) std::cout << "\n \033[1;3;43m \033[49m " << 

#define SYS if (__log__) std::cout << "\n \033[45m \033[49m " << 
#define SYSb if (__log__) std::cout << "\n \033[1;45m \033[49m " << 
#define SYSi if (__log__) std::cout << "\n \033[3;45m \033[49m " << 
#define SYSbi if (__log__) std::cout << "\n \033[1;3;45m \033[49m " << 

#define ERR if (__log__) std::cout << "\n \033[41m \033[49m " << 
#define ERRb if (__log__) std::cout << "\n \033[1;41m \033[49m " << 
#define ERRi if (__log__) std::cout << "\n \033[3;41m \033[49m " << 
#define ERRbi if (__log__) std::cout << "\n \033[1;3;41m \033[49m " << 

#define WARN if (__log__) std::cout << "\n \033[46m \033[49m " << 
#define WARNb if (__log__) std::cout << "\n \033[1;46m \033[49m " << 
#define WARNi if (__log__) std::cout << "\n \033[3;46m \033[49m " << 
#define WARNbi if (__log__) std::cout << "\n \033[1;3;46m \033[49m " << 

#define SUCC if (__log__) std::cout << "\n \033[42m \033[49m " << 
#define SUCCb if (__log__) std::cout << "\n \033[1;42m \033[49m " << 
#define SUCCi if (__log__) std::cout << "\n \033[3;42m \033[49m " << 
#define SUCCbi if (__log__) std::cout << "\n \033[1;3;42m \033[49m " << 

#define STYLEnone "\033[22;23m"
#define ALLnone "\033[0m"

#define __NAME__(_Name) COLy << _Name << COLnone

#endif