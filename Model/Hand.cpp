#include "Hand.hpp"

#include <algorithm>

Hand::Hand() : type(0)
{}

void Hand::set(const std::vector<unsigned> c)
{
  cards.clear();
  for(std::vector<unsigned>::const_iterator it = c.begin(); it != c.end(); ++it) {
    cards.push_back(*it);
  }
  checkHand();
}
std::vector<unsigned> Hand::getCards() const
{
  std::vector<unsigned> v;
  for(int i=0; i<5; ++i)
  {
    v.push_back(cards[i].getCard());
  }
  return v;
}
bool Hand::operator < (const Hand& h) const
{
  // jesli brak znaczacych ukladow, porownaj najwyzsze karty rak
  if(type==WYSOKA_KARTA && h.type==WYSOKA_KARTA)
    return (getMaxCard() < h.getMaxCard());
  return type < h.type;
}

bool Hand::operator == (const Hand& h) const
{
  if(type==WYSOKA_KARTA && h.type==WYSOKA_KARTA)
    return (getMaxCard() == h.getMaxCard());
  return type != h.type;
}

Card Hand::getMaxCard() const
{
  Card max = cards[0];
  for(unsigned i=1; i<HAND_SIZE; ++i)
  {
    if(cards[i] < max)
      max = cards[i];
  }
  return max;
}

bool Hand::isMonoColor()
{
  unsigned color = cards[0].getC();
  for(unsigned i =1; i<HAND_SIZE; ++i)
  {
    if(color != cards[i].getC())
      return false;
  }
  return true;
}

bool Hand::isAsc()
{
  unsigned val = cards[0].getV();
  for(unsigned i =1; i<HAND_SIZE; ++i)
  {
    if(val-i != cards[i].getV())
      return false;
  }
  return true;
}

unsigned Hand::getType() const
{
	return type;
}

void Hand::checkHand()
{
   //sortuje malej�co
   sort(cards.begin(),cards.end());
   
   //zlicz wystapienia poszczegolnych figur i zapisz w wektorze v, indeks odpowiada figurze
   std::vector<int> v(13, 0);
   for(unsigned i=0; i<HAND_SIZE; ++i)
   {
     unsigned val = cards[i].getV();
     v[val] += 1;
   }
     
   type = WYSOKA_KARTA; 
   checkPair(v);
   checkTwoPair(v);
   checkThree(v);
   checkStraight();
   checkFlush();
   checkFull(v);
   checkFour(v);
   checkStraightFlush();
   checkRoyalFlush();
}

void Hand::checkRoyalFlush()
{
  if(!isMonoColor())
    return;
  if(cards[0].getV()==CARD_A && 
     cards[1].getV()==CARD_K &&
     cards[2].getV()==CARD_Q &&
     cards[3].getV()==CARD_J &&
     cards[4].getV()==CARD_10)
      type = ROYAL_POKER;
}

void Hand::checkStraightFlush()
{
  if(isMonoColor() && isAsc())
    type = POKER;
}

void Hand::checkFour(std::vector<int>& v)
{
    for(unsigned i=0; i<v.size(); ++i)
    {
      if(v[i] == 4)
      {
	 type = KARETA;
	 return;
      }
    }
}

void Hand::checkFull(std::vector<int>& v)
{
    bool pair = false;
    bool three = false;
    for(unsigned i=0; i<v.size(); ++i)
    {
      if(v[i] == 3)
	three = true;
      if(v[i] == 2)
	pair = true;
    }
    if(pair && three)
      type = FULL;
}

void Hand::checkFlush()
{
  if(isMonoColor())
    type = KOLOR;
}

void Hand::checkStraight()
{
  if(isAsc())
    type = STRIT;
}

void Hand::checkThree(std::vector<int>& v)
{
    for(unsigned i=0; i<v.size(); ++i)
    {
      if(v[i] == 3)
      {
	type = TROJKA;
	return;
      }
    }
}

void Hand::checkTwoPair(std::vector<int>& v)
{
    int pair = 0;
    for(unsigned i=0; i<v.size(); ++i)
    {
      if(v[i] == 2)
	++pair;
    }
    if(pair >= 2)
      type = DWIE_PARY;
}

void Hand::checkPair(std::vector<int>& v)
{
    for(unsigned i=0; i<v.size(); ++i)
    {
      if(v[i] == 2)
      {
	type = PARA;
	return;
      }
    }
}







































