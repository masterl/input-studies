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
