#pragma once
class MapGenWindow
{
public:
  bool show;
  MapGenWindow() {} 
  ~MapGenWindow() {}
  const char* Title()
  {
    return title;
  }
  const char* MenuTitle()
  {
    return menutitle;
  }

protected:
  const char* title;
  const char* menutitle;
};

