#pragma once
#include <codecvt>
/*
This struct represents a C# string. Credits to caoyin.

It is pretty straight forward. If you have this in a dump,

public class Player {
    public string username; // 0xC8
}

getting that string would look like this: monoString *username = *(monoString **)((uint64_t)player + 0xc8);

C# strings are UTF-16. This means each character is two bytes instead of one.

To get the length of a monoString, call getLength.
To get a NSString from a monoString, call toNSString.
To get a std::string from a monoString, call toCPPString.
To get a C string from a monoString, call toCString.
*/


template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    void* vector[1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};

template <typename T>
struct monoList {
    void* unk0;
    void* unk1;
    monoArray<T>* items;
    int size;
    int version;

    T getItems() {
        return items->getPointer();
    }

    int getSize() {
        return size;
    }

    int getVersion() {
        return version;
    }
};

template <typename K, typename V>
struct monoDictionary {
    void* unk0;
    void* unk1;
    monoArray<int**>* table;
    monoArray<void**>* linkSlots;
    monoArray<K>* keys;
    monoArray<V>* values;
    int touchedSlots;
    int emptySlot;
    int size;

    K getKeys() {
        return keys->getPointer();
    }

    V getValues() {
        return values->getPointer();
    }

    int getNumKeys() {
        return keys->getLength();
    }

    int getNumValues() {
        return values->getLength();
    }

    int getSize() {
        return size;
    }
};

struct Vector4
{
    union
    {
        struct
        {
            float X;
            float Y;
            float Z;
            float W;
        };
    };

    inline Vector4(float x, float y, float z, float w);
};

Vector4::Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

inline bool operator==(const Vector4 lhs, const Vector4 rhs);
bool operator==(const Vector4 lhs, const Vector4 rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z && lhs.W == rhs.W;
}