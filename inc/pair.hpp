namespace ft
{
template<
    class T1,
    class T2
> struct pair
{
    typedef T1  first_type;
    typedef T2  second_type;

private:
    first_type  first_;
    second_type second_;
public:
    pair();
    pair( const T1& x, const T2& y ) : first_(x), second_(y) {}; //make pair?

    template< class U1, class U2 >
    pair( const pair<U1, U2>& p );
    pair( const pair& p ) = default; //??
    ~pair();

};
} // namespace ft
