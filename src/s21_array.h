#ifndef _S21_ARRAY_H_
#define _S21_ARRAY_H_

class array {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  int begin();
  int end();
  int operator*(const array &A);
  int operator++();
  int operator--();
  bool operator==(const array &iter2);
  bool operator!=(const array &iter2);

  bool push_back();
  bool pop_back();
  bool array_clean();

  int array_count();
  bool array_empty();

  double &operator()(const int i);

  array();
  array(const array &other);
  array(array &&other);
  //   array(array &array);
  ~array();
};

#endif  //_S21_ARRAY_H_
