
namespace data_structure{

template <typename T>
class UniquePtr{

public:
    UniquePtr();
    UniquePtr(T&& iPtr);
    UniquePtr operator=(const UniquePtr& iPtr) = delete;
    ~UniquePtr();

private:
    T* underlyingPtr;
};
}