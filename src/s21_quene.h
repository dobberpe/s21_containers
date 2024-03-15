#ifndef _S21_QUENE_H_
#define _S21_QUENE_H_

class quene {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  int begin();
  int end();
  int operator*(const quene &A);
  int operator++();
  int operator--();
  bool operator==(const quene &iter2);
  bool operator!=(const quene &iter2);

  bool add_elem();
  bool remove_elem();
  bool quene_clean();

  int quene_count();
  bool quene_empty();

  double &operator()(const int i);

  quene();
  quene(const quene &other);
  quene(quene &&other);
  //   quene(quene &quene);
  ~quene();
};

#endif  //_S21_QUENE_H_
