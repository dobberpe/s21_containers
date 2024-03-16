#ifndef _S21_MAP_H_
#define _S21_MAP_H_

class map {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  int begin();
  int end();
  int operator*(const map &A);
  int operator++();
  int operator--();
  bool operator==(const map &iter2);
  bool operator!=(const map &iter2);

  bool push_back();
  bool pop_back();
  bool map_clean();

  int map_count();
  bool map_empty();

  double &operator()(const int i);

  map();
  map(const map &other);
  map(map &&other);
  //   map(map &map);
  ~map();
};

#endif  //_S21_MAP_H_
