#include "array.h"
#include "enumerable.h"


template <class Key, class T>
class Hash_Map
{
    ////////////////////////////////////////////////////////////////////////////////
    // Node Class
    ////////////////////////////////////////////////////////////////////////////////
    private:
    class Node
    {
        private:
        Key key_;
        T element_;

        public:
        Node()
        : key_(), element_()
        {}

        Node(Key key, T element)
        : key_(key), element_(element)
        {}

        Node(const Node & node)
        : key_(node.key_), element_(node.element_)
        {}

        Key get_key() const
        {
            return key_;
        }

        T & get_element()
        {
            return element_;
        }

        Node & set_element(T element)
        {
            element_ = element;
            return *this;
        }

        bool has_key(const Key & key) const
        {
            return key == key_;
        }

        friend std ::ostream & operator<<(std::ostream & o, const Node & node)
        {
            o << "(";
            o << node.key_;
            o << " => ";
            o << node.element_;
            o << ")";
            return o;
        }

    };
    ////////////////////////////////////////////////////////////////////////////////
    // Real class
    ////////////////////////////////////////////////////////////////////////////////
    private:

    Array<Enumerable<Node>> data_;
    uint64_t size_;
    uint64_t allocated_size_;

    static const uint64_t BASIC_SIZE = 20;

    public:
    Hash_Map()
    : data_(BASIC_SIZE, Enumerable<Node>()), size_(0), allocated_size_(0)
    {}

    Hash_Map(uint64_t allocated_size)
    : data_(allocated_size, Enumerable<Node>()), size_(0), allocated_size_(allocated_size)
    {}

    ////////////////////////////////////////////////////////////////////////////////
    // adding
    ////////////////////////////////////////////////////////////////////////////////

    Hash_Map & push(const Key & key,const T & elem)
    {
        Node * result = find_node(key);
        if (!result)
        {
            data_[hash(key)].push(Node(key, elem));
            ++size_;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // accessor
    ////////////////////////////////////////////////////////////////////////////////

    T & operator[](const Key & key)
    {
        Node * result = find_node(key);
        if (result)
        {
            return result->get_element();
        }
        throw std::out_of_range("Index doesn't exist");
    }

    ////////////////////////////////////////////////////////////////////////////////
    // manipulator
    ////////////////////////////////////////////////////////////////////////////////

    template<class U,class Function>
    Hash_Map<Key, U> map(Function fct)
    {
        Hash_Map<Key, U> out_map(allocated_size_);

        //data_.each([&out_map](const Enumerable<Node> & enum)
        //{
        //    enum.each([&out_map](Node & n)
        //    {
        //        out_map.push(n.get_key(), fct(n.get_key(), n.get_element()))
        //    });
        //});
        return out_map;
    }

    template<class Function>
    Hash_Map<Key, T> & each(Function fct)
    {
        //data_.each([](const Enumerable<Node> & enum)
        //{
        //    enum.each([](Node & n)
        //    {
        //        fct(n.get_key(), n.get_element());
        //    });
        //});
        return *this;

    }

    ////////////////////////////////////////////////////////////////////////////////
    // affichage
    ////////////////////////////////////////////////////////////////////////////////

    friend std ::ostream & operator<<(std::ostream & o, Hash_Map & map)
    {
        o << "{";
        uint64_t count = 0;
        if (map.size_ > 0)
        {
            for(uint64_t i = 0;i < map.data_.size(); ++i)
            {
                for(auto it = map.data_[i].begin(); it != map.data_[i].end(); ++it)
                {
                    o << *it;
                    ++count;
                    if (count != map.size_)
                    {
                        o << ", ";
                    }
                }
            }
        }
        o << "}";
        return o;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Helper
    ////////////////////////////////////////////////////////////////////////////////
    private:

    uint64_t hash(int key)
    {
        return key % data_.size();
    }

    float get_saturation()
    {
        return (float)size_ / (float)allocated_size_;
    }

    void resize()
    {
        if (get_saturation() < 0.7) return;

        Array<Node> nodes;

        allocated_size_;
    }

    Node * find_node(Key key)
    {
        uint64_t position = hash(key);
        for (auto it = data_[position].begin(); it != data_[position].end(); ++it)
        {
            if (it->has_key(key))
            {
                return &(*it);
            }
        }
        return nullptr;
    }
};
