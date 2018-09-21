/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2016 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KBE_MEMORYSTREAM_H
#define KBE_MEMORYSTREAM_H

#include "common/common.h"
#include "common/objectpool.h"
#include "helper/debug_helper.h"
#include "common/memorystream_converter.h"
	
namespace KBEngine{

class MemoryStreamException
{
    public:
        MemoryStreamException(bool _add, size_t _pos, size_t _esize, size_t _size)
            : _m_add(_add), _m_pos(_pos), _m_esize(_esize), _m_size(_size)
        {
            PrintPosError();
        }

        void PrintPosError() const
        {
			ERROR_MSG(fmt::format("Attempted to {} in MemoryStream (pos:{}  size: {}).\n", 
				(_m_add ? "put" : "get"), _m_pos, _m_size));
        }
    private:
        bool 		_m_add;
        size_t 		_m_pos;
        size_t 		_m_esize;
        size_t 		_m_size;
};

/*
	将常用数据类型二进制序列化与反序列化
	注意：端与端之间传输可能涉及大小端问题，可以通过如下进行转换进行转换:
	具体看 MemoryStreamConverter.h

	使用方法:
			MemoryStream stream; 
			stream << (int64)100000000;
			stream << (uint8)1;
			stream << (uint8)32;
			stream << "kbe";
			stream.print_storage();
			uint8 n, n1;
			int64 x;
			std::string a;
			stream >> x;
			stream >> n;
			stream >> n1;
			stream >> a;
			printf("还原: %lld, %d, %d, %s", x, n, n1, a.c_str());
*/
class MemoryStream : public PoolObject
{

public:
	static ObjectPool<MemoryStream>& ObjPool();
	static void destroyObjPool();

	typedef KBEShared_ptr< SmartPoolObject< MemoryStream > > SmartPoolObjectPtr;
	static SmartPoolObjectPtr createSmartPoolObj();

	virtual size_t getPoolObjectBytes();
	virtual void onReclaimObject();

    const static size_t DEFAULT_SIZE = 0x100;

    MemoryStream(): rpos_(0), wpos_(0)
    {
        data_.reserve(DEFAULT_SIZE);
    }

    MemoryStream(size_t res): rpos_(0), wpos_(0)
    {
		if(res > 0)
		  data_.reserve(res);
    }

    MemoryStream(const MemoryStream &buf): rpos_(buf.rpos_), wpos_(buf.wpos_), data_(buf.data_) { }
	
	virtual ~MemoryStream()
	{
		clear(true);
	}
	
    void clear(bool clearData)
    {
    	if(clearData)
      	  data_.clear();

        rpos_ = wpos_ = 0;
    }

    template <typename T> void append(T value)
    {
        EndianConvert(value);
        append((uint8 *)&value, sizeof(value));
    }

    template <typename T> void put(size_t pos,T value)
    {
        EndianConvert(value);
        put(pos,(uint8 *)&value,sizeof(value));
    }
	
	void swap(MemoryStream & s)
	{
		size_t rpos = s.rpos(), wpos = s.wpos();
		std::swap(data_, s.data_);
		s.rpos(rpos_);
		s.wpos(wpos_);
		rpos_ = rpos;
		wpos_ = wpos;
	}

    MemoryStream &operator<<(uint8 value)
    {
        append<uint8>(value);
        return *this;
    }

    MemoryStream &operator<<(uint16 value)
    {
        append<uint16>(value);
        return *this;
    }

    MemoryStream &operator<<(uint32 value)
    {
        append<uint32>(value);
        return *this;
    }

    MemoryStream &operator<<(uint64 value)
    {
        append<uint64>(value);
        return *this;
    }

    MemoryStream &operator<<(int8 value)
    {
        append<int8>(value);
        return *this;
    }

    MemoryStream &operator<<(int16 value)
    {
        append<int16>(value);
        return *this;
    }

    MemoryStream &operator<<(int32 value)
    {
        append<int32>(value);
        return *this;
    }

    MemoryStream &operator<<(int64 value)
    {
        append<int64>(value);
        return *this;
    }

