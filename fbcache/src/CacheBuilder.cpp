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

    virtual flatbuffers::Offset<FlatBufferRoot> pack() const {
        return FlatBufferRoot::Pack(_fbBuilder, &_root);
    }

    void toOutputStream(std::ostream& oOutput) const override{
        _fbBuilder.Finish(pack());
        auto detachedBuffer = _fbBuilder.Release();
        oOutput.write(reinterpret_cast<char*>(detachedBuffer.data()), 
                    detachedBuffer.size());
        _fbBuilder.Clear();
    }

    

protected:
    FlatBufferRootT _root;
private:
    mutable flatbuffers::FlatBufferBuilder _fbBuilder;
};
} // namespace fbcache