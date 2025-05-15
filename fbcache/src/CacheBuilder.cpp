#include <flatbuffers/flatbuffers.h>
#include <iostream>

namespace fbcache {

class CacheBuiderBase{
    public:
        /**
         * Writes the serialized data to the output stream, implement in concrete implementation of the class
         * @param aOutput the output stream to write the data to.
         */
        virtual void toOutputStream(std::ostream aOutputfile) const = 0;
        virtual ~CacheBuiderBase()                                  = default;
};

template <typename FlatBufferRootT>
class CacheBuilder: public CacheBuiderBase{
    using FlatBufferRoot = typename FlatBufferRootT::TableType;

protected:
    FlatBufferRootT _root;
private:
    mutable flatbuffers::FlatBufferBuilder _fbBuilder;
};
} // namespace fbcache