#ifndef BOOST_ITERATOR_FACADE_ITERATOR_FACADE_HPP
#define BOOST_ITERATOR_FACADE_ITERATOR_FACADE_HPP

#include <utility>
#include <iterator>


namespace boost { namespace iterator_facade {

    template<
        typename Derived,
        typename IteratorCategory,
        typename ValueType,
        typename Reference = ValueType &,
        typename Pointer = ValueType *,
        typename DifferenceType = std::ptrdiff_t>
    struct iterator_facade;

    struct access
    {
        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static auto
        dereference(iterator_facade<
                    Derived,
                    IteratorCategory,
                    ValueType,
                    Reference,
                    Pointer,
                    DifferenceType> const &
                        it) noexcept(noexcept(derived(it).dereference()))
        {
            return derived(it).dereference();
        }

        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static auto equals(
            iterator_facade<
                Derived,
                IteratorCategory,
                ValueType,
                Reference,
                Pointer,
                DifferenceType> const & lhs,
            iterator_facade<
                Derived,
                IteratorCategory,
                ValueType,
                Reference,
                Pointer,
                DifferenceType> const &
                rhs) noexcept(noexcept(derived(lhs).equals(derived(rhs))))
        {
            return derived(lhs).equals(derived(rhs));
        }

        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static auto
        next(iterator_facade<
             Derived,
             IteratorCategory,
             ValueType,
             Reference,
             Pointer,
             DifferenceType> & it) noexcept(noexcept(derived(it).next()))
        {
            derived(it).next();
        }

        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static auto
        prev(iterator_facade<
             Derived,
             IteratorCategory,
             ValueType,
             Reference,
             Pointer,
             DifferenceType> & it) noexcept(noexcept(derived(it).prev()))
        {
            derived(it).prev();
        }

        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static auto advance(
            iterator_facade<
                Derived,
                IteratorCategory,
                ValueType,
                Reference,
                Pointer,
                DifferenceType> & it,
            DifferenceType diff) noexcept(noexcept(derived(it).advance(diff)))
        {
            derived(it).advance(diff);
        }

        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static auto compare(
            iterator_facade<
                Derived,
                IteratorCategory,
                ValueType,
                Reference,
                Pointer,
                DifferenceType> & it1,
            iterator_facade<
                Derived,
                IteratorCategory,
                ValueType,
                Reference,
                Pointer,
                DifferenceType> & it2) noexcept(noexcept(derived(it1)
                                                             .compare(it2)))
        {
            derived(it1).compare(it2);
        }

        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static Derived & derived(iterator_facade<
                                           Derived,
                                           IteratorCategory,
                                           ValueType,
                                           Reference,
                                           Pointer,
                                           DifferenceType> & if_) noexcept
        {
            return static_cast<Derived &>(if_);
        }
        template<
            typename Derived,
            typename IteratorCategory,
            typename ValueType,
            typename Reference,
            typename Pointer,
            typename DifferenceType>
        constexpr static Derived const &
        derived(iterator_facade<
                Derived,
                IteratorCategory,
                ValueType,
                Reference,
                Pointer,
                DifferenceType> const & if_) noexcept
        {
            return static_cast<Derived const &>(if_);
        }
    };

    // TODO: In which category do we introduce operator->?

    template<
        typename Derived,
        typename ValueType,
        typename Reference,
        typename Pointer,
        typename DifferenceType>
    struct iterator_facade<
        Derived,
        std::input_iterator_tag,
        ValueType,
        Reference,
        Pointer,
        DifferenceType>
    {
#if 0 // TODO: Define these, or just let the machinery of ITER_CONCEPT() pick
      // them up?
        using iterator_concept = std::input_iterator_tag;
#endif
        using iterator_category = std::input_iterator_tag;
        using value_type = ValueType;
        using reference = Reference;
        using pointer = void;
        using difference_type = DifferenceType;

        constexpr value_type operator*() const
            noexcept(noexcept(access::dereference(*this)))
        {
            return access::dereference(*this);
        }

        constexpr Derived & operator++() noexcept(noexcept(access::next(*this)))
        {
            access::next(*this);
            return access::derived(*this);
        }
        constexpr Derived operator++(int)noexcept(
            noexcept(Derived(access::derived(*this)), access::next(*this)))
        {
            Derived retval = access::derived(*this);
            access::next(*this);
            return retval;
        }

        // TODO: noexcept throughout.
        friend constexpr auto operator==(Derived lhs, Derived rhs) noexcept(
            noexcept(access::equals(lhs, rhs)))
        {
            return access::equals(lhs, rhs);
        }
        friend constexpr auto
        operator!=(Derived lhs, Derived rhs) noexcept(noexcept(lhs == rhs))
        {
            return !(lhs == rhs);
        }
    };