    MemoryStream &operator<<(float value)
    {
        append<float>(value);
        return *this;
    }

    MemoryStream &operator<<(double value)
    {
        append<double>(value);
        return *this;
    }

    MemoryStream &operator<<(const std::string &value)
    {
        append((uint8 const *)value.c_str(), value.length());
        append((uint8)0);
        return *this;
    }

    MemoryStream &operator<<(const char *str)
    {
        append((uint8 const *)str, str ? strlen(str) : 0);
        append((uint8)0);
        return *this;
    }

    MemoryStream &operator<<(COMPONENT_TYPE value)
    {
        append<int32>(value);
        return *this;
    }

    MemoryStream &operator<<(bool value)
    {
        append<int8>(value);
        return *this;
    }

    MemoryStream &operator>>(bool &value)
    {
        value = read<char>() > 0 ? true : false;
        return *this;
    }

    MemoryStream &operator>>(uint8 &value)
    {
        value = read<uint8>();
        return *this;
    }

    MemoryStream &operator>>(uint16 &value)
    {
        value = read<uint16>();
        return *this;
    }

    MemoryStream &operator>>(uint32 &value)
    {
        value = read<uint32>();
        return *this;
    }

    MemoryStream &operator>>(uint64 &value)
    {
        value = read<uint64>();
        return *this;
    }

    MemoryStream &operator>>(int8 &value)
    {
        value = read<int8>();
        return *this;
    }

    MemoryStream &operator>>(int16 &value)
    {
        value = read<int16>();
        return *this;
    }

    MemoryStream &operator>>(int32 &value)
    {
        value = read<int32>();
        return *this;
    }

    MemoryStream &operator>>(int64 &value)
    {
        value = read<int64>();
        return *this;
    }

    MemoryStream &operator>>(float &value)
    {
        value = read<float>();
        return *this;
    }

    MemoryStream &operator>>(double &value)
    {
        value = read<double>();
        return *this;
    }

    MemoryStream &operator>>(std::string& value)
    {
        value.clear();
        while (length() > 0)
        {
            char c = read<char>();
            if (c == 0 || !isascii(c))
                break;

            value += c;
        }
        
        return *this;
    }

    MemoryStream &operator>>(char *value)
    {
        while (length() > 0)
        {
            char c = read<char>();
            if (c == 0 || !isascii(c))
                break;

            *(value++) = c;
        }

		*value = '\0';
        return *this;
    }
    
    MemoryStream &operator>>(COMPONENT_TYPE &value)
    {
        value = static_cast<COMPONENT_TYPE>(read<int32>());
        return *this;
    }

    uint8 operator[](size_t pos) const
    {
        return read<uint8>(pos);
    }

    size_t rpos() const { return rpos_; }

    size_t rpos(int rpos)
    {
		if(rpos < 0)
			rpos = 0;

        rpos_ = rpos;
        return rpos_;
    }

    size_t wpos() const { return wpos_; }

    size_t wpos(int wpos)
    {
		if(wpos < 0)
			wpos = 0;

        wpos_ = wpos;
        return wpos_;
    }

    template<typename T>
    void read_skip() { read_skip(sizeof(T)); }

    void read_skip(size_t skip)
    {
        if(skip > length())
            throw MemoryStreamException(false, rpos_, skip, length());

        rpos_ += skip;
    }

    template <typename T> T read()
    {
        T r = read<T>(rpos_);
        rpos_ += sizeof(T);
        return r;
    }

    template <typename T> T read(size_t pos) const
    {
        if(sizeof(T) > length())
            throw MemoryStreamException(false, pos, sizeof(T), length());

        T val = *((T const*)&data_[pos]);
        EndianConvert(val);
        return val;
    }

    void read(uint8 *dest, size_t len)
    {
        if(len > length())
           throw MemoryStreamException(false, rpos_, len, length());

        memcpy(dest, &data_[rpos_], len);
        rpos_ += len;
    }

