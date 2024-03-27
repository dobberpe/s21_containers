#ifndef _S21_STACK_H_
#define _S21_STACK_H_

class stack {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  int begin();
  int end();
  int operator*(const stack &A);
  int operator++();
  int operator--();
  bool operator==(const stack &iter2);
  bool operator!=(const stack &iter2);

  bool push_back();
  bool pop_back();
  bool stack_clean();

  int stack_count();
  bool stack_empty();

  double &operator()(const int i);

  stack();
  stack(const stack &other);
  stack(stack &&other);
  //   stack(stack &stack);
  ~stack();
};

#endif  //_S21_STACK_H_