    template<
        typename Derived,
        typename ValueType,
        typename Reference,
        typename Pointer,
        typename DifferenceType>
    struct iterator_facade<
        Derived,
        std::forward_iterator_tag,
        ValueType,
        Reference,
        Pointer,
        DifferenceType>
    {
        using iterator_category = std::forward_iterator_tag;
        using value_type = ValueType;
        using reference = Reference;
        using pointer = Pointer;
        using difference_type = DifferenceType;

        constexpr reference operator*() const
            noexcept(noexcept(access::dereference(*this)))
        {
            return access::dereference(*this);
        }

        constexpr Derived & operator++() noexcept(noexcept(access::next(*this)))
        {
            access::next(*this);
            return access::derived(*this);
        }
        constexpr Derived operator++(int)noexcept(
            noexcept(Derived(access::derived(*this)), access::next(*this)))
        {
            Derived retval = access::derived(*this);
            access::next(*this);
            return retval;
        }

        friend constexpr auto operator==(Derived lhs, Derived rhs) noexcept(
            noexcept(access::equals(lhs, rhs)))
        {
            return access::equals(lhs, rhs);
        }
        friend constexpr auto
        operator!=(Derived lhs, Derived rhs) noexcept(noexcept(lhs == rhs))
        {
            return !(lhs == rhs);
        }
    };

    template<
        typename Derived,
        typename ValueType,
        typename Reference,
        typename Pointer,
        typename DifferenceType>
    struct iterator_facade<
        Derived,
        std::bidirectional_iterator_tag,
        ValueType,
        Reference,
        Pointer,
        DifferenceType>
    {
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = ValueType;
        using reference = Reference;
        using pointer = Pointer;
        using difference_type = DifferenceType;

        constexpr reference operator*() const
            noexcept(noexcept(access::dereference(*this)))
        {
            return access::dereference(*this);
        }

        constexpr Derived & operator++() noexcept(noexcept(access::next(*this)))
        {
            access::next(*this);
            return access::derived(*this);
        }
        constexpr Derived operator++(int)noexcept(
            noexcept(Derived(access::derived(*this)), access::next(*this)))
        {
            Derived retval = access::derived(*this);
            access::next(*this);
            return retval;
        }

        constexpr Derived & operator--() noexcept(noexcept(access::prev(*this)))
        {
            access::prev(*this);
            return access::derived(*this);
        }
        constexpr Derived operator--(int)noexcept(
            noexcept(Derived(access::derived(*this)), access::prev(*this)))
        {
            Derived retval = access::derived(*this);
            access::prev(*this);
            return retval;
        }

        friend constexpr auto operator==(Derived lhs, Derived rhs) noexcept(
            noexcept(access::equals(lhs, rhs)))
        {
            return access::equals(lhs, rhs);
        }
        friend constexpr auto
        operator!=(Derived lhs, Derived rhs) noexcept(noexcept(lhs == rhs))
        {
            return !(lhs == rhs);
        }
    };

