#ifndef CONTENT_H
#define CONTENT_H

#include <string>

class Content
{
   public:
      Content(const std::string& desc = "an empty room", char abbr = '.');
      virtual ~Content();
      std::string getDescription() const { return description; }
      char getAbbr() const { return abbr; }
      bool operator==(char ch) const { return abbr == ch; }
      bool operator!=(char ch) const { return abbr != ch; }

   protected:
      std::string description;
      char abbr;
   private:

};

#endif // CONTENT_H
