// Programmer: Illya Starikov
// Section: 3E
// File: main.cpp
// Description: To use constructors and define friend/operator overloading functions.

/*
 Name: Rectangle()
 Description: Default constructor, assigns 1 to length and width.
 Pre-Condition: None.
 Post-Condition: Constructs the default Rectangle.
 */

/*
 Name: Rectangle(const int rect_length, const int rect_height);
 Description: To take a length and a height and assign that when constructing the rectangle.
 Pre-Condition: valid length and height, recommended to have both > 0.
 Post-Condition: Rectangle is constructed with a height and a length.
 */

/*
 Name:   Rectangle(const Rectangle & source);
 Description: to construct the rectangle as a copy from a different rectangle
 Pre-Condition: A rectangle must be passed.
 Post-Condition: A copy of a rectangle is copied.
 */

/*
 Name:  void operator !();
 Description: Deduct two from the calling object's height and width.
 Pre-Condition: None.
 Post-Condition: Two is deducted from the calling object's height and width.
 */

/*
 Name:  Rectangle operator *= (const Rectangle & rec);
 Description: To return a rectangle that is multiplied by a different rectangle.
 Pre-Condition: Something must be on the right hand side.. or it won't even compile.
 Post-Condition: A rectangle is returned in the place of the calling object.
 */

/*
 Name:  friend Rectangle operator + (const Rectangle &rec1 , const Rectangle &rec2);
 Description: adds to rectangles.
 Pre-Condition: two valid rectangles must be passed.
 Post-Condition: Two rectangles are added.
 */

/*
 Name: friend ostream & operator << (ostream & stream, const Rectangle & rec);
 Description: the intended use is to output the rectangle in nice, readable way. This doesn't have to be
 the only use case, however.
 Pre-Condition: Something must be on the right hand side of the extraction operator.
 Post-Condition: To output the rectangle in a nice, friendly way to the user is the indented use.
 */

#include <iostream>
#include <fstream>

using namespace std;

class Rectangle
{
// Price said it's okay to have indentation in this way.
public:
  Rectangle();
  Rectangle(const int rect_length, const int rect_height);
  Rectangle(const int rect_height);
  Rectangle(const Rectangle & source);

  void operator !();
  Rectangle operator *= (const Rectangle & rec);

  friend Rectangle operator + (const Rectangle &rec1 , const Rectangle &rec2);
  friend ostream & operator << (ostream & stream, const Rectangle & rec);

private:
  int length;
  int width;
};

int main()
{
  Rectangle A(3, 2);
  Rectangle B(9,5);
  Rectangle C;
  Rectangle D(5);
  Rectangle E(D);
  cout <<"A: " << A;
  cout <<"B: " << B;
  cout <<"C: " << C;
  cout <<"D: " << D;
  cout <<"E: " << E;
  C = A + B;
  cout <<"C = A + B ==> C: " << C;
  C *= A;
  cout <<"C *= A  ==> C: " << C;
  !C;
  cout <<"!C    ==> C: " << C;

  return 0;
}

Rectangle::Rectangle()
{
  length = 1;
  width = 1;
}

Rectangle::Rectangle(const int rect_length, const int rect_height)
{
  if (rect_height <= 0 || rect_length <= 0)
  {
    cerr << "ERROR. Exiting Now.";
    return;
  }
  else
  {
    length = rect_length;
    width = rect_height;
  }
}

Rectangle::Rectangle(const int rect_height)
{
  if (rect_height <= 0)
  {
    cerr << "ERROR. Exiting Now.";
    return;
  }
  else
  {
    length = (2 * rect_height);
    width = rect_height;
  }

}
Rectangle::Rectangle(const Rectangle & source)
{
  length = source.length;
  width = source.width;
}

void Rectangle::operator !()
{
  length -= 2;
  width  -= 2;

  if (length <= 0)
  {
    length = 1;
  }
  if (width <= 0)
  {
    width = 1;
  }

}

Rectangle Rectangle::operator *= (const Rectangle & rec)
{
  length *=  rec.length;
  width *= rec.width;
  return *this;
}

Rectangle operator + (const Rectangle &rec1 , const Rectangle &rec2)
{
  Rectangle returnRectangle;

  returnRectangle.length = rec1.length + rec2.length;
  returnRectangle.width = rec1.width + rec2.width;

  return returnRectangle;
}

ostream & operator << (ostream & stream, const Rectangle & rec)
{
  // Sorry it's the wrong format, didn't look at the sample output
  // Until the end :(
  stream << endl << "Length: " << rec.length << endl << "Width: " << rec.width << endl;

  return stream;
}
