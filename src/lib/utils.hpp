namespace utils {
  /**
   * Splits a string into an array.
   * TAKEN from: https://favtutor.com/blogs/split-string-cpp
   */
  std::vector<std::string> splitString(std::string str, char separator) {
    std::vector<std::string> strings;
    int startIndex = 0, endIndex = 0;
    for (int i = 0; i <= str.size(); i++) {
      // If we reached the end of the word or the end of the input.
      if (str[i] == separator || i == str.size()) {
        endIndex = i;
        std::string temp;
        temp.append(str, startIndex, endIndex - startIndex);
        strings.push_back(temp);
        startIndex = endIndex + 1;
      }
    }
    return strings;
  }

  /**
   * Trims a string from the start.
   * TAKEN from: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
   */
  inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
              return !std::isspace(ch);
            }));
  }

  /**
   * Trims a string from the end.
   * TAKEN from: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
   */
  inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                        [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }

  /**
   * Trims a string.
   * TAKEN from: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
   */
  inline void trim(std::string& s) {
    rtrim(s);
    ltrim(s);
  }

  /**
   * Transforms an entire string to uppercase.
   * TAKEN from: https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
   */
  std::string toupper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
  }
}
