<img src="doc/urlang.png" height="120" align="right">

[![Build Status][1]][2]

[1]: https://img.shields.io/appveyor/ci/DangerRust/visual-urlang.svg
[2]: https://ci.appveyor.com/project/DangerRust/visual-urlang

Visual Urlang is a new programming language which is morally inspired Visual
BASIC 6.0. 

## Outline.

Visual Urlang builds on the Web Scale Object Model (WSOM) and includes features
like Modules and Anonymous Functions from ML as well as introducing
Polymorphic Identifiers.

Consider this Class Module with a Functor for example:

```vb6
Functor (T As Type)

Public Function GetAT(ByVal a_t As T)
    Dim anonymous_function = Function (ByVal a_t As T)
                                 Return a_t
                             End Function
    GetAT = local://anonymous_function(a_t)
End Function
```

There is documentation be created in the Docs: Read it [here](doc/README.md).

## Community
 - Contributors to Visual Urlang are welcomed.
 - Contributors should behave in a Christian way.

## Copying
Visual Urlang is proprietary software. Licensing terms are detailed in the
End-User License Agreement, available in the file [EULA.md](EULA.md).

The WSOM SDK is licensed under the Common Distribution and Development License
(CDDL) version 1.1. Details are found in the file [WSOM_SDK/COPYING.md](WSOM_SDK/COPYING.md).

Code under the folder *External* is imported from other projects and each package
has its own subdirectory there with a license.