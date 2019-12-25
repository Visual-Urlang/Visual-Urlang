<img src="doc/urlang.png" height="120" align="right">

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
    Dim AnonymousFunction = Function (ByVal a_t As T)
                                Return a_t
                            End
    GetAT = local://AnonymousFunction(a_t)
End Function
```

## Community
 - Contributors to Visual Urlang are welcomed.
 - Contributors should behave in a Christian way.

## Copying
Visual Urlang is proprietary software. Licensing terms are detailed in the
End-User License Agreement, available in the file [EULA.md](EULA.md).
