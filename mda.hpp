#pragma once
#include <vector>
#include <memory>
namespace mda {
    template <typename T>
    class mda
    {
        std::vector< mda<T> > children;
        size_t d;
        size_t s;
        std::unique_ptr<T> content;
        mda(std::vector<size_t>::iterator it, size_t p_d);
    public:
        mda(); // calls default constructor of T
        mda(std::vector<size_t> shape); // multidimensional array with lengths shape[0], shape[1], ...
        const mda& operator[](size_t i) const; // access but not reassign entire mda
        operator T&() const; // access content of 0d mda
        void operator=(const T& p_content) const; // assign content of mda to p_content
        size_t size() const; // length of mda
        size_t dim() const; // dimensions of mda
        template <typename U> friend mda<U> copy(const mda<U>& p_mda);
    };

    template <typename T>
    mda<T>::mda()
    : d(0), s(0), content(std::make_unique<T>())
    {}

    template <typename T>
    mda<T>::mda(std::vector<size_t> shape)
    : d(shape.size())
    {
        if (d != 0)
        {
            std::vector<size_t>::iterator it = shape.begin();
            s = *it;
            children.reserve(s);
            if (d != 1)
            {
                it++;
            }
            for (size_t i=0; i<s; i++)
            {
                children.push_back(mda<T>(it, d-1));
            }
            content = nullptr;
        }
        else
        {
            s = 0;
            content = std::make_unique<T>();
        }
    }

    template <typename T>
    mda<T>::mda(std::vector<size_t>::iterator it, size_t p_d)
    : d(p_d)
    {
        if (d != 0)
        {
            s = *it;
            children.reserve(s);
            if (d != 1)
            {
                it++;
            }
            for (size_t i=0; i<s; i++)
            {
                children.push_back(mda<T>(it, d-1));
            }
            content = nullptr;
        }
        else
        {
            s = 0;
            content = std::make_unique<T>();
        }
    }

    template <typename T>
    const mda<T>& mda<T>::operator[](size_t i) const
    {
        if (d == 0)
        {
            std::exit(1);
        }
        return children[i];
    }

    template <typename T>
    mda<T>::operator T&() const
    {
        if (d != 0)
        {
            std::exit(1);
        }
        return *content;
    }

    template <typename T>
    void mda<T>::operator=(const T& p_content) const
    {
        if (d != 0)
        {
            std::exit(1);
        }
        *content = p_content;
    }

    template <typename T>
    size_t mda<T>::size() const
    {
        return s;
    }

    template <typename T>
    size_t mda<T>::dim() const
    {
        return d;
    }

    template <typename T>
    mda<T> copy(const mda<T>& p_mda) // copy all contents of given mda
    {
        mda<T> outmda;
        if (outmda.dim() == 0)
        {
            *(outmda.content) = *(p_mda.content);
        }
        else
        {
            for (size_t i=0; i<p_mda.size(); i++)
            {
                outmda.children.push_back(copy<T>(p_mda[i]));
            }
        }
        return outmda;
    }
}