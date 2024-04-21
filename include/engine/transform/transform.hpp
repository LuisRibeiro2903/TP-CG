// abstract class that defines a transformation
#ifndef TRANSFORM
#define TRANSFORM

using namespace std;

class Transform {
public:
  virtual void applyTransform() const = 0;
};

#endif
