#ifndef _S21_SET_H_
#define _S21_SET_H_

class set {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  int begin();
  int end();
  int operator*(const set &A);
  int operator++();
  int operator--();
  bool operator==(const set &iter2);
  bool operator!=(const set &iter2);

  bool push_back();
  bool pop_back();
  bool set_clean();

  int set_count();
  bool set_empty();

  double &operator()(const int i);

  set();
  set(const set &other);
  set(set &&other);
  //   set(set &set);
  ~set();
};

#endif  //_S21_SET_H_
