// -*- C++ -*-
//===--------------------------- updatable_priority_queue ------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _PEW_UPQ
#define _PEW_UPQ

/*
    queue synopsis

namespace pewulfman
{

class updatable_priority_queue
{
public:
    typedef Container                                container_type;
    typedef Map                                      map_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;
    map_type m;
    Compare comp;

public:
    updatable_priority_queue() = default;
    ~updatable_priority_queue() = default;

    updatable_priority_queue(const priority_queue& q) = default;
    updatable_priority_queue(priority_queue&& q) = default;

    updatable_priority_queue& operator=(const priority_queue& q) = default;
    updatable_priority_queue& operator=(priority_queue&& q) = default;

    explicit updatable_priority_queue(const Compare& comp);
    updatable_priority_queue(const Compare& comp, const container_type& c);
    explicit updatable_priority_queue(const Compare& comp, container_type&& c);
    template <class InputIterator>
        updatable_priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp = Compare());
    template <class InputIterator>
        updatable_priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp, const container_type& c);
    template <class InputIterator>
        updatable_priority_queue(InputIterator first, InputIterator last,
                       const Compare& comp, container_type&& c);
    template <class Alloc>
        explicit updatable_priority_queue(const Alloc& a);
    template <class Alloc>
        updatable_priority_queue(const Compare& comp, const Alloc& a);
    template <class Alloc>
        updatable_priority_queue(const Compare& comp, const container_type& c,
                       const Alloc& a);
    template <class Alloc>
        updatable_priority_queue(const Compare& comp, container_type&& c,
                       const Alloc& a);
    template <class Alloc>
        updatable_priority_queue(const priority_queue& q, const Alloc& a);
    template <class Alloc>
        updatable_priority_queue(priority_queue&& q, const Alloc& a);

    bool            empty() const;
    size_type       size() const;
    const_reference top() const;

    void push(const value_type& v);
    void push(value_type&& v);
    template <class... Args> void emplace(Args&&... args);
    void pop();
    void update_priority(_Value, _Tp);
    void update_priority(value_type&);

    void swap(priority_queue& q)
        noexcept(is_nothrow_swappable_v<Container> &&
                 is_nothrow_swappable_v<Comp>)
};

template <class Compare, class Container>
updatable_priority_queue(Compare, Container)
    -> updatable_priority_queue<typename Container::value_type, Container, Compare>; // C++17
  
template<class InputIterator, 
         class Compare = less<typename iterator_traits<InputIterator>::value_type>,
         class Container = vector<typename iterator_traits<InputIterator>::value_type>>
updatable_priority_queue(InputIterator, InputIterator, Compare = Compare(), Container = Container())
    -> updatable_priority_queue<typename iterator_traits<InputIterator>::value_type, Container, Compare>; // C++17
  
template<class Compare, class Container, class Allocator>
updatable_priority_queue(Compare, Container, Allocator)
    -> updatable_priority_queue<typename Container::value_type, Container, Compare>; // C++17

template <class T, class Container, class Compare>
  void swap(updatable_priority_queue<T, Container, Compare>& x,
            updatable_priority_queue<T, Container, Compare>& y)
            noexcept(noexcept(x.swap(y)));

}  // std

*/

#include "__config"
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif
using namespace std;
namespace pewulfman
{
    template <class _Value, class _Tp, class _Container = vector<pair< _Value, _Tp>>,
             class _Compare = less<typename _Container::value_type::second_type>,
             class _Map = unordered_map< _Value,typename iterator_traits<typename _Container::iterator>::difference_type>>
    class updatable_priority_queue
    {
        public:
            typedef _Container                               container_type;
            typedef _Compare                                 value_compare;
            typedef _Map                                     map_type;
            typedef typename container_type::value_type      value_type;
            typedef typename container_type::reference       reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::size_type       size_type;
            typedef typename container_type::iterator        iter_type;
            typedef typename iterator_traits<iter_type>::difference_type diff_type;
            //static_assert((is_same<_Tp, value_type::second_type>::value), "" );

