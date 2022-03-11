#include <iostream>
#include <map>
#include <string>
#include <exception>

class NegativeRemCountException: public std::exception{
    const char* what() const noexcept override{
        return "Negative removing count";
    }
};

class NotFoundException: public std::exception{
    const char* what() const noexcept override{
        return "Vendor code (Art) not found";
    }
};

class RemoveMoreException: public std::exception{
    const char* what() const noexcept override{
        return "Quantity to be removed is greater than available";
    }
};

class Basket
{
private:
    std::map<std::string, int> basket;
public:
    void add(std::string inArt, int inCount){
        basket.insert(std::pair(inArt, inCount));
    }
    void remove(std::string inArt, int remCount){
        if(remCount < 0){
            throw NegativeRemCountException();
        }
        auto it = basket.find(inArt);
        if(it == basket.end()){
            throw NotFoundException();
        }
        if(it->second < remCount){
            throw RemoveMoreException();
        }
        it->second-= remCount;
    }
    void showBasket(){
        for(auto & it : basket){
            std::cout<<it.first<<" "<<it.second<<std::endl;
        }
    }


};

int main() {
    Basket b;
    std::string request;
    std::cout<<"Input please request 'show', 'add', 'remove', exit"<<std::endl;
    std::cin>>request;
    while(request != "exit"){
        if(request == "add"){
            std::string art;
            int count;
            std::cout<<"Input please vendor code and count of the product"<<std::endl;
            std::cin>>art>>count;
            b.add(art, count);
        } else if(request =="show"){
            b.showBasket();
        } else if(request =="remove"){
            std::string art;
            int count;
            std::cout<<"Input please vendor code and quantity to be removed"<<std::endl;
            std::cin>>art>>count;
            try {
                b.remove(art, count);
            }
            catch(const std::exception& x){
                std::cerr<<"Caught exception: "<<x.what()<<std::endl;
            }
        }
        std::cout<<"Input please request 'show', 'add', 'remove', exit"<<std::endl;
        std::cin >> request;
    }
    return 0;
}
