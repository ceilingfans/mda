#pragma once
#include <vector>
#include <stdexcept>
#include <memory>
namespace mda {
    template <typename T>
    class mda
    {
        std::vector< mda<T> > children;
        size_t d;
        size_t s;
        std::unique_ptr<T> content;

        mda(std::vector<size_t>::iterator it, size_t p_d)
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

    public:

        mda()
        : d(0), s(0), content(std::make_unique<T>())
        {}
        
        mda(const mda<T>& p_mda)
        : d(p_mda.d), s(p_mda.s)
        {
            if (d == 0)
            {
                content = std::make_unique<T>(*(p_mda.content));
            }
            else
            {
                children.clear();
                children.reserve(s);
                for (size_t i=0; i<s; i++)
                {
                    children.push_back(mda<T>(p_mda[i]));
                }
            }
        }

        template <typename Any> friend class mda;
        template <typename U>
        mda(const mda<U>& p_mda)
        : d(p_mda.d), s(p_mda.s)
        {
            if (d == 0)
            {
                content = std::make_unique<T>(*(p_mda.content));
            }
            else
            {
                children.clear();
                children.reserve(s);
                for (size_t i=0; i<s; i++)
                {
                    children.push_back(mda<T>(p_mda[i]));
                }
            }
        }

        mda(std::vector<size_t> shape)
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

        const mda<T>& operator[](size_t i) const
        {
            if (d == 0)
            {
                std::string outerr = "attempted subscript of mda with dim==0";
                throw std::invalid_argument(outerr);
            }
            return children[i];
        }

        operator T&() const
        {
            if (d != 0)
            {
                std::string outerr = "attempted cast from mda with dim>0";
                throw std::invalid_argument(outerr);
            }
            return *content;
        }

        void operator=(const mda<T>& p_mda)
        {
            s = p_mda.s;
            d = p_mda.d;
            if (d == 0)
            {
                content = std::make_unique<T>(*(p_mda.content));
            }
            else
            {
                children.clear();
                children.reserve(s);
                for (size_t i=0; i<s; i++)
                {
                    children.push_back(mda<T>(p_mda[i]));
                }
            }
        }

        void operator=(mda<T>&& p_mda)
        {
            s = p_mda.s;
            d = p_mda.d;
            if (d == 0)
            {
                content = std::make_unique<T>();
                *content = *(p_mda.content);
            }
            else
            {
                children.clear();
                children.reserve(s);
                for (size_t i=0; i<s; i++)
                {
                    children.push_back(mda<T>(p_mda[i]));
                }
            }
        }

        void operator=(const T& p_content) const
        {
            if (d != 0)
            {
                std::string outerr = "attempted assignment of value to mda with dim>0";
                throw std::invalid_argument(outerr);
            }
            *content = p_content;
        }

        size_t size() const
        {
            return s;
        }

        size_t dim() const
        {
            return d;
        }
    };

}