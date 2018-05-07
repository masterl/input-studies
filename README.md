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

#### Folder naming
- `no-ec` suffix means "no error check"
- `with-ec` suffix means "with error check"

---

## Methods discussion

---

### In-place (no error check)

The first option was to do it in-place:

```cpp
int number;
std::string user_input;

std::cout << "Input a number: ";

std::getline( std::cin, user_input );

std::istringstream input_stream( user_input );

input_stream >> number;

std::cout << "\nYou typed [" << number << "]" << std::endl;
```

See the [full source here](in-place-no-ec/main.cpp).

Of course there are many ways of doing this, for example:
- Create a new string and stream everytime we need input
- Create a string and stream and carry them from start to bottom

Either way, the impacts are mostly bad.

#### PROs:

- **not put global std::cin on a bad state**<br>
  Imagine we tried `cin >> number;`, but the user provided a letter, cin would now be on a bad state.<br>
  By extracting the line as a string, we avoid this situation.

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

This will not only have all the previously mentioned CONs, but now even if we decide to check for errors we wouldn't be able to, since we have no way of calling `.fail()` or any other state checking method on that stream.

---

### In-place (with error checking)

Now we'll do it in-place again, but now checking for error:

```cpp
std::cout << "Input a number: ";

std::getline( std::cin, user_input );

std::istringstream input_stream( user_input );

input_stream >> number;

if( input_stream.fail() )
{
    std::cerr << "\nOops, [" << user_input << "] is not a number!" << std::endl;

    return -1;
}

std::cout << "\nYou typed [" << number << "]" << std::endl;
```

See the [full source here](in-place-with-ec/main.cpp).

The code provided is just an example of one of the possible approaches inside `main`, namely *"exiting upon error"*.<br>
We could also have a loop to keep asking for input on error, for example.

#### PROs:

- **not put global std::cin on a bad state**<br>
  Imagine we tried `cin >> number;`, but the user provided a letter, cin would now be on a bad state.<br>
  By extracting the line as a string, we avoid this situation.

- **error checking**<br>
  Now our program won't proceed after an error.

#### CONs:

- **Code duplication**<br>
  Every input will need this boilerplate-ish code. So you'd need to fill your code with a lot of variables or carry this string and istringstream everywhere and remember to clear the buffer and error state before reusing it along the program.
- **Scope pollution**<br>
  By doing it in-place we still need to expend two variable names, one for the input and one for the stream.
- **Code clutter**<br>
  Adding error checking makes the input receive part even bigger now, clouding the program logic.

---

### Simple functions (no error check)

We've seen that doing it in-place has more CONs overall, so now let's try isolating this code on functions:

```cpp
std::string read_line();
int read_integer();

int main()
{
    int number;
    std::string user_input;

    std::cout << "Input a number: ";

    number = read_integer();

    std::cout << "\nYou typed [" << number << "]" << std::endl;

    return 0;
}

// read_line and read_integer defined here
```

See the [full source here](simple-functions-no-ec/main.cpp).

#### PROs:

- **not put global std::cin on a bad state**<br>
  Imagine we tried `cin >> number;`, but the user provided a letter, cin would now be on a bad state.<br>
  By extracting the line as a string, we avoid this situation.

- **Less code duplication** (more on this on the CONs)<br>
  If there is something wrong on the input handling, we don't need to scan all our code to fix it, there's a few places that we need to check.

- **No scope pollution**<br>
  At least regarding variables, we are not polluting the scope anymore.<br>
  All variables are scoped to their respective functions.

- **Less clutter**<br>
  Now the input read part is just a function call which doesn't obfuscate the program logic.

#### CONs:

- **No error checking**<br>
  Since we don't check for errors, this is obviously a concern.

- **Some code duplication**<br>
  By using simple functions without the help of templates or anything, we need to declare one function for each type we need.<br>
  On the example, `read_integer` reads an `int`, but what if we need `short`? Or `double`? `long`? `unsigned`? `char`? And so on...

  ---

  ### Simple functions (with error checking)

  Now we are able to determine if an input was successful or not without cluttering up too much our code:

  ```cpp
  bool read_line( std::string &line );
  bool read_integer( int &value );

  int main()
  {
      int number;
      std::string user_input;

      std::cout << "Input a number: ";

      if( !read_integer( number ) )
      {
          std::cerr << "Oops, looks like you didn't type a number" << std::endl;

          return -1;
      }

      std::cout << "\nYou typed [" << number << "]" << std::endl;

      return 0;
  }

  // read_line and read_integer defined here
  ```

  See the [full source here](simple-functions-with-ec/main.cpp).

#### PROs:

- **not put global std::cin on a bad state**<br>
  Imagine we tried `cin >> number;`, but the user provided a letter, cin would now be on a bad state.<br>
  By extracting the line as a string, we avoid this situation.

- **Less code duplication** (more on this on the CONs)<br>
  If there is something wrong on the input handling, we don't need to scan all our code to fix it, there's a few places that we need to check.

- **No scope pollution**<br>
  At least regarding variables, we are not polluting the scope anymore.<br>
  All variables are scoped to their respective functions.

- **Less clutter**<br>
  Now the input read part is just a function call which doesn't obfuscate the program logic.

- **Error checking**<br>
  Now we can check for errors on input and act accordingly.

#### CONs:

- **Some code duplication**<br>
  By using simple functions without the help of templates or anything, we need to declare one function for each type we need.<br>
  On the example, `read_integer` reads an `int`, but what if we need `short`? Or `double`? `long`? `unsigned`? `char`? And so on...

##### Note:

There are a lot of ways of providing error information to whoever called the function, including returning the error and the value instead of taking a reference, for example returning std::pair, std::tuple or some struct containing an error field and a value field, or even throwing exceptions.

The point that it's made here is that we have the ability of checking the error and the input reading part of the code is isolated.
