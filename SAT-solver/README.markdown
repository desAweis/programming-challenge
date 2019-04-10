# SAT-solver challenge

The specific descriptions of this challenge can be found in `description-1.png` and `description-2.png`.

One of the possible solution is presented named `sat.cpp`.

# Main idea:

brute force

- `regex_search` extract all occurred variables

- `set` delete repeat variables
- `bitset` assign bit values in canonical order to all variables
- `map` to store corresponding values
- `regex_search` find and replace every  internal tuple "|xy" by "0" or "1", loop until s == "1" or "0"
- `regex_match` handle invalid input

# sample input

## satisfiable input

- Run `./sat '||uv&!w|v!uy'` 

## invalid input

- Run `./sat '&.a'`
- Run `./sat '&a'`
- Run `./sat '&aaa'`
- Run `./sat 'a'`

