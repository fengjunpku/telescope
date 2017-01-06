#include "JunErrors.hh"

void MiaoError(string errorStr)
{
  cout<<YELLOW<<BOLD<<"# Miao! "<<COLOR_END;
  cout<<RED<<BOLD<<"Error: "<<COLOR_END;
  cout<<errorStr<<endl;
  exit(0);
}