    template<
        typename Derived,
        typename ValueType,
        typename Reference,
        typename Pointer,
        typename DifferenceType>
    struct iterator_facade<
        Derived,
        std::random_access_iterator_tag,
        ValueType,
        Reference,
        Pointer,
        DifferenceType>
    {
        using iterator_category = std::random_access_iterator_tag;
        using value_type = ValueType;
        using reference = Reference;
        using pointer = Pointer;
        using difference_type = DifferenceType;

        constexpr reference operator*() const
            noexcept(noexcept(access::dereference(*this)))
        {
            return access::dereference(*this);
        }
        constexpr reference operator[](difference_type i) const
            noexcept(noexcept(
                Derived(access::derived(*this)),
                access::advance(*this, i),
                access::dereference(*this)))
        {
            Derived copy = access::derived(*this);
            access::advance(copy, i);
            return access::dereference(copy);
        }

        constexpr Derived & operator++() noexcept(
            noexcept(access::advance(*this, difference_type(1))))
        {
            access::advance(*this, difference_type(1));
            return access::derived(*this);
        }
        constexpr Derived operator++(int)noexcept(noexcept(
            Derived(access::derived(*this)),
            access::advance(*this, difference_type(1))))
        {
            Derived retval = access::derived(*this);
            access::advance(*this, difference_type(1));
            return retval;
        }
        constexpr Derived & operator+=(difference_type i) noexcept(
            noexcept(access::advance(*this, i)))
        {
            access::advance(*this, i);
            return *this;
        }

        constexpr Derived operator+(difference_type i) noexcept(noexcept(
            Derived(access::derived(*this)), access::advance(*this, i)))
        {
            Derived copy = access::derived(*this);
            access::advance(copy, i);
            return copy;
        }
        friend constexpr Derived
        operator+(difference_type i, Derived it) noexcept(
            noexcept(Derived(access::derived(it)), access::advance(it, i)))
        {
            Derived copy = access::derived(it);
            access::advance(copy, i);
            return copy;
        }

        constexpr Derived & operator--() noexcept(
            noexcept(access::advance(*this, difference_type(-1))))
        {
            access::advance(*this, difference_type(-1));
            return access::derived(*this);
        }
        constexpr Derived operator--(int)noexcept(noexcept(
            Derived(access::derived(*this)),
            access::advance(*this, difference_type(-1))))
        {
            Derived retval = access::derived(*this);
            access::advance(*this, difference_type(-1));
            return retval;
        }
        constexpr Derived & operator-=(difference_type i) noexcept(
            noexcept(access::advance(*this, -i)))
        {
            access::advance(*this, -i);
            return *this;
        }

        constexpr Derived operator-(difference_type i) noexcept(noexcept(
            Derived(access::derived(*this)), access::advance(*this, -i)))
        {
            Derived copy = access::derived(*this);
            access::advance(copy, -i);
            return copy;
        }

        friend constexpr Derived
        operator-(Derived it1, Derived it2) noexcept(noexcept(it1.comp(it2)))
        {
            return it1.comp(it2);
        }

        friend constexpr auto operator==(Derived lhs, Derived rhs) noexcept(
            noexcept((lhs.comp(rhs) == difference_type(0))))
        {
            return lhs.comp(rhs) == difference_type(0);
        }
        friend constexpr auto operator!=(Derived lhs, Derived rhs) noexcept(
            noexcept((lhs.comp(rhs) != difference_type(0))))
        {
            return lhs.comp(rhs) != difference_type(0);
        }
        friend constexpr auto operator<(Derived lhs, Derived rhs) noexcept(
            noexcept((lhs.comp(rhs) < difference_type(0))))
        {
            return lhs.comp(rhs) < difference_type(0);
        }
        friend constexpr auto operator<=(Derived lhs, Derived rhs) noexcept(
            noexcept((lhs.comp(rhs) <= difference_type(0))))
        {
            return lhs.comp(rhs) <= difference_type(0);
        }
        friend constexpr auto operator>(Derived lhs, Derived rhs) noexcept(
            noexcept((lhs.comp(rhs) > difference_type(0))))
        {
            return lhs.comp(rhs) > difference_type(0);
        }
        friend constexpr auto operator>=(Derived lhs, Derived rhs) noexcept(
            noexcept((lhs.comp(rhs) >= difference_type(0))))
        {
            return lhs.comp(rhs) >= difference_type(0);
        }

    private:
        friend boost::iterator_facade::access;

        constexpr difference_type comp(iterator_facade it2) const
            noexcept(noexcept(access::compare(*this, it2)))
        {
            return access::compare(*this, it2);
        }
    };

}}

#endif
