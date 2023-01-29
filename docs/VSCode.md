
## VSCode setup instructions

VSCode provides a decent environment to work in C with its highly customizable features, low overhead, and rich extension options.

The folder `.vscode` configures the workspace for use with VSCode.

`tasks.json` describes build and run commands. 

Ctrl+Shift+B will build and run the programs.

You may have to change compilerPath in c_cpp_properties.json to your own compiler.

I'm using GCC 8.1 (came with CodeBlocks) with the -ansi flag.

I referenced this article when setting up the VSCode environment. [Medium Article](https://medium.com/swlh/simple-vscode-setup-to-develop-c-7830182ee4d8)

I referenced the [gcc documentation](https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html) while setting up the compiler.

