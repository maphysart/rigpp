# Basics
**Rigpp** is a rigging system based on C++ runtime evaluation using LLVM/Clang. It uses LLVM and Clang of 14.0.0 version, which could be upgraded to any version you want. There are no additional dependencies as all the tools are already included. 

This implementation is in progress as some issues are currently not solved (see below). No internal hierarchy here, but you can use numbers, Vector, Matrix, Quat and Nurbs Curve. API of these types you can be found in `maya_module\rigpp\runtime\include\rigpp_math.hpp`

# File structure

| Folder| Description|
|-|-|
| maya_module| Ready to use tool for Maya. | 
| /platform | Plugins for diffrerent Maya versions. |
| /runtime | Environment for your C++ rigs. |
| /scripts | Additional python scripts. |
| plugin| Sources for rigpp compilation. | 
| vscode_project| Predefined vscode project to work with rigpp. | 

Please make sure  libs and default includes are packed into an archive. Just unzip all of them as described in readme.txt in each appropriate folder. Notice that debug libraries are not provided with the sources due to their large size (>6.5GB). They will be distributed separately (on release page).

# Installation
Put the content of `maya_module` into your MAYA_MODULE_PATH (such as `C:/Users/USER_NAME/Documents/maya/modules`). Then in Maya make sure you have `rigpp.mll` loaded.
If you don't like modules, load `rigpp.mll` any way you want and make sure you have set up `RIGPP_RUNTIME` environment variable to `maya_module/rigpp/runtime`.

# How to use
1. Load `rigpp.mll` plugin.
2. Create `rigpp` node in Maya.
3. Add some input and output attributes.<br>
  Use `maya_module\rigpp\scripts\rigpp_utils.py` for helper functions.
4. Write code for the node.<br>
  Use `extern type @var` for your attributes to make them visible in your code.

If the value of `rigpp._source` attribute is a C++ file, then `.bc` file will be created near that file. Bitcode files are dependency free (no includes are required to load and evaluate them)!
  
# Issues
### Name mangling
I didn't find any appropriate way of finding mangle names of symbols. So in code there is a lot of `?var@@3HA` things and it's good to find something more general here. 

**Question**: How to find that `int a` will be mangled into `?a@@3HA`?

### Resource deallocation and smart pointers
How to release LLJIT and its context properly? When you try to use host `shared_ptr<int> ptr` and on the jit side you use `ptr = make_shared<int>()` then you'll get a crash on a free memory state (recompilation). This code itself works fine, pointer counters are considered and nothing strange occurs.

**Question**: How to properly setup LLJIT to make it possible for doing multiple compilations and evaluations? Do I need to remove all symbols manually?
Should I call `jit->deinitialize(jit->getMainJITDylib())` explicitly to run destructors? Actually I get a crash on doing this...

### Exceptions
How to setup exceptions for LLJIT? I've read an article of Emmanuel Roche here https://wiki.nervtech.org/doku.php?id=blog:2020:0414_jit_cpp_compiler
but I cannot make it work. I've tried `SingleSectionMemoryManager` as he wrote and define `_CxxThrowException` and do other stuff. But no solution at this moment.
