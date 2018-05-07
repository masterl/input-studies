# Input studies

Reading directly from `cin` might put this global in an error state, so reading the line and parsing later might be better on this regard.
Of course there are many ways of achieving this, this repository aim is to try different options.

## Base strategy used
1. Read full line into a `string`
2. create an `istringstream` from this `string`
3. read from this new stream

### Dependencies
- C++14 compatible compiler
- [entr](entrproject.org) (If you plan on using supplied auto-compiling script)
    - Note: Script was built for g++, you might need to change it for another compiler!

#### Folder names
- `no-ec` suffix means "no error check"

---
## Methods discussion

### In-place

The first option was to do it in-place, as can be seen on [the source](in-place-no-ec/main.cpp).<br>
Of course there are many ways of doing this, for example:
- Create a new string and stream everytime we need input
- Create a string and stream and carry them from start to bottom

Either way, the impacts are mostly bad.

#### PROs:
- **not put global std::cin on a bad state**<br>
  Imagine we tried `cin >> number;`, but the user provided a letter, cin would now be on a bad state.<br>
  If we extract the line as a string, we avoid this situation.

#### CONs:

- **Code duplication**<br>
  Every input will need this boilerplate-ish code. So you'd need to fill your code with a lot of variables or carry this string and istringstream everywhere and remember to clear the buffer and error state before reusing it along the program.
- **No error checking**<br>
  Since we don't check for errors, this is obviously a concern.
- **Scope pollution**<br>
  By doing it in-place we need to expend two variable names, one for the input and one for the stream.

##### Note:

Another way is creating a string and carrying it from start to bottom, but create the stream and use it right away, for example:

```cpp
std::string input;
int number;
// (...)
std::getline(std::cin, input);

std::istringstream(input) >> number;
```

This will not only have all the previously mentioned CONs, but now we also will not be able to determine if the input was successful or not, since we have no way of calling `.fail()` or any other state checking method on that stream.

---
