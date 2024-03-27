#ifndef _S21_MULTISET_H_
#define _S21_MULTISET_H_

class multiset {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  int begin();
  int end();
  int operator*(const multiset &A);
  int operator++();
  int operator--();
  bool operator==(const multiset &iter2);
  bool operator!=(const multiset &iter2);

  bool push_back();
  bool pop_back();
  bool multiset_clean();

  int multiset_count();
  bool multiset_empty();

  double &operator()(const int i);

  multiset();
  multiset(const multiset &other);
  multiset(multiset &&other);
  //   multiset(multiset &multiset);
  ~multiset();
};

#endif  //_S21_MULTISET_H_