        protected:
            container_type c;
            map_type m;
            value_compare comp;

        public:
            updatable_priority_queue() _NOEXCEPT_(is_nothrow_default_constructible<container_type>::value &&
                        is_nothrow_default_constructible<map_type>::value    &&
                        is_nothrow_default_constructible<value_compare>::value)
                : c(), m(), comp() {}

            updatable_priority_queue(const updatable_priority_queue& __q) : c(__q.c), m(__q.m), comp(__q.comp) {}

            updatable_priority_queue& operator=(const updatable_priority_queue& __q)
            {c = __q.c; m= __q.m; comp = __q.comp; return *this;}

#ifndef _LIBCPP_CXX03_LANG
            updatable_priority_queue(updatable_priority_queue&& __q)
                _NOEXCEPT_(is_nothrow_move_constructible<container_type>::value &&
                        is_nothrow_move_constructible<map_type>::value &&
                        is_nothrow_move_constructible<value_compare>::value)
                : c(move(__q.c)), m(move(__q.m)), comp(move(__q.comp)) {}

            updatable_priority_queue& operator=(updatable_priority_queue&& __q)
            _NOEXCEPT_(is_nothrow_move_assignable<container_type>::value &&
                is_nothrow_move_assignable<map_type>::value &&
                is_nothrow_move_assignable<value_compare>::value)
            {c = move(__q.c); m=move(__q.comp); comp = move(__q.comp); return *this;}
#endif  // _LIBCPP_CXX03_LANG

                explicit updatable_priority_queue(const value_compare& __comp)
                : c(), comp(__comp), m() {}
                updatable_priority_queue(const value_compare& __comp, const container_type& __c);
#ifndef _LIBCPP_CXX03_LANG
                explicit updatable_priority_queue(const value_compare& __comp, container_type&& __c);
#endif
                template <class _InputIter>
                updatable_priority_queue(_InputIter __f, _InputIter __l,
                    const value_compare& __comp = value_compare());
                template <class _InputIter>
                updatable_priority_queue(_InputIter __f, _InputIter __l,
                    const value_compare& __comp, const container_type& __c);
#ifndef _LIBCPP_CXX03_LANG
                template <class _InputIter>
                    updatable_priority_queue(_InputIter __f, _InputIter __l,
                            const value_compare& __comp, container_type&& __c);
#endif  // _LIBCPP_CXX03_LANG
                template <class _Alloc>
                    explicit updatable_priority_queue(const _Alloc& __a,
                            typename enable_if<uses_allocator<container_type,
                            _Alloc>::value>::type* = 0);
                template <class _Alloc>
                    updatable_priority_queue(const value_compare& __comp, const _Alloc& __a,
                            typename enable_if<uses_allocator<container_type,
                            _Alloc>::value>::type* = 0);
                template <class _Alloc>
                    updatable_priority_queue(const value_compare& __comp, const container_type& __c,
                            const _Alloc& __a,
                            typename enable_if<uses_allocator<container_type,
                            _Alloc>::value>::type* = 0);
                template <class _Alloc>
                    updatable_priority_queue(const updatable_priority_queue& __q, const _Alloc& __a,
                            typename enable_if<uses_allocator<container_type,
                            _Alloc>::value>::type* = 0);
#ifndef _LIBCPP_CXX03_LANG
                template <class _Alloc>
                    updatable_priority_queue(const value_compare& __comp, container_type&& __c,
                            const _Alloc& __a,
                            typename enable_if<uses_allocator<container_type,
                            _Alloc>::value>::type* = 0);
                template <class _Alloc>
                    updatable_priority_queue(updatable_priority_queue&& __q, const _Alloc& __a,
                            typename enable_if<uses_allocator<container_type,
                            _Alloc>::value>::type* = 0);
#endif  // _LIBCPP_CXX03_LANG

