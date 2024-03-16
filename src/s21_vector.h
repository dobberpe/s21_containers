#ifndef _S21_VECTOR_H_
#define _S21_VECTOR_H_

class vector {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  int begin();
  int end();
  int operator*(const vector &A);
  int operator++();
  int operator--();
  bool operator==(const vector &iter2);
  bool operator!=(const vector &iter2);

  bool push_back();
  bool pop_back();
  bool vector_clean();

  int vector_count();
  bool vector_empty();

  double &operator()(const int i);

  vector();
  vector(const vector &other);
  vector(vector &&other);
  //   vector(vector &vector);
  ~vector();
};

#endif  //_S21_VECTOR_H_
