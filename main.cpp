/*
 Project 9: Part 1/1
 Chapter 5 Part 7 Task

 Create a branch named Part1

Purpose:  This project will teach you about variadic templates and recursive templates, one of the last areas needing discussion while learning C++

0) Do your best to avoid looking at previous student submissions for this project.
    This project does not have a lot of code.  
    There are only 1 or 2 ways to solve it.  everyone always arrives at the same solution.
    If you look at the previous student submissions, you will be denying yourself the opportunity to figure this project out for yourself.
    If you get stuck, I would prefer if you message me for help instead of looking at the previous student submissions.
 
1) read Instructions.cpp

Make the following program work, which makes use of Variadic templates and Recursion
 */

#include <iostream>
#include <string>
#include <typeinfo>
#include <utility>

struct Point
{
    Point(float _x, float _y) : x(_x), y(_y) { }
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    std::string toString() const
    {
        std::string str;
        str +="Point { x: ";
        str += std::to_string(x);
        str += ", y: ";
        str += std::to_string(y);
        str += " }";
        return str;
    }
private:
    float x{0}, y{0};
};



template<typename Type>
struct Wrapper
{
    Wrapper(Type&& t) : val(std::move(t)) 
    { 
        std::cout << "Wrapper(" << typeid(val).name() << ")" << std::endl; 
    }

    void print()
    {
        std::cout << "Wrapper::print(" << val << ")\n";
    }
private:
    Type val;
};

// Challenge 1: specialized print() member function 
template<>
void Wrapper<Point>::print()
{
    std::cout << "Wrapper::print(" << val.toString() << ")\n";
}


// 4) single-parameter version of template
// template<typename T>
// void variadicHelper(T&& first)
// {
//     Wrapper<T>( std::forward<T>(first) ).print();
// }

void variadicHelper();

// 3) recursive variadic template (Challenge 2: alternate recursive solution #1)
template<typename T, typename ... Args>
void variadicHelper(T&& first, Args&& ... everythingElse)
{
    Wrapper<T>( std::forward<T>(first) ).print();

    variadicHelper( std::forward<Args>(everythingElse) ... ); // recursive call
}

void variadicHelper()
{
}

// Challenge 2: alternate recursive solution #2
// template<typename T, typename ... Args>
// void variadicHelper(T&& first, Args&& ... everythingElse)
// {
//     Wrapper<T>( std::forward<T>(first) ).print();

//     if constexpr (!sizeof ... (Args) )
//     {
//     }
//     else
//     {
//         variadicHelper( std::forward<Args>(everythingElse) ... ); // recursive call
//     }
// }



/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

int main()
{
    variadicHelper( 3, std::string("burgers"), 2.5, Point{3.f, 0.14f} );
}