    bool            empty() const {return c.empty();}
    size_type       size() const  {return c.size();}
    const_reference top() const   {return c.front();}

    void push(const value_type& __v);
#ifndef _LIBCPP_CXX03_LANG
    void push(value_type&& __v);
    //template <class... _Args>
    //void emplace(_Args&&... __args);
#endif  // _LIBCPP_CXX03_LANG
    void pop();
    void update_priority(const _Value&, const _Tp&);
    void update_priority(const value_type&);

    void swap(updatable_priority_queue& __q)
        _NOEXCEPT_(__is_nothrow_swappable<container_type>::value &&
                   __is_nothrow_swappable<map_type>::value      && 
                   __is_nothrow_swappable<value_compare>::value);


protected :
    void __sift_up(iter_type __first, iter_type __last, _Compare __comp, diff_type __len);
    void __push_heap(iter_type __first, iter_type __last, _Compare __comp);
    void __sift_down(iter_type __first, iter_type /*__last*/, _Compare __comp, diff_type __len, iter_type __start);
    void __pop_heap(iter_type __first, iter_type __last, _Compare __comp, diff_type __len);
};

#ifndef _LIBCPP_HAS_NO_DEDUCTION_GUIDES
/*template <class _Compare,
          class _Container,
          class = typename enable_if<!__is_allocator<_Compare>::value, nullptr_t>::type,
          class = typename enable_if<!__is_allocator<_Container>::value, nullptr_t>::type
>
priority_queue(_Compare, _Container)
    -> priority_queue<typename _Container::value_type, _Container, _Compare>;
  
template<class _InputIterator, 
         class _Compare   = less<typename iterator_traits<_InputIterator>::value_type>,
         class _Container = vector<typename iterator_traits<_InputIterator>::value_type>,
         class = typename enable_if< __is_input_iterator<_InputIterator>::value, nullptr_t>::type,
         class = typename enable_if<!__is_allocator<_Compare>::value, nullptr_t>::type,
         class = typename enable_if<!__is_allocator<_Container>::value, nullptr_t>::type
>
priority_queue(_InputIterator, _InputIterator, _Compare = _Compare(), _Container = _Container())
    -> priority_queue<typename iterator_traits<_InputIterator>::value_type, _Container, _Compare>;
  
template<class _Compare, 
         class _Container,
         class _Alloc,
         class = typename enable_if<!__is_allocator<_Compare>::value, nullptr_t>::type,
         class = typename enable_if<!__is_allocator<_Container>::value, nullptr_t>::type,
         class = typename enable_if< __is_allocator<_Alloc>::value, nullptr_t>::type
>
priority_queue(_Compare, _Container, _Alloc)
    -> priority_queue<typename _Container::value_type, _Container, _Compare>;
*/
#endif

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(const _Compare& __comp,
                                                          const container_type& __c)
    : c(__c),
      comp(__comp)
{
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(const value_compare& __comp,
                                                          container_type&& __c)
    : c(move(__c)),
      comp(__comp)
{
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

#endif  // _LIBCPP_CXX03_LANG


template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
template <class _InputIter>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(_InputIter __f, _InputIter __l,
                                                          const value_compare& __comp)
    : c(__f, __l),
      comp(__comp)
{
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
template <class _InputIter>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(_InputIter __f, _InputIter __l,
                                                          const value_compare& __comp,
                                                          const container_type& __c)
    : c(__c),
      comp(__comp)
{
    c.insert(c.end(), __f, __l);
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
template <class _InputIter>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(_InputIter __f, _InputIter __l,
                                                          const value_compare& __comp,
                                                          container_type&& __c)
    : c(move(__c)),
      comp(__comp)
{
    c.insert(c.end(), __f, __l);
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

#endif  // _LIBCPP_CXX03_LANG

/*
template <class _Value, class _Tp, class _Container,class _Compare,class _Map>
template <class _Alloc>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::priority_queue(const _Alloc& __a,
                       typename enable_if<uses_allocator<container_type,
                                                         _Alloc>::value>::type*)
    : c(__a)
{
}

template <class _Tp, class _Container, class _Compare>
template <class _Alloc>
inline
priority_queue<_Tp, _Container, _Compare>::priority_queue(const value_compare& __comp,
                                                          const _Alloc& __a,
                       typename enable_if<uses_allocator<container_type,
                                                         _Alloc>::value>::type*)
    : c(__a),
      comp(__comp)
{
}
*/
template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
template <class _Alloc>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(const value_compare& __comp,
                                                          const container_type& __c,
                                                          const _Alloc& __a,
                       typename enable_if<uses_allocator<container_type,
                                                         _Alloc>::value>::type*)
    : c(__c, __a),
      comp(__comp)
{
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
template <class _Alloc>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(const updatable_priority_queue& __q,
                                                          const _Alloc& __a,
                       typename enable_if<uses_allocator<container_type,
                                                         _Alloc>::value>::type*)
    : c(__q.c, __a),
      comp(__q.comp)
{
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
template <class _Alloc>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(const value_compare& __comp,
                                                          container_type&& __c,
                                                          const _Alloc& __a,
                       typename enable_if<uses_allocator<container_type,
                                                         _Alloc>::value>::type*)
    : c(move(__c), __a),
      comp(__comp)
{
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
template <class _Alloc>
inline
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::updatable_priority_queue(updatable_priority_queue&& __q,
                                                          const _Alloc& __a,
                       typename enable_if<uses_allocator<container_type,
                                                         _Alloc>::value>::type*)
    : c(move(__q.c), __a),
      comp(move(__q.comp))
{
    make_heap(c.begin(), c.end(), comp);
    for (iter_type it=c.begin(); it!=c.end(); it++){
        m.insert({it->first, it-c.begin()});
    }
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::push(const value_type& __v)
{
    c.push_back(__v);
    m.insert({__v.first,--c.end()-c.begin()});
    __push_heap(c.begin(), c.end(), comp);
}

#ifndef _LIBCPP_CXX03_LANG

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::push(value_type&& __v)
{
    c.push_back(move(__v));
    m.insert({move(__v.first),--c.end()-c.begin()});
    __push_heap(c.begin(), c.end(), comp);
}
/*
template <class _Tp, class _Container, class _Compare>
template <class... _Args>
inline
void
priority_queue<_Tp, _Container, _Compare>::emplace(_Args&&... __args)
{
    c.emplace_back(forward<_Args>(__args)...);
    push_heap(c.begin(), c.end(), comp);
}
*/
#endif  // _LIBCPP_CXX03_LANG

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
void
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::pop()
{
    __pop_heap(c.begin(), c.end(), comp, c.end()-c.begin());
    m.erase((--c.end())->first);
    c.pop_back();
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::swap(updatable_priority_queue& __q)
        _NOEXCEPT_(__is_nothrow_swappable<container_type>::value &&
                   __is_nothrow_swappable<map_type>::value &&
                   __is_nothrow_swappable<value_compare>::value)
{
    std::swap(c, __q.c);
    std::swap(m, __q.m);
    std::swap(comp, __q.comp);
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline 
typename enable_if<
    __is_swappable<_Container>::value
    && __is_swappable<_Map>::value
    && __is_swappable<_Compare>::value,
    void
>::type
swap(updatable_priority_queue<_Tp, _Container, _Compare>& __x,
     updatable_priority_queue<_Tp, _Container, _Compare>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

/*
template <class _Value, class _Tp, class _Container, class _Compare, class _Map, class _Alloc>
struct _LIBCPP_TEMPLATE_VIS std::uses_allocator<updatable_priority_queue<_Tp, _Container, _Compare>, _Alloc>
    : public uses_allocator<_Container, _Alloc>
{
};
*/

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void 
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::update_priority(const _Value& __v, const _Tp& __new){
    iter_type __item = c.begin()+m[__v];
    _Tp __old = __item->second;
    __item->second = __new;
    if (comp(__old,__new)){
        __item++;
        __sift_up(c.begin(),__item,comp,__item-c.begin());
    }else{
        __sift_down(c.begin(),c.end(),comp,c.end()-c.begin(), __item);
    } 
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void 
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::update_priority(const value_type& vt){
    update_priority(vt.first, vt.second);
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void 
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::__pop_heap(iter_type __first, iter_type __last, _Compare __comp, diff_type __len)
{
    if (__len > 1)
    {
        std::swap(*__first, *--__last);
        __sift_down(__first, __last, __comp, __len-1, __first);
    }
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void 
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::__sift_up(iter_type __first, iter_type __last, _Compare __comp, diff_type __len)
{
    if (__len > 1)
    {
        __len = (__len - 2) / 2;
        iter_type __ptr = __first + __len;
        if (__comp(__ptr->second, (--__last)->second))
        {
            value_type __t(move(*__last));
            do
            {
                *__last = move(*__ptr);
                m[__last->first] = __last - c.begin();
                __last = __ptr;
                if (__len == 0)
                    break;
                __len = (__len - 1) / 2;
                __ptr = __first + __len;
            } while (__comp(__ptr->second, __t.second));
            *__last = move(__t);
            m[__last->first] = __last - c.begin();
        }
    }
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
inline
void 
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::__push_heap(iter_type __first, iter_type __last, _Compare __comp)
{
#ifdef _LIBCPP_DEBUG
    typedef typename add_lvalue_reference<__debug_less<_Compare> >::type _Comp_ref;
    __debug_less<_Compare> __c(__comp);
    __sift_up(__first, __last, __c, __last - __first);
#else  // _LIBCPP_DEBUG
    typedef typename add_lvalue_reference<_Compare>::type _Comp_ref;
    __sift_up(__first, __last, __comp, __last - __first);
#endif  // _LIBCPP_DEBUG
}

template <class _Value, class _Tp, class _Container, class _Compare, class _Map>
    inline
void 
updatable_priority_queue<_Value, _Tp, _Container, _Compare, _Map>::__sift_down(iter_type __first, iter_type /*__last*/,
        _Compare __comp,
        diff_type __len,
        iter_type __start)
{
    // left-child of __start is at 2 * __start + 1
    // right-child of __start is at 2 * __start + 2
    diff_type __child = __start - __first;

    if (__len < 2 || (__len - 2) / 2 < __child)
        return;
    __child = 2 * __child + 1;
    iter_type __child_i = __first + __child;
    if ((__child + 1) < __len && __comp(__child_i->second, (__child_i + 1)->second)) {
        // right-child exists and is greater than left-child
        ++__child_i;
        ++__child;
    }

    // check if we are in heap-order
    if (__comp(__child_i->second, __start->second))
        // we are, __start is larger than it's largest child
        return;

    value_type __top(move(*__start));
    do
    {
        // we are not in heap-order, swap the parent with it's largest child
        *__start = move(*__child_i);
        m[__start->first] = __start-c.begin();
        __start = __child_i;

        if ((__len - 2) / 2 < __child)
            break;

        // recompute the child based off of the updated parent
        __child = 2 * __child + 1;
        __child_i = __first + __child;

        if ((__child + 1) < __len && __comp(__child_i->second, (__child_i + 1)->second)) {
            // right-child exists and is greater than left-child
            ++__child_i;
            ++__child;
        }

        // check if we are in heap-order
    } while (!__comp(__child_i->second, __top.second));
    m[__start->first] = __start-c.begin();
    *__start = move(__top);
}

}; //namespace pewulfman


#endif  // _PEW_UPQ

