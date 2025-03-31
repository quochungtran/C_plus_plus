#ifndef UNIQUE_PTR_HPP_
#define UNIQUE_PTR_HPP_

template<class T>
class unique_ptr
{
public:
    unique_ptr(): ptr(nullptr){}
    unique_ptr(T* ptr): ptr(ptr){}
    
    unique_ptr(const unique_ptr& obj)            = delete;
    unique_ptr& operator=(const unique_ptr& obj) = delete;

    unique_ptr(unique_ptr&& dyingObj){
        // Transfer ownership of the memory pointed 
        // by dyingObj to this object
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    void operator=(unique_ptr&& dyingObj){
        __cleanup__();

        // Transfer ownership of the memory pointed by dyingObj to this object
        this->ptr    = dyingObj.ptr;
        dyingObj.ptr = nullptr; 
    }

    T* operator->(){
        return this->ptr;
    }

    T& operator*(){
        return *(this->ptr);
    }

    ~unique_ptr(){
        __cleanup__();
    };

private:
    void __cleanup__(){
        if (ptr != nullptr){
            delete ptr;
        }
    }
private:
    T* ptr = nullptr;
};


#endif  // UNIQUE_PTR_HPP_