	ArraySize readBlob(std::string& datas)
	{
		if(length() <= 0)
			return 0;

		ArraySize rsize = 0;
		(*this) >> rsize;
		if((size_t)rsize > length())
			return 0;

		if(rsize > 0)
		{
			datas.assign((char*)(data() + rpos()), rsize);
			read_skip(rsize);
		}

		return rsize;
	}

	void appendBlob(const MemoryStream *stream)
	{
		ArraySize len = (ArraySize)stream->length();
		(*this) << len;

		if (len > 0)
			append(*stream);
	}

    uint8 *data() { return &data_[0]; }
	const uint8 *data() const { return &data_[0]; }
	
	// vector的大小
    virtual size_t size() const { return data_.size(); }

	// vector是否为空
    virtual bool empty() const { return data_.empty(); }

	// 读索引到与写索引之间的长度
	virtual size_t length() const { return rpos() >= wpos() ? 0 : wpos() - rpos(); }

	// 剩余可填充的大小
	virtual size_t space() const { return wpos() >= size() ? 0 : size() - wpos(); }

	// 将读索引强制设置到写索引，表示操作结束
	void done(){ read_skip(length()); }

    void resize(size_t newsize)
    {
        data_.resize(newsize);
        rpos_ = 0;
        wpos_ = size();
    }

    void data_resize(size_t newsize)
    {
        data_.resize(newsize);
    }

    void reserve(size_t ressize)
    {
        if (ressize > size())
            data_.reserve(ressize);
    }

    void appendBlob(const char *src, ArraySize cnt)
    {
        (*this) << cnt;

		if(cnt > 0)
			append(src, cnt);
    }

	void appendBlob(const std::string& datas)
    {
		ArraySize len = datas.size();
		(*this) << len;

		if(len > 0)
			append(datas.data(), len);
    }

    void append(const std::string& str)
    {
        append((uint8 const*)str.c_str(), str.size() + 1);
    }

    void append(const char *src, size_t cnt)
    {
        return append((const uint8 *)src, cnt);
    }

    template<class T> void append(const T *src, size_t cnt)
    {
        return append((const uint8 *)src, cnt * sizeof(T));
    }

    void append(const uint8 *src, size_t cnt)
    {
        if (!cnt)
            return;

        assert(size() < 10000000);

        if (data_.size() < wpos_ + cnt)
            data_.resize(wpos_ + cnt);

        memcpy(&data_[wpos_], src, cnt);
        wpos_ += cnt;
    }

    void append(const MemoryStream& buffer)
    {
        if(buffer.wpos()){
			append(buffer.data() + buffer.rpos(), buffer.length());
        }
    }

	void insert(size_t pos, const uint8 *src, size_t cnt)
	{
		data_.insert(data_.begin() + pos, cnt, 0);
		memcpy(&data_[pos], src, cnt);
		wpos_ += cnt;
	}

    void put(size_t pos, const uint8 *src, size_t cnt)
    {
        if(pos + cnt > size())
           throw MemoryStreamException(true, pos, cnt, size());

        memcpy(&data_[pos], src, cnt);
    }

	/** 输出流数据 */
    void print_storage() const
    {
		char buf[1024];
		std::string fbuffer;
		size_t trpos = rpos_;

		kbe_snprintf(buf, 1024, "STORAGE_SIZE: %lu, rpos=%lu.\n", (unsigned long)wpos(), (unsigned long)rpos());
		fbuffer += buf;

        for(uint32 i = rpos(); i < wpos(); ++i)
		{
			kbe_snprintf(buf, 1024, "%u ", read<uint8>(i));
			fbuffer += buf;
		}

		fbuffer += " \n";
        DEBUG_MSG(fbuffer.c_str());

		rpos_ = trpos;
    }

	/** 输出流数据字符串 */
    void textlike() const
    {
		char buf[1024];
		std::string fbuffer;
		size_t trpos = rpos_;

		kbe_snprintf(buf, 1024, "STORAGE_SIZE: %lu, rpos=%lu.\n", (unsigned long)wpos(), (unsigned long)rpos());
		fbuffer += buf;

        for(uint32 i = rpos(); i < wpos(); ++i)
		{
			kbe_snprintf(buf, 1024, "%c", read<uint8>(i));
			fbuffer += buf;
		}

		fbuffer += " \n";
        DEBUG_MSG(fbuffer.c_str());

		rpos_ = trpos;
    }

