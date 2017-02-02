#pragma once
#include <map>

using namespace std;

template <typename A, typename B>
class BidirectionalMap
{
public:
    void set(A a, B b) {
        mapBtoA_[get(a)] = nullptr;
        mapAtoB_[get(b)] = nullptr;
        mapAtoB_[a] = b;
        mapBtoA_[b] = a;
    }

    B get(A a) {
        return mapAtoB_[a];
    }

    A get(B b) {
        return mapBtoA_[b];
    }

private:
    map<A,B> mapAtoB_;
    map<B,A> mapBtoA_;
};

