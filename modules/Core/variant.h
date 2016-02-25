#ifndef VARIANT_H
#define VARIANT_H

class Variant {
public:
    template< class T >
    Variant(T&& value) :
    {}

    template< class T >
    Variant& operator=(T&& value) {

    }

};

#endif // VARIANT_H