    void hexlike() const
    {
        uint32 j = 1, k = 1;
		char buf[1024];
		std::string fbuffer;
		size_t trpos = rpos_;

		kbe_snprintf(buf, 1024, "STORAGE_SIZE: %lu, rpos=%lu.\n", (unsigned long)wpos(), (unsigned long)rpos());
		fbuffer += buf;
		
		uint32 i = 0;
        for(uint32 idx = rpos(); idx < wpos(); ++idx)
        {
			++i;
            if ((i == (j * 8)) && ((i != (k * 16))))
            {
                if (read<uint8>(idx) < 0x10)
                {
					kbe_snprintf(buf, 1024, "| 0%X ", read<uint8>(idx));
					fbuffer += buf;
                }
                else
                {
					kbe_snprintf(buf, 1024, "| %X ", read<uint8>(idx));
					fbuffer += buf;
                }
                ++j;
            }
            else if (i == (k * 16))
            {
                if (read<uint8>(idx) < 0x10)
                {
					kbe_snprintf(buf, 1024, "\n0%X ", read<uint8>(idx));
					fbuffer += buf;
                }
                else
                {
					kbe_snprintf(buf, 1024, "\n%X ", read<uint8>(idx));
					fbuffer += buf;
                }

                ++k;
                ++j;
            }
            else
            {
                if (read<uint8>(idx) < 0x10)
                {
					kbe_snprintf(buf, 1024, "0%X ", read<uint8>(idx));
					fbuffer += buf;
                }
                else
                {
					kbe_snprintf(buf, 1024, "%X ", read<uint8>(idx));
					fbuffer += buf;
                }
            }
        }

		fbuffer += "\n";

		DEBUG_MSG(fbuffer.c_str());

		rpos_ = trpos;
    }

protected:
	mutable size_t rpos_, wpos_;
	std::vector<uint8> data_;
};


template <typename T>
inline MemoryStream &operator<<(MemoryStream &b, std::vector<T> v)
{
	uint32 vsize = v.size();
    b << vsize;
    for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
    {
        b << *i;
    }
    return b;
}

template <typename T>
inline MemoryStream &operator>>(MemoryStream &b, std::vector<T> &v)
{
    ArraySize vsize;
    b >> vsize;
    v.clear();
    while(vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename T>
inline MemoryStream &operator<<(MemoryStream &b, std::list<T> v)
{
	ArraySize vsize = v.size();
    b << vsize;
    for (typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i)
    {
        b << *i;
    }
    return b;
}

template <typename T>
inline MemoryStream &operator>>(MemoryStream &b, std::list<T> &v)
{
    ArraySize vsize;
    b >> vsize;
    v.clear();
    while(vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename K, typename V>
inline MemoryStream &operator<<(MemoryStream &b, std::map<K, V> &m)
{
	ArraySize vsize = m.size();
    b << vsize;
    for (typename std::map<K, V>::iterator i = m.begin(); i != m.end(); ++i)
    {
        b << i->first << i->second;
    }
    return b;
}

template <typename K, typename V>
inline MemoryStream &operator>>(MemoryStream &b, std::map<K, V> &m)
{
    ArraySize msize;
    b >> msize;
    m.clear();
    while(msize--)
    {
        K k;
        V v;
        b >> k >> v;
        m.insert(make_pair(k, v));
    }
    return b;
}

template<>
inline void MemoryStream::read_skip<char*>()
{
    std::string temp;
    *this >> temp;
}

template<>
inline void MemoryStream::read_skip<char const*>()
{
    read_skip<char*>();
}

template<>
inline void MemoryStream::read_skip<std::string>()
{
    read_skip<char*>();
}

// 从对象池中创建与回收 
#define NEW_MEMORY_STREAM() MemoryStream::ObjPool().createObject()
#define DELETE_MEMORY_STREAM(obj) { MemoryStream::ObjPool().reclaimObject(obj); obj = NULL; }

}
#endif
