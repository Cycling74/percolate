# percolate
A collection of synthesis, signal processing, and image processing objects originally authored by Dan Trueman and Luke Dubois.

## Hacking

```
# Clone the repository
git clone git@github.com:Cycling74/percolate.git

# Get the Max SDK submodule
git submodule update --init
```

If you have issues doing `git submodule update --init`, you may need to remove any residual Max SDK caches in Git first: 
```
git rm -r --cached source/maxsdk
```

## Building

```
mkdir build
cd build
cmake -G "Ninja" ..  # Or whichever generator you choose
cmake --build .
```
