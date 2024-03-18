#include "Rational.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>

Rational::Rational() : numerator_(0), denominator_(1) {}
Rational::Rational(int numerator, int denominator) {
  if (denominator == 0) {
    throw std::invalid_argument("Nazivnik ne moze biti 0!");
  } else {
    numerator_ = numerator;
    denominator_ = denominator;
    int temp = gcd(numerator_, denominator_);
    numerator_ /= temp;
    denominator_ /= temp;
  }
}

Rational::Rational(const char *rational) {
  std::istringstream input(rational);
  int num, denom;
  char delim = '\0';

  if (!(input >> num))
    throw std::invalid_argument("Nevalidan unos");
  input >> delim;
  if (delim != '/')
    throw std::invalid_argument("Nevalidan format");
  if (delim == '\0')
    denom = 1;
  if (!(input >> denom))
    throw std::invalid_argument("Nevalidan unos");
  if (denom == 0)
    throw std::invalid_argument("Nazivnik ne moze biti 0");

  int temp = gcd(num, denom);
  numerator_ = num / temp;
  denominator_ = denom / temp;
}
Rational::Rational(const std::string &razlomak) {
  std::istringstream input(razlomak);
  int num, denom;
  char delim = '\0';

  if (!(input >> num))
    throw std::invalid_argument("Nevalidan unos");
  input >> delim;
  if (delim != '/')
    throw std::invalid_argument("Nevalidan format");
  if (delim == '\0')
    denom = 1;
  if (!(input >> denom))
    throw std::invalid_argument("Nevalidan unos");
  if (denom == 0)
    throw std::invalid_argument("Nazivnik ne moze biti 0");

  int temp = gcd(num, denom);
  numerator_ = num / temp;
  denominator_ = denom / temp;
}

Rational::Rational(const Rational &rational) {
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;
}

Rational::Rational(Rational &&rational) {
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;
  rational.numerator_ = 0;
  rational.denominator_ = 1;
}

Rational &Rational::operator=(const Rational &rational) {
  if (this != &rational) {
    numerator_ = rational.numerator_;
    denominator_ = rational.denominator_;
  }
  return *this;
}

Rational &Rational::operator=(Rational &&rational) {
  if (this != &rational) {
    numerator_ = rational.numerator_;
    denominator_ = rational.denominator_;
    rational.numerator_ = 0;
    rational.denominator_ = 1;
  }
  return *this;
}

Rational Rational::operator+(const Rational &rational) const {
  Rational rezultat;
  rezultat.numerator_ =
      (numerator_ * rational.denominator_ + denominator_ * rational.numerator_);
  rezultat.denominator_ = denominator_ * rational.denominator_;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator+(int numerator) const {
  Rational rezultat;
  rezultat.numerator_ = (numerator_ + denominator_ * numerator);
  rezultat.denominator_ = denominator_;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator-(const Rational &rational) const {
  Rational rezultat;
  rezultat.numerator_ =
      (numerator_ * rational.denominator_ - denominator_ * rational.numerator_);
  rezultat.denominator_ = denominator_ * rational.denominator_;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator-(int numerator) const {
  Rational rezultat;
  rezultat.numerator_ = (numerator_ - denominator_ * numerator);
  rezultat.denominator_ = denominator_;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator*(const Rational &rational) const {
  Rational rezultat;
  rezultat.numerator_ = numerator_ * rational.numerator_;
  rezultat.denominator_ = denominator_ * rational.denominator_;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator*(int numerator) const {
  Rational rezultat;
  rezultat.numerator_ = numerator_ * numerator;
  rezultat.denominator_ = denominator_;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator/(const Rational &rational) const {
  Rational rezultat;
  rezultat.numerator_ = numerator_ * rational.denominator_;
  rezultat.denominator_ = denominator_ * rational.numerator_;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator/(int numerator) const {
  Rational rezultat;
  rezultat.numerator_ = numerator_;
  rezultat.denominator_ = denominator_ * numerator;
  int temp = gcd(rezultat.numerator_, rezultat.denominator_);
  rezultat.numerator_ /= temp;
  rezultat.denominator_ /= temp;

  return rezultat;
}

Rational Rational::operator^(int num) const {
  Rational rezultat;
  rezultat.numerator_ = pow(numerator_, num);
  rezultat.denominator_ = pow(denominator_, num);

  return rezultat;
}

Rational &Rational::operator++() {
  numerator_ = numerator_ + denominator_;
  return *this;
}

Rational Rational::operator++(int) {
  Rational rezultat(numerator_, denominator_);
  ++(*this);
  return rezultat;
}

Rational &Rational::operator--() {
  numerator_ = numerator_ - denominator_;
  return *this;
}

Rational Rational::operator--(int) {
  Rational rezultat(numerator_, denominator_);
  --(*this);
  return rezultat;
}

bool Rational::operator==(const Rational &rational) const {
  if (numerator_ == rational.numerator_ &&
      denominator_ == rational.denominator_)
    return true;
  else
    return false;
}

bool Rational::operator==(const char *rational) const {
  std::istringstream input(rational);
  int num, denom;
  char delim;

  input >> num >> delim >> denom;

  if (delim != '/' || denom == 0) {
    throw std::invalid_argument(
        "Nevalidan format ili je nazivnik jednak nuli!");
  }
  Rational temp(num, delim);
  if (numerator_ == temp.numerator_ && denominator_ == temp.denominator_)
    return true;
  return false;
}

bool Rational::operator!=(const Rational &rational) const {
  if (numerator_ == rational.numerator_ &&
      denominator_ == rational.denominator_)
    return false;
  else
    return true;
}

bool Rational::operator!=(const char *rational) const {
  std::istringstream input(rational);
  int num, denom;
  char delim;

  input >> num >> delim >> denom;

  if (delim != '/' || denom == 0) {
    throw std::invalid_argument(
        "Nevalidan format ili je nazivnik jednak nuli!");
  }
  Rational temp(num, delim);
  if (numerator_ == temp.numerator_ && denominator_ == temp.denominator_)
    return false;
  return true;
}

const int Rational::numerator() const { return numerator_; }

const int Rational::denominator() const { return denominator_; }

std::ostream &operator<<(std::ostream &os, const Rational &rational) {
  if (rational.denominator() == 0)
    throw std::invalid_argument("Nazivnik ne smije biti 0");
  if (rational.denominator() == 1)
    os << rational.numerator();
  else
    os << rational.numerator() << "/" << rational.denominator();

  return os;
}
Rational::~Rational()=default;
int gcd(const int numerator, const int denominator) {
  int temp = std::min(numerator, denominator);
  while (temp > 0) {
    if (numerator % temp == 0 && denominator % temp == 0) {
      break;
    }
    temp--;
  }
  return temp;
}
